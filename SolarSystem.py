import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from mpl_toolkits.mplot3d import Axes3D

f=open("good.txt")
n=8
x=[[] for i in range(n)]
y=[[] for i in range(n)]
z=[[] for i in range(n)]

t=0
now=0
for l in f:
    ls=[float(i) for i in l.split()]
    if now%(n+1)==0:
        t=ls[0]
    else:
        i=now%(n+1)-1
        x[i].append(ls[0])
        y[i].append(ls[1])
        z[i].append(ls[2])
    now+=1

N=len(x[0])

data = [[] for i in range(n)] # data[i]: ith planet,  data[i][0]: ith planet's x coordinate
for i in range(n):
    data[i].append(x[i])
    data[i].append(y[i])
    data[i].append(z[i])

data=np.array(data)

fig = plt.figure()
ax = fig.add_subplot(projection='3d')
plt.title("solar system")
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")
R=5000E9
ax.set_xlim(-R,R)
ax.set_ylim(-R,R)
ax.set_zlim(-R,R)

line = []
for i in range(n):
    ll, = ax.plot(data[i,0,0:1], data[i,1,0:1], data[i,2,0:1])
    line.append(ll)

def update(num, data, line):
    for i in range(n):
        line[i].set_data(data[i,:2,:num])
        line[i].set_3d_properties(data[i,2,:num])

ani = animation.FuncAnimation(fig, update, N, fargs=(data, line), interval=0.1, blit=False)
plt.show()
