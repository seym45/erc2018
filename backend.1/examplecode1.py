def read_data(queue_, should_stop):
    while not should_stop.is_set():
        # calculate/get cX, cY, angle
        queue_.put((cX, cY, angle))
        # sleep 30ms

def send_to_ardunio(queue_, should_stop):
    while not should_stop.is_set():
        data = queue_.get()
        cX, cY, angle = data
        # update ardunio

def tell_when_to_stop(should_stop):
    # detect when to stop, and set the Event. For example, we'll wait for 10 seconds and then ask all to stop
    time.sleep(10)
    should_stop.set()


queue_ = Queue()
should_stop = Event()

thread_stop_decider = Thread(target=tell_when_to_stop, args=(should_stop,))
thread_read = Thread(target=read_data, args=(queue_, should_stop))
thread_ardunio = Thread(target=send_to_ardunio, args=(queue_, should_stop))

thread_read.start()
thread_ardunio.start()
thread_stop_decider.start()

try:
    while thread_read.is_alive():
        thread_read.join(1)
except KeyboardInterrupt:
        should_stop.set()
thread_read.join()
thread_ardunio.join()
thread_stop_decider.join()