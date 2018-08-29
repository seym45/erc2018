from scipy.interpolate import interp1d
import numpy as np

y = [68 ,75, 100, 110, 123, 132, 153]
x = [318, 770, 1160, 1260, 1580, 1675, 1900]
f = interp1d(x, y)
f2 = interp1d(x, y, kind='cubic')

xnew = np.linspace(318, 1900, num=100, endpoint=True)
import matplotlib.pyplot as plt
plt.plot(x, y, 'o', xnew, f(xnew), '-', xnew, f2(xnew), '--', 500, f2(500), 'X')
plt.legend(['data', 'linear', 'cubic'], loc='best')
plt.show()
print(f2(500))