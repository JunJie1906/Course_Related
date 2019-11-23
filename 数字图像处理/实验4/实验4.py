import sys
import numpy as np
import matplotlib.pyplot as plt

argc = len(sys.argv)
if argc == 1:
    N = 10000
else:
    N = int(sys.argv[1])

dt    = 1/N
t     = np.arange(0, 1, dt)
dW    = 1/np.sqrt(N)*np.random.randn(N)
dW[0] = 0
W     = np.cumsum(dW)

plt.plot(t, W)
plt.savefig('wiener.png')
plt.close()

plt.plot(t[0:int(N/10)], W[0:int(N/10)])
plt.savefig('wiener_zoomed.png')
plt.close()