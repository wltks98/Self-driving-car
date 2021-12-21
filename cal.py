import socket
import sys
import os
import numpy as np
import pdb
import math
import cv2
import time
from pyzbar import pyzbar

from picamera import PiCamera

from Image import *
from Utils import *

def cal() :
    font = cv2.FONT_HERSHEY_SIMPLEX
    direction = 0
    w = 1080
    h = 1080
    a = 250

    #N_SLICES만큼 이미지를 조각내서 Images[] 배열에 담는다
    Images=[]
    N_SLICES = 3

    for q in range(N_SLICES):
        Images.append(Image())

    camera = PiCamera()
    camera.resolution = (w,h)
    camera.start_preview()
    camera.capture('/home/pi/rcCar/image.jpeg',use_video_port = True)
    camera.stop_preview()
    camera.close()

    img = cv2.imread('/home/pi/rcCar/image.jpeg')
    barcode = pyzbar.decode(img)

    if(barcode):
        flag = 1
    else:
        flag = 0

    if img is not None:
        #이미지를 조각내서 윤곽선을 표시하게 무게중심 점을 얻는다
        Points = SlicePart(img, Images, N_SLICES)
        print('Points : ', Points)

        #N_SLICES 개의 무게중심 점을 x좌표, y좌표끼리 나눈다
        x = int(Points[0][0])
        y = int(Points[1][0])
        z = int(Points[2][0])
        
        
        if(x > w/2 + a) :
            direction = 'R'
        elif(x < w/2 - a) :
            direction = 'L'
        else:
            direction = 'G'

#         result = int(math.atan((abs(x - (w/2))/(h/2)))*180/math.pi)
#         print(direction)
#         print(result)
        

    return direction, flag

