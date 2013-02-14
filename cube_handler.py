# COS 436: Lab 0 : Wondrous Weather ube
# Author: Kiran Vodrahalli 
# Date: Feb 14, 2013
# cube_handler.py: Fetches data from the arduino device as to whether the
# photosensor is receiving light or not. If the sensor is receiving light, 
# then the weather side must be faceup, so run the weather app. 
# If the sensor is not receiving light, the NASDAQ side is faceup, so run
# the nasdaq app. 
# Uses the nasdaq_scraper.py and weather_scraper.py files. 

#imports
import nasdaq_scraper # need to define the file as a function
import weather_scraper # need to define the file as a function
import serial

#get the Arduino serial
ser = serial.Serial('/dev/tty.usbmodem621', 9600)
ser.close()
ser.open()

print("Serial attached")

while True:

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
