#Computer Organisation & Architecture Lab (IT451)
All the generated FPGA devices work as intended. However, there are some flaws.

If there is any unfinished 'if statement' (i.e. missing else statement without any initialisation of the variables the if statement changes) or there is an unfinished 'case statement' (i.e. missing others statement) untimely latches are generated which isn't desirable in FPGAs.

Another one is that if you use intermediate signals instead on variables in sequential circuits with edge triggered clock, the signal will update in the next clock cycle unlike variables.

