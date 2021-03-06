#include <Wire.h>
#define SLAVE_ADDRESS 0x04

int number = 0;
int state = 0;
void setup() {
	pinMode(8, OUTPUT);
	Serial.begin(9600); // start serial for output
	// initialize i2c as slave
	Wire.begin(SLAVE_ADDRESS);
	// define callbacks for i2c communication
	Wire.onReceive(receiveData);
	Wire.onRequest(sendData);
	Serial.println("Ready!");
}
void loop() {
	delay(100);
}

// callback for received data
void receiveData(int byteCount) {
	while (Wire.available()) {
		number = Wire.read();
		Serial.print("data received: ");
		Serial.println(number);
		if (state == 0) {
			digitalWrite(8, LOW);
			state = 1;
		}
		else {
			digitalWrite(8, HIGH);
			state = 0;
		}
	}
}
// callback for sending data
void sendData() {
	Wire.write(number + 1);
}
