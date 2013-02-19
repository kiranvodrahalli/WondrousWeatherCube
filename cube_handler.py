# COS 436: Lab 0 : Wondrous Weather Cube
# Author: Kiran Vodrahalli 
# Date: Feb 14, 2013
# cube_handler.py: Fetches data from the arduino device as to whether the
# photosensor is receiving light or not. If the sensor is receiving light, 
# then the weather side must be faceup, so run the weather app. 
# If the sensor is not receiving light, the NASDAQ side is faceup, so run
# the nasdaq app. 
# Uses the nasdaq_scraper.py and weather_scraper.py files. 

#imports
import nasdaq_scraper 
import weather_scraper 
import serial
import time 

#runWeather
#runNASDAQ

#get the Arduino serial
ser = serial.Serial('/dev/tty.usbmodem411', 9600)
ser.close()
ser.open()

print("Serial attached")
photovoltage = ser.readline()
print("length of string: ")
print(len(photovoltage))
while len(photovoltage) < 5:
    photovoltage = ser.readline()
print("length of string: ")
print(len(photovoltage))
photovoltage = int(photovoltage)

print("Photovoltage: ")
print(photovoltage)
while True:

    print("newloop")
    if photovoltage < 150:
        nasdaq_scraper.runNASDAQ(ser)
    else:
        weather_scraper.runWeather(ser)

    if ser.isOpen():
        photovoltage = ser.readline()
        print("length of string: ")
        print(len(photovoltage))
        
        while len(photovoltage) < 5:
            photovoltage = ser.readline()
        print("length of string: ")
        print(len(photovoltage))
        
        photovoltage = int(photovoltage)
        print("Photovoltage: ")
        print(photovoltage)
        time.sleep(1)
        




    #OUTLINE

    #get the data from the photosensor (light or no light)

    #if light --> weather side
    #call the weather_scraper function

    #if no light --> nasdaq side
    #call the nasdaq_scraper function

    #if there is an change in the data from the photosensor, interrupt the current
    #function that's running and switch to the other one immediately.

    # MAKE SURE THAT THE FUNCTION THAT IS CURRENTLY RUNNING DOES NOT KEEP RUNNING
    # WHEN YOU ATTEMPT TO SWITCH OVER 
