# toilet-monitor

# Includes:
	- Hardware code - Arduino
	- Server code - Node.js with Express
	- Fronend - AngularJS 1.3


# Components:

## IOT device
 - Arduino ATmega 328 (http://arduino.cc/en/Main/arduinoBoardUno)
 - ESP8266 (http://hackaday.com/tag/esp8266/)(https://github.com/esp8266/esp8266-wiki)

## Server (for IOT device and serving Angular)
Acts as a relay between IOT device and Firebase Database service. This is required as the Arduino only has a small memory space. Adding a Firebase library (websockets) or an HTTPS library (for POST requests) maybe an option

Firebase: https://www.firebase.com

## Frontend TODO
Angular (1.3) provides frontend with 

AngularJS http://angularjs.org

## Android TODO
Ionic with Android and Firebase library


# IOT Traffic
Arduino  >--HTTP POST data--> Node.js Server <--Websocket--> Firebase

# Client Traffic
Browser/Android Client <--Websocket--> Firebase

Client Downloads Angular Frontend once at begining of visit from Node.js Server