import numpy as np
import cv2
import imutils
dup = []

'''lower = {'green': (60, 96, 25)}
upper = {'green': (80, 255, 255)}'''
lower = {'green': (60, 96, 25), 'yellow': (27, 45, 137), 'orange': (0, 89, 142),'blue':(90,73,120)}
upper = {'green': (80, 255, 255), 'yellow': (55, 255, 255), 'orange': (10, 255, 255),'blue':(110,255,255)}
camera = cv2.VideoCapture(0)
while True:
    _, frame = camera.read()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    for key, value in upper.items():
        lower_blue = np.array(lower[key])
        upper_blue = np.array(upper[key])
        mask = cv2.inRange(hsv, lower_blue, upper_blue)
        blurred = cv2.GaussianBlur(frame, (5, 5), 0)
        erode_element = cv2.getStructuringElement(cv2.MORPH_RECT, (6, 6))
        dilate_element = cv2.getStructuringElement(cv2.MORPH_RECT, (6, 6))
        eroded_mask = cv2.erode(mask, erode_element)
        dilated_mask = cv2.dilate(eroded_mask, dilate_element)
        cnts = cv2.findContours(dilated_mask.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)
        center = None
        if len(cnts) > 0:
            # find the largest contour in the mask, then use
            # it to compute the minimum enclosing circle and
            # centroid
            c = max(cnts, key=cv2.contourArea)
            ((x, y), radius) = cv2.minEnclosingCircle(c)
            M = cv2.moments(c)


            # only proceed if the radius meets a minimum size
            if radius > 20:
                # draw the circle and centroid on the frame,
                # then update the list of tracked points
                cv2.circle(frame, (int(x), int(y)), int(radius),
                           (0, 255, 255), 2)
                cv2.circle(frame, center, 5, (0, 0, 255), -1)
                if key not in dup:
                    print(key)
                    dup.append(key)

        cv2.imshow("output1", mask)
        cv2.imshow("output2", frame)

    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break

camera.release()

cv2.destroyAllWindows()

