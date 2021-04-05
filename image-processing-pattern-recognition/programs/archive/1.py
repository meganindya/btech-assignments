import matplotlib.pyplot as plt
import matplotlib as mp
import numpy as np
from PIL import Image

datContent = [i.strip().split() for i in open("b256.dat").readlines()]
array = np.array(datContent,dtype='int')
n = len(array)

min_pix = min( [min(i) for i in array] )
max_pix = max( [max(i) for i in array] )
print('Min pixel value is ',min_pix)
print('Max pixel value is ',max_pix)

thresh =int((min_pix + max_pix)/2) 
print('Threshold is ',thresh)

H = (array>thresh)*array

thresh2 = 128
H1 = (array>thresh2)*array


H = np.array(H,dtype='str')
lines=[]
for i in range(n):
    lines.append(' '.join(H[i]))

with open("demo_thresh.dat", "w") as outfile:
    outfile.write("\n".join(lines))

H1 = np.array(H1,dtype='str')
lines=[]
for i in range(n):
    lines.append(' '.join(H1[i]))

with open("demo_thresh1.dat", "w") as outfile:
    outfile.write("\n".join(lines))
#mp.image.imsave('demo.png', array)
#mp.image.imsave('demo_thresh.png',H )
#mp.image.imsave('demo_thresh1.png',H1 )