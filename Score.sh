== Test uthread == 
$ make qemu-gdb
uthread: OK (4.0s) 
== Test answers-thread.txt == answers-thread.txt: OK 
== Test ph_safe == make[1]: Entering directory '/home/silence/xv6-labs-2021'
gcc -o ph -g -O2 -DSOL_THREAD -DLAB_THREAD notxv6/ph.c -pthread
make[1]: Leaving directory '/home/silence/xv6-labs-2021'
ph_safe: OK (10.1s) 
== Test ph_fast == make[1]: Entering directory '/home/silence/xv6-labs-2021'
make[1]: 'ph' is up to date.
make[1]: Leaving directory '/home/silence/xv6-labs-2021'
ph_fast: OK (23.2s) 
== Test barrier == make[1]: Entering directory '/home/silence/xv6-labs-2021'
gcc -o barrier -g -O2 -DSOL_THREAD -DLAB_THREAD notxv6/barrier.c -pthread
make[1]: Leaving directory '/home/silence/xv6-labs-2021'
barrier: OK (10.8s) 
== Test time == 
time: OK 
Score: 60/60