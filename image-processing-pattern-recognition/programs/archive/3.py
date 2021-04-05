import matplotlib.pyplot as plt
import matplotlib as mp
import numpy as np
from PIL import Image

datContent = [i.strip().split() for i in open("b256.dat").readlines()]
array = np.array(datContent,dtype='int')
n = len(array)

L = np.amax(array)
for i in range(n):
    for j in range(n):
        array[i][j]=L-1-array[i][j]

array = np.array(array,dtype='str')
lines=[]
for i in range(n):
    lines.append(' '.join(array[i]))

with open("negative.dat", "w") as outfile:
    outfile.write("\n".join(lines))
#mp.image.imsave('negative.png', array)