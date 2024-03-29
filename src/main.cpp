#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
boolean successfullyReadtheFirstCard = false;

#define GREENLEDPIN 7
#define WHITELED1PIN 2
#define WHITELED2PIN 3
#define WHITELED3PIN 4
#define WHITELED4PIN 8
#define WHITELED5PIN 6
#define WHITELED6PIN 5
#define WHITELED7PIN A3
#define WHITELED8PIN A5
#define WHITELED9PIN A4

boolean card1Read = false;
boolean card2Read = false;
boolean card3Read = false;
boolean bone1Read = false;
boolean bone2Read = false;
boolean bone3Read = false;

unsigned long greenLEDDuration = 500;
unsigned long whiteLEDDuration = 500;

unsigned long greenLEDTurnedOnTime = 0;
unsigned long whiteLED1TurnedOnTime = 0;
unsigned long whiteLED2TurnedOnTime = 0;
unsigned long whiteLED3TurnedOnTime = 0;
unsigned long whiteLED4TurnedOnTime = 0;
unsigned long whiteLED5TurnedOnTime = 0;
unsigned long whiteLED6TurnedOnTime = 0;
unsigned long whiteLED7TurnedOnTime = 0;
unsigned long whiteLED8TurnedOnTime = 0;
unsigned long whiteLED9TurnedOnTime = 0;

boolean greenLEDIsOn = false;
boolean whiteLED1IsOn = false;
boolean whiteLED2IsOn = false;
boolean whiteLED3IsOn = false;
boolean whiteLED4IsOn = false;
boolean whiteLED5IsOn = false;
boolean whiteLED6IsOn = false;
boolean whiteLED7IsOn = false;
boolean whiteLED8IsOn = false;
boolean whiteLED9IsOn = false;

String card1ID = "74 ED DB 03";
String card2ID = "E4 BD D1 03";
String card3ID = "74 67 0E 04";
String bone1ID = "A1 21 13 1D";
String bone2ID = "91 D4 35 1D";
String bone3ID = "A1 5B EE 1D";

// this function checks to see if there is a card to be read (true or false)
boolean thereIsACard()
{
  // if there's a card and it can be read...
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())
  {
    return true;
  } else { // no card was present or it couldn't be read
    return false;
  }
}

// this function returns the uppercase ID of the card being read, as a String
String returnCardID()
{
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  return content.substring(1);
}

void setup()
{
  pinMode(GREENLEDPIN, OUTPUT);
  pinMode(WHITELED1PIN, OUTPUT);
  pinMode(WHITELED2PIN, OUTPUT);
  pinMode(WHITELED3PIN, OUTPUT);
  pinMode(WHITELED4PIN, OUTPUT);
  pinMode(WHITELED5PIN, OUTPUT);
  pinMode(WHITELED6PIN, OUTPUT);
  pinMode(WHITELED7PIN, OUTPUT);
  pinMode(WHITELED8PIN, OUTPUT);
  pinMode(WHITELED9PIN, OUTPUT);

  Serial.begin(9600); // Initiate a serial communication
  SPI.begin();        // Initiate  SPI bus
  mfrc522.PCD_Init(); // Initiate MFRC522
  Serial.println("Ready");
}

