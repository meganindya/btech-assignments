import matplotlib.pyplot as plt
import matplotlib as mp
import numpy as np
from PIL import Image

datContent = [i.strip().split() for i in open("b256.dat").readlines()]
array = np.array(datContent,dtype='int')
n = len(array)

b = np.amax(array)
a = np.amin(array)

print('Current range is ['+str(a)+', '+str(b)+']')
p = [int(i) for i in input('Enter the values of range, i.e. [c,d] after shifting - ').split(' ')]
c=p[0]
d=p[1]
for i in range(n):
    for j in range(n):
        array[i][j]=c+((array[i][j]-a)*(d-c)/(b-a))


mp.image.imsave('shifted.png', array)

array = np.array(array,dtype='str')
lines=[]
for i in range(n):
    lines.append(' '.join(array[i]))

with open("shifted.dat", "w") as outfile:
    outfile.write("\n".join(lines))
