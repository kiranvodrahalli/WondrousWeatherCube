# COS 436: Lab 0 : Wondrous Weather Cube
# Author: Kiran Vodrahalli, Collin Stedman 
# Date: Feb 19, 2013
# cube_handler.py: Fetches data from the arduino device as to whether the
# photosensor is receiving light or not. If the sensor is receiving light, 
# then the weather side must be faceup, so run the weather app. 
# If the sensor is not receiving light, the NASDAQ side is faceup, so run
# the nasdaq app. 
# Uses the nasdaq_scraper.py and weather_scraper.py files, as well as 
# PySerial, time, and regular expressions. 

#imports
import nasdaq_scraper 
import weather_scraper 
import serial
import time
import re


#OUTLINE

#get the data from the photosensor (light or no light)

#if light --> weather side
#call the weather_scraper function

#if no light --> nasdaq side
#call the nasdaq_scraper function

#if there is an change in the data from the photosensor, interrupt the current
#function that's running and switch to the other one immediately.


#get the Arduino serial
ser = serial.Serial('/dev/tty.usbmodem411', 9600)
ser.close()
ser.open()


print("Serial attached")
if ser.readable():
    photovoltage = ser.readline()

while re.match(r'[0-9][0-9][0-9]\r\n', photovoltage) == None:
    if ser.readable():
        photovoltage = ser.readline()

photovoltage = int(photovoltage)


print("Photovoltage: ")
print(photovoltage)
while True:
    #ser.flushInput()
    print("newloop")
    if photovoltage < 600:
        nasdaq_scraper.runNASDAQ(ser)
    else:
        weather_scraper.runWeather(ser)

    if ser.isOpen():
        if ser.readable():
            photovoltage = ser.readline()
        while re.match(r'[0-9][0-9][0-9]\r\n', photovoltage) == None:
            if ser.readable():
                photovoltage = ser.readline()
        
        photovoltage = int(photovoltage)
        print("Photovoltage: ")
        print(photovoltage)
        time.sleep(1)
         
