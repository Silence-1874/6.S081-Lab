silence@silence-vm:~/xv6-labs-2021$ ./grade-lab-traps 
make: 'kernel/kernel' is up to date.
== Test answers-traps.txt == answers-traps.txt: OK 
== Test backtrace test == backtrace test: OK (1.4s) 
== Test running alarmtest == (4.5s) 
== Test   alarmtest: test0 == 
  alarmtest: test0: OK 
== Test   alarmtest: test1 == 
  alarmtest: test1: OK 
== Test   alarmtest: test2 == 
  alarmtest: test2: OK 
== Test usertests == Timeout! usertests: FAIL (300.2s) 
    ...
         usertrap(): unexpected scause 0x000000000000000f pid=31
                     sepc=0x0000000000002208 stval=0x8000000000000000
         OK
         test manywrites: panic: balloc: out of blocks
         qemu-system-riscv64: terminating on signal 15 from pid 62083 (make)
    MISSING '^ALL TESTS PASSED$'
    QEMU output saved to xv6.out.usertests
== Test time == 
time: OK 
Score: 66/85
