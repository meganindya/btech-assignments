import matplotlib.pyplot as plt
import matplotlib as mp
import numpy as np
# from PIL import Image
from scipy import ndimage

datContent = [i.strip().split() for i in open("b256.dat").readlines()]
array = np.array(datContent,dtype='int')
n = len(array)

a = ndimage.interpolation.zoom(array,.5)
b = ndimage.interpolation.zoom(a,.5)
c = ndimage.interpolation.zoom(b,.5)
d = ndimage.interpolation.zoom(array,2)
e = ndimage.interpolation.zoom(d,2)
f = ndimage.interpolation.zoom(e,2)

n = len(a)
a = np.array(a,dtype='str')
lines=[]
for i in range(n):
    lines.append(' '.join(a[i]))
with open("down2x.dat", "w") as outfile:
    outfile.write("\n".join(lines))
mp.image.imsave('down2x.png', a)


n = len(b)
b = np.array(b,dtype='str')
lines=[]
for i in range(n):
    lines.append(' '.join(b[i]))
with open("down4x.dat", "w") as outfile:
    outfile.write("\n".join(lines))
mp.image.imsave('down4x.png', b)


n = len(c)
c = np.array(c,dtype='str')
lines=[]
for i in range(n):
    lines.append(' '.join(c[i]))
with open("down8x.dat", "w") as outfile:
    outfile.write("\n".join(lines))
mp.image.imsave('down8x.png', c)

n = len(d)
d = np.array(d,dtype='str')
lines=[]
for i in range(n):
    lines.append(' '.join(d[i]))
with open("up2x.dat", "w") as outfile:
    outfile.write("\n".join(lines))
mp.image.imsave('up2x.png', d)



n = len(e)
e = np.array(e,dtype='str')
lines=[]
for i in range(n):
    lines.append(' '.join(e[i]))
with open("up4x.dat", "w") as outfile:
    outfile.write("\n".join(lines))
mp.image.imsave('up4x.png', e)


n = len(f)
f = np.array(f,dtype='str')
lines=[]
for i in range(n):
    lines.append(' '.join(f[i]))
with open("up8x.dat", "w") as outfile:
    outfile.write("\n".join(lines))
mp.image.imsave('up8x.png', f)
#print(f.shape)
