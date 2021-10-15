#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

const char* ping = "ping\0";
const char* pong = "pong\0";

int main()
{
    char buf[32];

    int child_to_parent[2];
    int parent_to_child[2];
    pipe(child_to_parent);
    pipe(parent_to_child);
    
    if (fork() == 0) {
        close(parent_to_child[1]);
        while (read(parent_to_child[0], buf, sizeof(buf))) {
            printf("%d: received ping\n", getpid());
        }

        close(child_to_parent[0]);
        write(child_to_parent[1], pong, sizeof(pong));
        close(child_to_parent[1]);
        exit(0);
    } else {
        close(parent_to_child[0]);
        write(parent_to_child[1], ping, sizeof(ping));
        close(parent_to_child[1]);

        close(child_to_parent[1]);
        while (read(child_to_parent[0], buf, sizeof(buf))) {
            printf("%d: received pong\n", getpid());
        }
        exit(0);
    }

    return 0;
}

