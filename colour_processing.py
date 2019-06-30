# python color_tracking.py --video balls.mp4
# python color_tracking.py

# import the necessary packages
from collections import deque
from time import sleep
import numpy as np
import argparse
import imutils
import cv2
import urllib  # for reading image from URL

# construct the argument parse and parse the arguments
'''ap = argparse.ArgumentParser()
ap.add_argument("-v", "--video",
                help="path to the (optional) video file")
ap.add_argument("-b", "--buffer", type=int, default=64,
                help="max buffer size")
args = vars(ap.parse_args())'''

# define the lower and upper boundaries of the colors in the HSV color space
lower = {'green': (66, 122, 129), 'blue': (110, 100, 117), 'yellow': (48, 30, 119)
         ,'orange': (0, 110, 200)}
# assign new item lower['blue'] = (93, 10, 0)
upper = {'green': (86, 255, 255), 'blue': (130, 255, 255), 'yellow': (58, 200, 255)
         ,'orange': (20, 255, 255)}

# define standard colors for circle around the object
colors = {'red': (0, 0, 255), 'green': (0, 255, 0), 'blue': (255, 0, 0), 'yellow': (0, 255, 217), 'white': (255,255,255)
          ,'orange': (0, 140, 255)}

# pts = deque(maxlen=args["buffer"])

# if a video path was not supplied, grab the reference
# to the webcam
camera = cv2.VideoCapture(0)
'''if not args.get("video", True):
    camera = cv2.VideoCapture(0)


# otherwise, grab a reference to the video file
else:
    camera = cv2.VideoCapture(args["video"])'''
# keep looping
while True:
    _, frame = camera.read()
    # resize the frame, blur it, and convert it to the HSV
    # color space
    #frame = imutils.resize(frame, width=600)

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    # for each color in dictionary check object in frame
    for key, value in upper.items():
        # construct a mask for the color from dictionary`1, then perform
        # a series of dilations and erosions to remove any small
        # blobs left in the mask
        mask = cv2.inRange(hsv, lower[key], upper[key])
        blurred_mask = cv2.GaussianBlur(mask, (9, 9), 3, 3)
        erode_element = cv2.getStructuringElement(cv2.MORPH_RECT, (6, 6))
        dilate_element = cv2.getStructuringElement(cv2.MORPH_RECT, (6, 6))
        eroded_mask = cv2.erode(blurred_mask, erode_element)
        dilated_mask = cv2.dilate(eroded_mask, dilate_element)
        #cv2.imshow('dilated_mask',dilated_mask)
        cv2.imshow('eroded_mask',eroded_mask)
        # find contours in the mask and initialize the current
        # (x, y) center of the ball
        circles = cv2.HoughCircles(dilated_mask, cv2.HOUGH_GRADIENT, 1.4, 100)
        #cv2.imshow("hough_circles",circles)
        if circles is not None:
            circles = np.round(circles[0, :]).astype("int")
            for (x, y, r) in circles:
                cv2.circle(frame, (x, y), r, (0, 255, 0), 4)
                cv2.rectangle(frame, (x - 5, y - 5), (x + 5, y + 5), (0, 128, 255), -1)
                sleep(0)
                print(key)

        cv2.imshow("output", frame)
    key = cv2.waitKey(1) & 0xFF
    # if the 'q' key is pressed, stop the loop
    if key == ord("q"):
        break

# cleanup the camera and close any open windows
camera.release()
 
