#Blake Lufkin
#Script opens RPi expansion board and sends a
#character to the board to recieve data then inserts the data 
#into an sqlite3 database called hat.db and a table called hatdata.
#
#This script is to be called by a cronjob that executes the script
#every minute
#Last Updated: 4/28/2020
#! /usr/bin/python

import serial
import time
import datetime
import re
import sqlite3

#Acquire data from expansion board
ser = serial.Serial(
	port='/dev/ttyAMA0',
	baudrate=19200,
	parity=serial.PARITY_NONE,
	stopbits=serial.STOPBITS_ONE,
	bytesize=serial.EIGHTBITS
)

ser.isOpen()

#Send any character to retrieve data
ser.write('T')

#Allow time to retrieve data
time.sleep(1)

#read in entire line
out = ser.readline()

ser.close()

#Acquire current date and time
date_time=datetime.datetime.today().strftime('%Y-%m-%d %H:%M:%S')

#Parse acquired data using regular expressions
out = out.replace(' |','')

p=re.search(r'([0-9]+\.[0-9]+) ([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+) ([0-9]+)',out)

#Cast the captured strings to the types to be passed
hres=float(p.group(1))
ir=int(p.group(2))
fsi=int(p.group(3))
vli=int(p.group(4))
illum=int(p.group(5))
centC=int(p.group(6))
pressure=int(p.group(7))
humid=int(p.group(8))

m=re.search(r'([0-9]+\-[0-9]+\-[0-9]+) ([0-9]+\:[0-9]+\:[0-9]+)',date_time)
date = m.group(1)
time = m.group(2)

#make a list of data values to pass to sqlite3 execute
data = (date,time,hres,ir,fsi,vli,illum,centC,pressure,humid)

#insert data into the table in the database
conn = sqlite3.connect('hat.db')
c=conn.cursor()

#Insert data into database
c.execute("INSERT INTO hatdata (date,time,hrestemp,ir,fsi,vli,illum,centC,pressure,humid) VALUES (?,?,?,?,?,?,?,?,?,?)",data)

#Only keep data from the last 24 hrs
c.execute("DELETE FROM hatdata WHERE ROWID IN(SELECT ROWID FROM hatdata ORDER BY ROWID DESC LIMIT -1 OFFSET 1440)")

#Submission and cleanup
conn.commit()
conn.close()

