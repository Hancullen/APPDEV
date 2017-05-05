https://github.com/Hancullen/APPDEV
# This is my README file 
-------------------------------------
	Acoustic Sensor using Rpi3
-------------------------------------

1.Configuration Instructions 

This section contains 2 parts: hardware configuration and software configuration.

1.1 Hardware configuration

	This project is built on a Raspberry pi3, with a USB sound card and a microphone.
	Ethernet connection is recommended. 
	If an older version of Raspberry Pi is used,certain change might be necessary.

1.2 Software configuration

	You have to set USB sound card as default audio device
	- Use "lsub" command to check if USB sound card is mounted
	- Use "sudo nano /etc/asound.conf" and "nano .asoundrc" and
	  put the following contents:
		pcm.!default{
			type plug
			slave{
				pcm "hw:1,0"
			}
		}
		ctl.!default{
			type hw
			card 1
		}
	- Run "alsamixer" to check if the USB sound card is the default device
	If you are using Raspbian Jessie, you have to roll back alsa-utils to an earlier version.
        - Use "sudo nano /etc/apt/sources.list" command and add the last line:

 		deb http://mirrordirector.raspbian.org/raspbian/ jessie main contrib non-free rpi
 		# Uncomment line below then 'apt-get update' to enable 'apt-get source'
 		#deb-src http://archive.raspbian.org/raspbian/ jessie main contrib non-free rpi
 		deb http://mirrordirector.raspbian.org/raspbian/ wheezy main contrib non-free rpi

 	- Run "sudo apt-get update"
 	- Run "sudo aptitude versions alsa-utils" to check if version 1.0.25 of alsa-util is available:
 	- Run "sudo apt-get install alsa-utils=1.0.25-4" to downgrade
 	- Reboot(if neccesary)

2.Installation Instructions

	Download all source from Github and store in one directory
	Open terminal and change directory to source code folder
	Use command "make" to compile and link all the source code
	Change terminal to "UTF-8"

3.Operation Instructions

	Run "./wave.a" to run the program. 
	You will see a screen with many vertical bars and information of duration,
	bits per sample, and sample rate.

	To stop the program: Ctrl+C

4.Files included in this project: main.c wave.h wave.c comm.h comm.c 
				  screen.h screen.c makefile and README.md

5.Credit and acknowledgment
	Programmer: Nguyen Linh
	Instructor: Dr.Gao Chao(VAMK)
