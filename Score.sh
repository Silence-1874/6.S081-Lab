== Test running kalloctest == 
$ make qemu-gdb
Timeout! (202.0s) 
== Test   kalloctest: test1 == 
  kalloctest: test1: FAIL 
    ...
         
         hart 1 starting
         hart 2 starting
         panic: bget: no buffers
         qemu-system-riscv64: terminating on signal 15 from pid 37359 (make)
    MISSING '^test1 OK$'
== Test   kalloctest: test2 == 
  kalloctest: test2: FAIL 
    ...
         
         hart 1 starting
         hart 2 starting
         panic: bget: no buffers
         qemu-system-riscv64: terminating on signal 15 from pid 37359 (make)
    MISSING '^test2 OK$'
== Test kalloctest: sbrkmuch == 
$ make qemu-gdb
Timeout! kalloctest: sbrkmuch: FAIL (90.2s) 
    ...
         
         xv6 kernel is booting
         
         harpanic: bget: no buffers
         qemu-system-riscv64: terminating on signal 15 from pid 37819 (make)
    MISSING '^ALL TESTS PASSED$'
    QEMU output saved to xv6.out.sbrkmuch
== Test running bcachetest == 
$ make qemu-gdb
Timeout! (90.2s) 
== Test   bcachetest: test0 == 
  bcachetest: test0: FAIL 
    ...
         
         hart 1 starting
         hart 2 starting
         panic: bget: no buffers
         qemu-system-riscv64: terminating on signal 15 from pid 37856 (make)
    MISSING '^test0: OK$'
== Test   bcachetest: test1 == 
  bcachetest: test1: FAIL 
    ...
         
         hart 1 starting
         hart 2 starting
         panic: bget: no buffers
         qemu-system-riscv64: terminating on signal 15 from pid 37856 (make)
    MISSING '^test1 OK$'
== Test usertests == 
$ make qemu-gdb
Timeout! usertests: FAIL (300.2s) 
    ...
         xv6 kernel is booting
         
         hart 2 starting
         hart 1 startinpanic: bget: no buffers
         gqemu-system-riscv64: terminating on signal 15 from pid 37891 (make)
    MISSING '^ALL TESTS PASSED$'
    QEMU output saved to xv6.out.usertests
== Test time == 
time: OK 
Score: 1/70