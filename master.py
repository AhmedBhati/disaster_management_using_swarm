import serial
import re
from time import sleep
import color_processing_library
value=serial.Serial('COM13',9600, timeout=None)
print("enter the coordinates")
coords=input()#user input
temp=re.findall(r"\d+",coords)#taking coords from the string
x=str(temp[0])#taking in form of x x-coordinate
y=str(temp[1])#taking in form of y y-coordinate
print(x)
print(y)
value.write(x.encode())
feedback=value.read().decode('ascii')
print(feedback)
sleep(0.1)
value.write(y.encode())
feedback=value.read().decode('ascii')
print(feedback)
while True: #for 4 node bots#
     _, frame = camera.read()
    blurred = cv2.GaussianBlur(frame, (11, 11), 0)
    hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)
    for key, value in upper.items():
        mask = cv2.inRange(hsv, lower[key], upper[key])
        blurred_mask = cv2.GaussianBlur(mask, (9, 9), 3, 3)
        erode_element = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))
        dilate_element = cv2.getStructuringElement(cv2.MORPH_RECT, (8, 8))
        eroded_mask = cv2.erode(blurred_mask, erode_element)
        dilated_mask = cv2.dilate(eroded_mask, dilate_element)
        circles = cv2.HoughCircles(dilated_mask, cv2.HOUGH_GRADIENT, 3.0, 100)
        if circles is not None:
            circles = np.round(circles[0, :]).astype("int")
            for (x, y, r) in circles:
                cv2.circle(frame, (x, y), r, (0, 255, 0), 4)
                cv2.rectangle(frame, (x - 5, y - 5), (x + 5, y + 5), (0, 128, 255), -1)
                color=key
                sleep(1)
    if(key!=check)
        check=key
        print(key)
        i++
        value.write(color.encode())
        if(i=4)
            break
            counter+1
if(counter=1)
    break
    
    while 1:
        feedback=value.read().decode('ascii')
        if(feedback==1):
            break



