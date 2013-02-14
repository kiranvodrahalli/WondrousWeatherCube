# COS 436: Lab 0 : Wondrous Weather Cube
# Author: Kiran Vodrahalli
# Date: Feb 14, 2013
# weather_scraper.py: Scrapes Princeton current temperature off weather.com
# using Python, BeautifulSoup, html5lib, urllib2, re, serial, and time. 

#imports 
import html5lib
import urllib2
import re
import serial
import time 
from bs4 import BeautifulSoup

#using the serial (for Arduino)
#port might be different for different computers
#assume that the min temperature is 0 degrees F

ser = serial.Serial('/dev/tty.usbmodem621', 9600)
ser.close()
ser.open()
print("Serial attached"); 
while True:
    #get the html code from weather.com for Princeton
    html = urllib2.urlopen("http://www.weather.com/weather/right-now/USNJ0427:1:US")

    #find the part in the html code where it gives the weather
    soup = BeautifulSoup(html, "html5lib")
    report = soup.find_all("meta", content=re.compile("It's"))

    #string operations to get as an integer
    text = str(report[0])
    #using regular expressions 
    nums = re.findall(r'\d+', text)
    temperature = int(float(nums[0]))
    
    time.sleep(1)
    #write to Arduino Serial
    if ser.isOpen():

        #necessary spacing 
        if temperature < 10 :
            ser.write('0'+ str(temperature))
            print('0'+ str(temperature))
        else:
            ser.write(str(temperature))
            print(str(temperature))

        time.sleep(1)
        ser.flushOutput()


