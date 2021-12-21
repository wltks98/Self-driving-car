from picamera import PiCamera
import cv2
import time
from pyzbar import pyzbar

camera = PiCamera()
camera.resolution = (640,480)
camera.start_preview()
camera.capture('/home/pi/rcCar/image.jpeg',use_video_port = True)
camera.stop_preview()
camera.close()

qrDecoder = cv2.QRCodeDetector()

img = cv2.imread('/home/pi/rcCar/image.jpeg')
qr = cv2.resize(img, None, fx=0.2, fy=0.2, interpolation=cv2.INTER_AREA)
data, _, _ = qrDecoder.detectAndDecode(qr)
if len(data) >0 :
    flag = 1
else:
    flag = 0
    
print(flag)

barcode = pyzbar.decode(img)
code = barcode[0].data.decode('utf-8')

if(code == ""):
    flag = 0
else:
    flag = 1
    
print(flag)
