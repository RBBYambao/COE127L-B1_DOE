import matplotlib.pyplot as plt

x = [149815,359455,656628,1107080,7936016]
y = [0.0679758,0.395015,0.49064,1.83245,5.97505]
x1 = [149815,359455,656628,1107080,7936016]
y1 = [0.0161574,0.124158,0.173754,0.538747,1.8599]


plt.plot (x,y, marker='^', color='red', label='Single-Thread' )
plt.plot (x1,y1,marker='o', color='green', label='Multithreaded')
plt.title ("MEDIAN FILTER")
plt.xlabel("Image's Size(Bytes)")
plt.ylabel("Time(sec)")
plt.legend()
plt.show()
