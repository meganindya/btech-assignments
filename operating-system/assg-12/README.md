# Question

Demonstrate "Memory Mountain".

## Files

clock.{c,h}	- routines for using Pentium and Alpha cycle timers
fcyc2.{c,h}	- routines that use the K-best scheme for estimating
	          the number of cycles required by a function f
		  that takes two arguments.
		  (See "Measuring Program Performance" Chapter for
		  a discussion of the K-best scheme.)
makefile	- memory mountain makefile
mountain.c	- program that generates the memory mountain.

## Compilation

```gcc Wall -O2 -o mountain mountain.c fcyc2.c clock.c```