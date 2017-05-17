# please install first :
#apt get install python-serial psutils net-tools

import os
from collections import namedtuple
import time
import serial
import socket
import fcntl
import struct
import subprocess

def get_ip_address(ifname):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return socket.inet_ntoa(fcntl.ioctl(
        s.fileno(),
        0x8915,  # SIOCGIFADDR
        struct.pack('256s', ifname[:15])
    )[20:24])


watch_disk_path="/home/" #change to owncloud drive

ser = serial.Serial(
    port='/dev/ttyACM0', #change eg /dev/ttyUSB0
    baudrate=9600,        # change to 9600 baud see script.ino
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)

ser.isOpen()


_ntuple_diskusage = namedtuple('usage', 'total used free')
def disk_usage(path):
    """Return disk usage statistics about the given path.

    Returned valus is a named tuple with attributes 'total', 'used' and
    'free', which are the amount of total, used and free space, in bytes.
    """
    st = os.statvfs(path)
    free = st.f_bavail * st.f_frsize
    total = st.f_blocks * st.f_frsize
    used = (st.f_blocks - st.f_bfree) * st.f_frsize
    return _ntuple_diskusage(total, used, free)





while 42:
    # GET DIS USAGE
    watch_disk_usage_percentage = int(((1.0/disk_usage(watch_disk_path).total) * disk_usage(watch_disk_path).used)*100)
    # GET RAM
    tot_m, used_m, free_m = map(int, os.popen('free -t -m').readlines()[-1].split()[1:])
    ram_usage_percentage = (1.0/tot_m)*used_m*100
    uart_send_string = "127.0.0.01" + "_" + str(watch_disk_path) + "_" + str(watch_disk_usage_percentage) + "_" + str(int(ram_usage_percentage)) + "_"
   
    print("send :  "+uart_send_string)
    ser.write(uart_send_string + "\n")
    time.sleep(1)
  #  print(ser.read())
    pass

