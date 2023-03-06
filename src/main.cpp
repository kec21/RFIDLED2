
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
boolean successfullyReadtheFirstCard = false;

#define GREENLEDPIN 13
#define WHITELED1PIN
#define WHITELED2PIN
#define WHITELED3PIN
#define WHITELED4PIN
#define WHITELED5PIN
#define WHITELED6PIN
#define WHITELED7PIN
#define WHITELED8PIN
#define WHITELED9PIN 

boolean card1Read = false;
boolean card2Read = false;
boolean card3Read = false;
boolean bone1Read = false;
boolean bone2Read = false;
boolean bone3Read = false;

String card1ID = "74 ED D8 03";
String card2ID = "E4 BD D1 03";
String card3ID = "74 67 0E 04";
String bone1ID = "A1 21 13 1D";
String bone2ID = "91 D4 35 1D";
String bone3ID = "A1 SB EE 1D";

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

void turnOffOldLEDs() {
  if (millis() - LED1OnTimestamp >= LEDTimeLimit) {
    digitalWrite(LED1Pin, LOW);
  }
  /*
  if (millis() - LED2OnTimestamp >= LEDTimeLimit) {
    digitalWrite(LED2Pin, LOW);
  }
  */
}

void setup()
{
  pinMode(LED1Pin, OUTPUT);
  Serial.begin(9600); // Initiate a serial communication
  SPI.begin();        // Initiate  SPI bus
  mfrc522.PCD_Init(); // Initiate MFRC522
  Serial.println("Ready");
}

void loop()
{
  // skip the rest of the loop if there isn't a card to read
  if (thereIsACard() == false)
    return;

  // read the ID of the card into the "cardID" variable
  String cardID = returnCardID();

  //Serial.print("x");
  //Serial.print(cardID);
  //Serial.println("x");
  
  if (cardID == "74 ED DB 03" && card1Read ==false) {
    card1Read = true;
    Serial.println("Read Card1!");
  }
  else if (cardID == "A1 21 13 1D" && card2Read == false && card1Read == true) {
    card2Read = true;
    Serial.println("Read Card2!");
 }
  // else if (cardID == "74 67 0E 04" && card3Read == false) {
  //   card3Read = true;
  //   Serial.println("Read Card3!");
  // }

  // if (cardID == "" && card2Read == true)
  // {
  //   Serial.println("card 1 was read, followed by card A!");
  //   digitalWrite(LED1Pin, HIGH);
  //   LED1OnTimestamp = millis();
  // }

  // //turnOffOldLEDs();
}