#!/usr/bin/env python
 
"""XBeeModem.py bypasses the XBee's 802.15.4 capabilities and simply uses it modem for communications
 
    You don't have to master 802.15.4 and a large set of XBee commands
    to make a very simple but potentially useful network.  At its core,
    the XBee radio is  a modem and you can use it directly for simple serial communications.
 
    Reference Materials:
        Non-blocking read from stdin in python - http://repolinux.wordpress.com/2012/10/09/non-blocking-read-from-stdin-in-python/
        Non-blocking read on a subprocess.PIPE in python - http://stackoverflow.com/questions/375427/non-blocking-read-on-a-subprocess-pipe-in-python
 
    Originally Created By:
        Jeff Irland (jeff.irland@gmail.com) in March 2013
"""
import RPi.GPIO as GPIO
import serial
import sys
import time
import subprocess
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(18,GPIO.OUT) 
GPIO.setup(16,GPIO.OUT) 
GPIO.setup(15,GPIO.OUT) 

# imported modules
import os                   # portable way of using operating system dependent functionality
import sys                  # provides access to some variables used or maintained by the interpreter
import time                 # provides various time-related functions
import fcntl                # performs file control and I/O control on file descriptors
import serial               # encapsulates the access for the serial port
#from pretty import switchColor, printc  # provides colored text for xterm & VT100 type terminals using ANSI escape sequences

if __name__ == '__main__':
    serial = serial.Serial()
    serial.port = '/dev/ttyUSB0'
    serial.baudrate = 9600
    serial.timeout = 1
    serial.writeTimeout = 1
    serial.open()
 
    # make stdin a non-blocking file
    fcntl.fcntl(sys.stdin, fcntl.F_SETFL, os.O_NONBLOCK)
 
    # post startup message to other XBee's and at stdout
    serial.writelines("RPi #1 is up and running.\r\n")
    print "RPi #1 is up and running."
 
    #switchColor(CMD_OUTPUT_TEXT)
    print "Entering loop to read and print messages (Ctrl-C to abort)..."
 
    try:
        while True:
            # read a line from XBee and convert it from b'xxx\r\n' to xxx and print at stdout
            #switchColor(TERM_OUTPUT_TEXT)
	    
            line = serial.readline().decode('utf-8')
            if line:
                line=line.split('\n')[0]
		print line
		user=line.split(' ')[0].split('=')[1]
		humidity=line.split(' ')[1].split('=')[1]
		temperature=line.split(' ')[2].split('=')[1]
		gas=line.split(' ')[3].split('=')[1]
		
		print humidity
		print temperature
		print user
#User entry exit status
		
		if user =='1':
                        print "hello........"
                        subprocess.call(['bash','user.sh'])
                        

#Buzzer for humidity sensor
		if humidity>'65.00' and  temperature>'23.00':
			
			GPIO.output(18,GPIO.HIGH)
			#print "Enter the password"
			
			subprocess.call(['bash','humidity.sh'])
		else: 
			GPIO.output(18,GPIO.LOW)
#Buzzer and LED for Gas sensor
		if gas > '400':
 			GPIO.output(16,GPIO.LOW)
			GPIO.output(15,GPIO.HIGH)
			time.sleep(0.2)
			GPIO.output(15,GPIO.LOW)
			time.sleep(0.2)
			GPIO.output(15,GPIO.HIGH)
			time.sleep(0.2)
			GPIO.output(15,GPIO.LOW)
			subprocess.call(['bash','gas.sh'])

		else:
			GPIO.output(16,GPIO.HIGH)
			GPIO.output(15,GPIO.LOW)
            # read data from the keyboard (i.e. stdin) and send via the XBee modem
            #switchColor(TERM_INPUT_TEXT)
            try:
                line = sys.stdin.readline()
                serial.writelines(line)
            except IOError:
                time.sleep(0.1)
                continue
 
    except KeyboardInterrupt:
        printc("\n*** Ctrl-C keyboard interrupt ***", ERROR_TEXT)
        serial.writelines("RPi #1 is going down.\r\n")
 
    #finally:
        #switchColor(CMD_INPUT_TEXT) 