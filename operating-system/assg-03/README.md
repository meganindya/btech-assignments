# Question

1. Demonstrate how a Zombie process is created in a system.
2. Write programs to show how zombie prevention is done in 4 different ways.
3. Write a program that has masked interrupts.

## Comments

1. Child process is listed as *defunct*.
2. Child process is no longer *defunct*.
    1. calling *wait()* in parent.
    2. using *signal(SIGCHLD, SIG_IGN)* system call.
    3. using a signal handler and calling *wait()* from it.
    4. converting child into grandchild, where child exits right after calling grandchild.
3. Use ```Ctrl+Z``` to stop.
