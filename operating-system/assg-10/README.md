# Question

Write a program to add two arrays. The addition should be performed by calling a function from a dyanmic linked library. [ use dlopen(), dlsym() and dlclose() ]

## Compilation

compile library function addVec.c with:
```cc -c addVec.c```

make shared library mylib.so with:
```cc -shared -fPIC -o mylib.so addVec.o```

compile driver program as10q1.c with:
```cc -rdynamic -O2 -o q1 as10q1.c -ldl```

run program q1 with:
```./q1```
