# COS 436: Lab 0 : Wondrous Weather Cube
# Authors: Collin Stedman, Kiran Vodrahalli
# Date: Feb 14, 2013
# nasdaq_scraper.py: Scrapes the nasdaq percent change from www.nasdaq.com
# using Python, BeautifulSoup, html5lib, urllib2, re, serial, and time.

#imports
import html5lib
import urllib2
import re
import serial
import time
from bs4 import BeautifulSoup

def runNASDAQ():
    #assume that max value of market is +/- 16
    SCALE = 16/255.0

    #color string
    color_string = ""

    #using the serial (for Arduino)

    #port might be different for different computers
    ser = serial.Serial('/dev/tty.usbmodem411', 9600)
    ser.close()
    ser.open()
    print("Serial attached")

    while True:
        #get the html code from nasdaq.com 
        html = urllib2.urlopen("http://www.nasdaq.com/")

        #find the part in the html code where it gives the NASDAQ % change 
        soup = BeautifulSoup(html, "html5lib")
        report = soup.find(text=re.compile("setIndexInfo"))

        #string operations to get as an integer
        text = str(report)
        #using regular expressions 
        nums = re.findall(r'\-?\d+\.\d+', text)
        sign = float(nums[1])

        if (sign < 0):
            sign = -1
        else :
            sign = 1
        market = float(nums[2])
        #scale to the color we want (RGB scale: R00 if negative, 0G0 if positive)
        color = int(market/SCALE)*sign
    
        #color is a positive value
        if color < 0 :
            color = -color
        if color > 255:
            color = 255

        color_string = str(color)
        time.sleep(1)
        #write to Arduino Serial
        if ser.isOpen():
            #necessary spacing 
            if color < 10:
                color_string = '0' + '0' + color_string
            elif color < 100:
                color_string = '0' + color_string
                
            #increase or decrease?
            if sign < 0:
                ser.write('-' + color_string)
                print('-' + color_string)
            else:
                ser.write('+' + color_string)
                print('+' + color_string)
            time.sleep(1)
            ser.flushOutput()

