#include <SoftwareSerial.h>
//#include<ESP8266WiFi.h>;
#include <Adafruit_Fingerprint.h>
#include <ArduinoBlue.h>
#define mySerial Serial1
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
SoftwareSerial bluetooth(2, 3);
ArduinoBlue phone(bluetooth);
int x=4;

void setup() {
  pinMode(x,OUTPUT);
  Serial.begin(9600);
  while (!Serial); delay(100);  //or {;} instead of delay
  finger.begin(57600); delay(5);
  bluetooth.begin(9600); delay(100);
  if (finger.verifyPassword()) { Serial.println("found sensor :)"); }
  else { Serial.println("shit happens :("); while (1) { delay(1); } }
  Serial.println(F("identifying...")); //F() macro moves this stuff into FLASH instead of sRAM
  finger.getTemplateCount();
  if (finger.templateCount == 0) { Serial.print("enroll prints"); }
  else { Serial.print(finger.templateCount); Serial.println(" prints on sensor"); } 
}

void loop() {
  getFingerprintID(); delay(50); 
  int button = phone.getButton();
  if (button == 0) {digitalWrite(x, HIGH);delay(700);digitalWrite(x, LOW);}
}

uint8_t getFingerprintID() {       // int8_t is char .  byte is uint8_t is unsigned char .
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK: Serial.println("Image taken"); break;
    case FINGERPRINT_NOFINGER: return p;
    case FINGERPRINT_PACKETRECIEVEERR: Serial.println("Communication error"); return p;
    case FINGERPRINT_IMAGEFAIL: Serial.println("Imaging error"); return p;
    default: Serial.println("Unknown error"); return p; }
  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK: Serial.println("Image converted"); break;
    case FINGERPRINT_IMAGEMESS: Serial.println("Image too messy"); return p;
    case FINGERPRINT_PACKETRECIEVEERR: Serial.println("Communication error"); return p;
    case FINGERPRINT_FEATUREFAIL: Serial.println("Could not find fingerprint features"); return p;
    case FINGERPRINT_INVALIDIMAGE: Serial.println("Could not find fingerprint features"); return p;
    default: Serial.println("Unknown error"); return p; }
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) { Serial.println("Found a print match!"); } 
  else if (p == FINGERPRINT_PACKETRECIEVEERR) { Serial.println("Communication error"); return p; } 
  else if (p == FINGERPRINT_NOTFOUND) { Serial.println("no match"); return p; } 
  else { Serial.println("Unknown error"); return p; }
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  digitalWrite(x, HIGH);delay(700);digitalWrite(x, LOW);
  return finger.fingerID; 
}

int getFingerprintIDez() {     // returns -1 if failed or ID when success
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}