void loop()
{
  // skip the rest of the loop if there isn't a card to read
  if (thereIsACard() == false) return;

  // read the ID of the card into the "cardID" variable
  String readID = returnCardID();

  // deal with reading CARDs
  if (readID.equals(card1ID)) {
    card1Read = true;
    digitalWrite(GREENLEDPIN,HIGH);
    greenLEDIsOn = true;
    greenLEDTurnedOnTime = millis();
  }
  if (readID.equals(card2ID)) {
    card2Read = true;
    digitalWrite(GREENLEDPIN,HIGH);
    greenLEDIsOn = true;
    greenLEDTurnedOnTime = millis();
  }
  if (readID.equals(card3ID)) {
    card3Read = true;
    digitalWrite(GREENLEDPIN,HIGH);
    greenLEDIsOn = true;
    greenLEDTurnedOnTime = millis();
  }

  // turn off green LED if necessary
  if (greenLEDIsOn && millis() - greenLEDTurnedOnTime >= greenLEDDuration) {
    digitalWrite(GREENLEDPIN, LOW);
    greenLEDIsOn = false;
  }

  // check the bones
  if (readID.equals(bone1ID)) { // bone 1
    if (card1Read) {
      digitalWrite(WHITELED1PIN, HIGH);
      whiteLED1IsOn = true;
      whiteLED1TurnedOnTime = millis();
      card1Read = false;
    }
    if (card2Read) {
      digitalWrite(WHITELED4PIN, HIGH);
      whiteLED4IsOn = true;
      whiteLED4TurnedOnTime = millis();
      card2Read = false;
    }
    if (card3Read) {
      digitalWrite(WHITELED7PIN, HIGH);
      whiteLED7IsOn = true;
      whiteLED7TurnedOnTime = millis();
      card3Read = false;
    }
  }
  if (readID.equals(bone2ID)) { // bone 2
    if (card1Read) {
      digitalWrite(WHITELED2PIN, HIGH);
      whiteLED2IsOn = true;
      whiteLED2TurnedOnTime = millis();
      card1Read = false;
    }
    if (card2Read) {
      digitalWrite(WHITELED5PIN, HIGH);
      whiteLED5IsOn = true;
      whiteLED5TurnedOnTime = millis();
      card2Read = false;
    }
    if (card3Read) {
      digitalWrite(WHITELED8PIN, HIGH);
      whiteLED8IsOn = true;
      whiteLED8TurnedOnTime = millis();
      card3Read = false;
    }
  }
  if (readID.equals(bone3ID)) { // bone 3
    if (card1Read) {
      digitalWrite(WHITELED3PIN, HIGH);
      whiteLED3IsOn = true;
      whiteLED3TurnedOnTime = millis();
      card1Read = false;
    }
    if (card2Read) {
      digitalWrite(WHITELED6PIN, HIGH);
      whiteLED6IsOn = true;
      whiteLED6TurnedOnTime = millis();
      card2Read = false;
    }
    if (card3Read) {
      digitalWrite(WHITELED9PIN, HIGH);
      whiteLED9IsOn = true;
      whiteLED9TurnedOnTime = millis();
      card3Read = false;
    }
  }

  // turn off any white LEDs if necessary
  if (whiteLED1IsOn && millis() - whiteLED1TurnedOnTime >= whiteLEDDuration) {
    digitalWrite(WHITELED1PIN, LOW);
    whiteLED1IsOn = false;
  }
  if (whiteLED2IsOn && millis() - whiteLED2TurnedOnTime >= whiteLEDDuration) {
    digitalWrite(WHITELED2PIN, LOW);
    whiteLED2IsOn = false;
  }
  if (whiteLED3IsOn && millis() - whiteLED3TurnedOnTime >= whiteLEDDuration) {
    digitalWrite(WHITELED3PIN, LOW);
    whiteLED3IsOn = false;
  }
  if (whiteLED4IsOn && millis() - whiteLED4TurnedOnTime >= whiteLEDDuration) {
    digitalWrite(WHITELED4PIN, LOW);
    whiteLED4IsOn = false;
  }
  if (whiteLED5IsOn && millis() - whiteLED5TurnedOnTime >= whiteLEDDuration) {
    digitalWrite(WHITELED5PIN, LOW);
    whiteLED5IsOn = false;
  }
  if (whiteLED6IsOn && millis() - whiteLED6TurnedOnTime >= whiteLEDDuration) {
    digitalWrite(WHITELED6PIN, LOW);
    whiteLED6IsOn = false;
  }
  if (whiteLED7IsOn && millis() - whiteLED7TurnedOnTime >= whiteLEDDuration) {
    digitalWrite(WHITELED7PIN, LOW);
    whiteLED7IsOn = false;
  }
  if (whiteLED8IsOn && millis() - whiteLED8TurnedOnTime >= whiteLEDDuration) {
    digitalWrite(WHITELED8PIN, LOW);
    whiteLED8IsOn = false;
  }
  if (whiteLED9IsOn && millis() - whiteLED9TurnedOnTime >= whiteLEDDuration) {
    digitalWrite(WHITELED9PIN, LOW);
    whiteLED9IsOn = false;
  }


}