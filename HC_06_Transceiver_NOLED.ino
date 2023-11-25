/*
 * Ng Khai Le
 * Complete Project Details https://www.hackster.io/khaileng0428/the-saveguard-cane-9024cd 
 * 
 *
 * SGuard Contorller source code
 * Build2gather competition
 * Licensed to Faculty of Engineering & Information Techonology, Southern University College
 *

 */

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 11, TXPin = 12;
static const uint32_t GPSBaud = 9600;

const int buzzer = 6;
const int interruptPin_contact = 2;
volatile int contact = 0;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

// notes in the melody:
int melody[] = {
  262, 196, 196, 220, 196, 0, 247, 262
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void emergency_contact(){
  contact = 1;
  ss.print("S");
  ss.print(gps.location.lat(), 6);  
  ss.print(",");  
  ss.print(gps.location.lng(), 6); 
  ss.print(","); 
  ss.print(gps.date.year()); 
  ss.print(","); 
  ss.print(gps.date.month()); 
  ss.print(",");
  ss.print(gps.date.day()); 
  ss.print(",");
  ss.print(gps.time.hour()); 
  ss.print(",");
  ss.print(gps.time.minute()); 
  ss.print(",");
  ss.print(gps.time.second()); 
  ss.print(",");
  ss.print(contact); 
  ss.println("E");

  Serial.print("S"); 
  Serial.print(gps.location.lat(), 6);  
  Serial.print(",");  
  Serial.print(gps.location.lng(), 6); 
  Serial.print(","); 
  Serial.print(gps.date.year()); 
  Serial.print(","); 
  Serial.print(gps.date.month()); 
  Serial.print(",");
  Serial.print(gps.date.day()); 
  Serial.print(",");
  Serial.print(gps.time.hour()); 
  Serial.print(",");
  Serial.print(gps.time.minute()); 
  Serial.print(",");
  Serial.print(gps.time.second()); 
  Serial.print(",");
  Serial.print(contact); 
  Serial.println("E"); 
  contact = 0;
}

void setup(){
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzer, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzer);
  }
  Serial.begin(9600);
  ss.begin(GPSBaud);
  attachInterrupt(digitalPinToInterrupt(interruptPin_contact), emergency_contact, RISING);
}


void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
  if (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      ss.print("S");
      ss.print(gps.location.lat(), 6);  
      ss.print(",");  
      ss.print(gps.location.lng(), 6); 
      ss.print(","); 
      ss.print(gps.date.year()); 
      ss.print(","); 
      ss.print(gps.date.month()); 
      ss.print(",");
      ss.print(gps.date.day()); 
      ss.print(",");
      ss.print(gps.time.hour()); 
      ss.print(",");
      ss.print(gps.time.minute()); 
      ss.print(",");
      ss.print(gps.time.second()); 
      ss.print(",");
      ss.print(contact); 
      ss.println("E");

      Serial.print("S");
      Serial.print(gps.location.lat(), 6);  
      Serial.print(",");  
      Serial.print(gps.location.lng(), 6); 
      Serial.print(","); 
      Serial.print(gps.date.year()); 
      Serial.print(","); 
      Serial.print(gps.date.month()); 
      Serial.print(",");
      Serial.print(gps.date.day()); 
      Serial.print(",");
      Serial.print(gps.time.hour()); 
      Serial.print(",");
      Serial.print(gps.time.minute()); 
      Serial.print(",");
      Serial.print(gps.time.second()); 
      Serial.print(",");
      Serial.print(contact); 
      Serial.println("E");
      delay(1100);
    }
  }
}
