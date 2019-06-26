from collections import deque
from time import sleep
import numpy as np
import argparse
import imutils
import cv2
import urllib 
# define the lower and upper boundaries of the colors in the HSV color space
lower = {'red': (0,110,120), 'green': (66, 122, 129), 'blue': (97, 100, 117), 'yellow': (23, 59, 119)
         }
# assign new item lower['blue'] = (93, 10, 0)
upper = {'red': (10,255,255), 'green': (86, 255, 255), 'blue': (117, 255, 255), 'yellow': (54, 255, 255)
         }

# define standard colors for circle around the object
colors = {'red': (0, 0, 255), 'green': (0, 255, 0), 'blue': (255, 0, 0), 'yellow': (0, 255, 217), 'white': (255,255,255)
          }
