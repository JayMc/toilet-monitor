/*

https://importhack.wordpress.com/2014/11/22/how-to-use-ep8266-esp-01-as-a-sensor-web-client/
ESP8622

RX    VCC
GPIO  ?
?    CH_PD
GND  TX


Connect
pin 10 to FTDI TX
pin 11 to FTDI RX

pin 0 to ESP8622 Tx
pin 1 to ESP8622 Rx

pin 3.3v to ESP8622 Vcc & CH_PD
pin GND to ESP8622 GND

Use CoolTerm connected to the FTDI to monitor the Serial commands

*/
#include "config.h"
#include <SoftwareSerial.h>

const char SSID[] = incSSID;
//#define SSID "boo" // your wifi ssid
const char PASS[] = incPASS;
//#define PASS = incPASS // your wifi password
const int lightThreshold = incLightThreshold;
bool roomLightState = false;
bool newRoomLightState = false;
#define DST_IP "192.168.1.107" // IOT Server IP
#define DST_PORT 7777 // IOT Server port
#define PIN_OFFSET 2 // how many pins to ignore, by default ignore first two (used for soft serial)
#define PIN_MAX 12 // up to what pin to watch
#define ERROR_LED 13 // LED to enable on startup error

SoftwareSerial dbgSerial(10, 11); // Debug Soft Serial RX, TX
int currentInputState;
int lastInputState[PIN_MAX + 1];

void setup()
{
        pinMode(A0, OUTPUT);
	pinMode(ERROR_LED, OUTPUT);
	Serial.begin(9600); // Works well
	Serial.setTimeout(5000);
	dbgSerial.begin(9600);
	dbgSerial.println("IOT Started...");

	for (int i = PIN_OFFSET; i <= PIN_MAX; i++){
  		pinMode(i, OUTPUT);
  		lastInputState[i] = -1;
	}

	if (!detectESP8266()){
		fail();
	}

	delay(500);

	boolean connected = false;
	for (int i = 0; i < 15; i++){
		if (connectToWiFi()){
			connected = true;
			break;
		}
	}
	if (!connected){ fail(); }

	delay(500);
	printIP();	
	Serial.println("AT+CIPMUX=0"); //set the single connection mode
}

void loop(){
        checkPins();
        delay(500);
}

void checkPins(){
        bool dataToSend = false;
        String data = "{";
  	/*for (int i = PIN_OFFSET; i <= PIN_MAX; i++){
		currentInputState = digitalRead(i);
		if (currentInputState != lastInputState[i]) {
                        if (data.length() > 1) data += ","; //if we already have data
                        data += "\"P";
                        data += i;
                        data += "\":";
                        data += currentInputState;
                        dataToSend = true;
                        lastInputState[i] = currentInputState;
		}
	}*/

        //get light level
        int roomVal = analogRead(A0);        
        dbgSerial.println(roomVal);  
        dbgSerial.println(lightThreshold);        
        if(roomVal > lightThreshold){
          newRoomLightState = true;
        }
        if(roomVal <= lightThreshold){
          newRoomLightState = false;
        }
        
        //check if light level has changed
        if(roomLightState != newRoomLightState){
          dbgSerial.println("light level changed");
          
          data += "\"A0";
          data += "\":";
          data += analogRead(A0);
          data += "}\r\n";          
          dataToSend = true;
          roomLightState = newRoomLightState;
        }

        //send data if there is anything to report on
        if(dataToSend) {
          sendData(data);
        }
}

boolean sendData(String data){
	String cmd = "AT+CIPSTART=\"TCP\",\"";
	cmd += DST_IP;
	cmd += "\",";
        cmd += DST_PORT;
	Serial.println(cmd);
	dbgSerial.println(cmd);
	if (Serial.find("ERROR")) {
  		dbgSerial.println("ERROR Sending data.");
                return false;
        }
	cmd = "POST / HTTP/1.0\r\nContent-Type:application/json \r\nConnection: close\r\n";
	cmd += "Content-Length: ";
	cmd += data.length();
	cmd += "\r\n\r\n";
	cmd += data;
	Serial.print("AT+CIPSEND=");
	Serial.println(cmd.length());
        delay(500);
	if (Serial.find(">")){
		dbgSerial.print(">");
	}else{
		Serial.println("AT+CIPCLOSE");
		dbgSerial.println("Connection timed out.");
		delay(500);
		return false;
	}
	Serial.print(cmd);
	/*delay(500);
	while (Serial.available())
	{
		char c = Serial.read();
		dbgSerial.write(c);
		if (c == '\r') dbgSerial.print('\n');
	}*/
	dbgSerial.println("Send Successful.");
        delay(1000);
	return true;
}

boolean connectToWiFi(){
	Serial.println("AT+CWMODE=1");
	String cmd = "AT+CWJAP=\"";
	cmd += SSID;
	cmd += "\",\"";
	cmd += PASS;
	cmd += "\"";
	dbgSerial.println(cmd);
	Serial.println(cmd);
	delay(3000);
	if (Serial.find("OK")){
		dbgSerial.println("Connected to WiFi.");
		return true;
	}else{
		dbgSerial.println("Failed to connect to WiFi.");
		return false;
	}
}

boolean detectESP8266(){
	Serial.println("AT+RST");
	delay(2000);
	if (Serial.find("OK")){
		dbgSerial.println("ESP8266 found...");
		return true;
	}else{
		dbgSerial.println("ESP8266 NOT found...");
		return false;
	}
}

void printIP(){
	Serial.println("AT+CIFSR");
	dbgSerial.println("ip address:");
	while (Serial.available())
		dbgSerial.write(Serial.read());
}

void fail(){
	digitalWrite(ERROR_LED, HIGH);
	while (1);
}
