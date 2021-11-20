== Test running cowtest == 
$ make qemu-gdb
Timeout! (34.4s) 
== Test   simple == 
  simple: FAIL 
    Number of appearances of 'simple: ok'
    got:
      0
    expected:
      2
== Test   three == 
  three: FAIL 
    Number of appearances of 'three: ok'
    got:
      0
    expected:
      3
== Test   file == 
  file: FAIL 
    ...
         *** Now run 'gdb' in another window.
         
         xv6 kernel is booting
         
         qemu-system-riscv64: terminating on signal 15 from pid 81791 (make)
    MISSING '^file: ok$'
== Test usertests == 
$ make qemu-gdb
Timeout! (300.3s) 
         *** Now run 'gdb' in another window.
         
         xv6 kernel is booting
         
         qemu-system-riscv64: terminating on signal 15 from pid 82200 (make)
    MISSING '^ALL TESTS PASSED$'
    QEMU output saved to xv6.out.usertests
== Test   usertests: copyin == 
  usertests: copyin: FAIL 
    Parent failed: test_usertests
== Test   usertests: copyout == 
  usertests: copyout: FAIL 
    Parent failed: test_usertests
== Test   usertests: all tests == 
  usertests: all tests: FAIL 
    Parent failed: test_usertests
== Test time == 
time: OK 
Score: 1/110
make: *** [Makefile:336: grade] Error 1
