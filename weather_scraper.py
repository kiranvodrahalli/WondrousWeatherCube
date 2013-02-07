# Author: Kiran Vodrahalli
# Date: Feb 7, 2013
# weather_scraper.py: Scrapes Princeton current temperature off weather.com
# using Python, BeautifulSoup, html5lib, urllib2, and re

#imports 
import html5lib
import urllib2
import re
from bs4 import BeautifulSoup

#get the html code from weather.com for Princeton
html = urllib2.urlopen("http://www.weather.com/weather/right-now/USNJ0427:1:US")

#find the part in the html code where it gives the weather
soup = BeautifulSoup(html, "html5lib")
report = soup.find_all("meta", content=re.compile("It's"))

#string operations to get as an integer
text = str(report[0])
nums = re.findall(r'\d+', text)
temperature = int(float(nums[0]))

print(temperature);


