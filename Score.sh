silence@silence-vm:~/xv6-labs-2021$ ./grade-lab-pgtbl 
make: 'kernel/kernel' is up to date.
== Test pgtbltest == (1.8s) 
== Test   pgtbltest: ugetpid == 
  pgtbltest: ugetpid: OK 
== Test   pgtbltest: pgaccess == 
  pgtbltest: pgaccess: OK 
== Test pte printout == pte printout: OK (0.8s) 
== Test answers-pgtbl.txt == answers-pgtbl.txt: OK 
== Test usertests == (290.3s) 
== Test   usertests: all tests == 
  usertests: all tests: FAIL 
    ...
         test forktest: OK
         test bigdir: bigdir: bigdir link(bd, x00) failed
         FAILED
         SOME TESTS FAILED
         $ qemu-system-riscv64: terminating on signal 15 from pid 42351 (make)
    MISSING '^ALL TESTS PASSED$'
== Test time == 
time: OK 
Score: 36/46