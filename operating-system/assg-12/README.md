# Question

Allocate an integer array of size N. Starting from the first index, sequentially access locations which are S units apart. For example, if N = 5 and S = 2, then indices 0, 3 and 5 should be accessed. Execute this for various combinations of N and S. For each combination, calculate the throughput (number of bytes accessed per unit time). Plot the throughput vs each combination of N and S. This 3-D graph is called "Memory Mountain".

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
