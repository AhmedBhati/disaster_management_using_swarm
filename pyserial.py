import serial
from time import sleep

value = serial.Serial('COM10', 9600,timeout=None)
print("Access to the Arduino Board")
def serialcolour(h):
    value.write(h.encode())
    print(h)


