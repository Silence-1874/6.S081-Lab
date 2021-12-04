// Buffer cache.
//
// The buffer cache is a linked list of buf structures holding
// cached copies of disk block contents.  Caching disk blocks
// in memory reduces the number of disk reads and also provides
// a synchronization point for disk blocks used by multiple processes.
//
// Interface:
// * To get a buffer for a particular disk block, call bread.
// * After changing buffer data, call bwrite to write it to disk.
// * When done with the buffer, call brelse.
// * Do not use the buffer after calling brelse.
// * Only one process at a time can use a buffer,
//     so do not keep them longer than necessary.


#include "types.h"
#include "param.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "riscv.h"
#include "defs.h"
#include "fs.h"
#include "buf.h"

#define NBUCKET 13

struct {
  struct spinlock lock;
  struct buf buf[NBUF];

  // Linked list of all buffers, through prev/next.
  // Sorted by how recently the buffer was used.
  // head.next is most recent, head.prev is least.
  struct {
    struct buf head;
    struct spinlock lock;
  } bucket[NBUCKET];
} bcache;

void
binit(void)
{
  struct buf *b;

  for(int i = 0; i < NBUCKET; i++){
    initlock(&bcache.bucket[i].lock, "bcache");

  // Create linked list of buffers
    bcache.bucket[i].head.prev = &bcache.bucket[i].head;
    bcache.bucket[i].head.next = &bcache.bucket[i].head;
  }

  for(b = bcache.buf; b < bcache.buf+NBUF; b++){
    b->next = bcache.bucket[0].head.next;
    b->prev = &bcache.bucket[0].head;
    initsleeplock(&b->lock, "buffer");
    bcache.bucket[0].head.next->prev = b;
    bcache.bucket[0].head.next = b;
  }
}

// Look through buffer cache for block on device dev.
// If not found, allocate a buffer.
// In either case, return locked buffer.
static struct buf*
bget(uint dev, uint blockno)
{
  struct buf *b;

  int id = blockno % NBUCKET;

  acquire(&bcache.bucket[id].lock);

  // Is the block already cached?
  for(b = bcache.bucket[id].head.next; b != &bcache.bucket[id].head; b = b->next){
    if(b->dev == dev && b->blockno == blockno){
      b->refcnt++;
      release(&bcache.bucket[id].lock);
      acquiresleep(&b->lock);
      return b;
    }
  }

  // Not cached.
  // Recycle the least recently used (LRU) unused buffer.
  
  for(int i = (b->blockno + 1) % NBUCKET; i != id; i = (i + 1) % NBUCKET) {
    acquire(&bcache.bucket[i].lock);
    for(b = bcache.bucket[id].head.prev; b != &bcache.bucket[id].head; b = b->prev){
      if(b->refcnt == 0) {
        b->dev = dev;
        b->blockno = blockno;
        b->valid = 0;
        b->refcnt = 1;

        b->next->prev = b->prev;
        b->prev->next = b->next;
        release(&bcache.bucket[id].lock);
        b->next = bcache.bucket[id].head.next;
        b->prev = &bcache.bucket[id].head;
        bcache.bucket[id].head.next->prev = b;
        bcache.bucket[id].head.next = b;

        release(&bcache.bucket[id].lock);
        acquiresleep(&b->lock);
        return b;
      }
    }
    release(&bcache.bucket[id].lock);
  }
  panic("bget: no buffers");
}

// Return a locked buf with the contents of the indicated block.
struct buf*
bread(uint dev, uint blockno)
{
  struct buf *b;

  b = bget(dev, blockno);
  if(!b->valid) {
    virtio_disk_rw(b, 0);
    b->valid = 1;
  }
  return b;
}

// Write b's contents to disk.  Must be locked.
void
bwrite(struct buf *b)
{
  if(!holdingsleep(&b->lock))
    panic("bwrite");
  virtio_disk_rw(b, 1);
}

// Release a locked buffer.
// Move to the head of the most-recently-used list.
void
brelse(struct buf *b)
{
  if(!holdingsleep(&b->lock))
    panic("brelse");

  int id = b->blockno % NBUCKET;

  releasesleep(&b->lock);

  acquire(&bcache.bucket[id].lock);
  b->refcnt--;
  if (b->refcnt == 0) {
    // no one is waiting for it.
    b->next->prev = b->prev;
    b->prev->next = b->next;
    b->next = bcache.bucket[id].head.next;
    b->prev = &bcache.bucket[id].head;
    bcache.bucket[id].head.next->prev = b;
    bcache.bucket[id].head.next = b;
  }
  
  release(&bcache.bucket[id].lock);
}

void
bpin(struct buf *b) {
  int id = b->blockno % NBUCKET;
  acquire(&bcache.bucket[id].lock);
  b->refcnt++;
  release(&bcache.bucket[id].lock);
}

void
bunpin(struct buf *b) {
  int id = b->blockno % NBUCKET;
  acquire(&bcache.bucket[id].lock);
  b->refcnt--;
  release(&bcache.bucket[id].lock);
}


