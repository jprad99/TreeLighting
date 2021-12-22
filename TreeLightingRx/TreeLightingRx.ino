// Wireless
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = {'R', 'x', '6', 'F', '3'}; // CHANGE TO REFLECT MODULE ID
const byte channel = 108; // Above WiFi
const int relayPin = 3;

// Timing
long lastRx = 0;

void setup() {
  Serial.begin(9600);
  // Setup Relay
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Relays are to be (NC) configuration, BRANDS DIFFER
  // Start Radio
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX); // Max power
  //radio.setChannel(channel);
  //radio.setDataRate(RF24_250KBPS); // Lower rate, longer distance
  radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()) {
    char command[32] = "";
    radio.read(&command, sizeof(command));
    Serial.println(command);
    if(strcmp(command, "LightsOn")==0){ // if command is "LightsOn" we want the lights to turn on
      digitalWrite(relayPin, HIGH);
    }
    else if(strcmp(command, "LightsOff")==0){ // if command is "LightsOff" we want the lights to turn off
      digitalWrite(relayPin, LOW);
    }
    else {
      // ignore erroneous inputs
    }
  }
}
