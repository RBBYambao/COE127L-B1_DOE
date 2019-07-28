import matplotlib.pyplot as plt


x = [149815,359455,656628,1107080,7936016]
y = [0.0226879,0.157719,0.167859,0.621489,1.86497]
x1 = [149815,359455,656628,1107080,7936016]
y1 = [0.00675029,0.051343,0.102139,0.243976,0.650414]

plt.plot (x,y, marker='^', color='blue', label='Single-Thread' )
plt.plot (x1,y1,marker='o', color='orange', label='Multithreaded')
plt.title ("LOWPASS FILTER")
plt.xlabel("Image's Size(Bytes)")
plt.ylabel("Time(sec)")
plt.legend()
plt.show()

