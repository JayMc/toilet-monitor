# toilet-monitor

# Includes:
	- Hardware code - Arduino
	- Server code - Node.js with Express
	- Frontend - AngularJS 1.3
	- Phone app - Ionic


# Components:

## IOT device
 - Arduino ATmega 328 (http://arduino.cc/en/Main/arduinoBoardUno)
 - ESP8266 (http://hackaday.com/tag/esp8266/)(https://github.com/esp8266/esp8266-wiki)

## Server (for IOT device and serving Angular)
Acts as a relay between IOT device and Firebase database service. This is required as the Arduino only has a small memory space. Adding a Firebase library (websockets) or an HTTPS library (for Firebase POST requests) maybe an option but uses valuable space

node app.js

Firebase: https://www.firebase.com

## Frontend TODO
Angular (1.3) provides frontend with 

AngularJS http://angularjs.org

## Android TODO
Ionic with Android and Firebase library

To start ionic server Android/toilet-monitor/ionic serve

# IOT Traffic
Arduino  >--HTTP POST data--> Node.js Server <--Websocket--> Firebase

# Client Traffic
Browser/Android Client <--Websocket--> Firebase

Client Downloads Angular Frontend once at begining of visit from Node.js Server

# Start dev
 - npm install
 - cd Android/toilet-monitor
 - bower install

# Future ideas

	- Tweets
	- 2-way communication via websockets with IOT
		- LED matrix control (leads to colabritive games and drawing)
		- play music

