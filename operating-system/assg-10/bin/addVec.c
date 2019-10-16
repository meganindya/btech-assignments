int addVec(int n, int *a, int *b) {
    int sum = 0;

    for (int i = 0; i < n; i++)
        sum += a[i] + b[i];
    
    return sum;
}