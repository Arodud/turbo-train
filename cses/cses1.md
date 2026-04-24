I've written this thing with just syscalls, but be careful, causee first time  used to many of them, while I've only needed one buffer flush.

Various metrics (More syscalls - M, Less syscalls - L):

strace, n = 1000000:
M: 0.00765  seconds
L: 0.000266 seconds
