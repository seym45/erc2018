
import threading

def set_interval(func, sec):
    def func_wrapper():
        set_interval(func, sec) 
        func()  
    t = threading.Timer(sec, func_wrapper)
    t.start()
    return t

import time
def p():
    print(time.time())

t = set_interval(p,.1)

s = time.time()
while True:
    if(time.time() - s > 5):
        t.cancel()
        print('a')
        break

    