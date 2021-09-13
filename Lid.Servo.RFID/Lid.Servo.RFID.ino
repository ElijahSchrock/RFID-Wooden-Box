#include <Servo.h> 
#include <SPI.h>
#include <MFRC522.h>
bool state;
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo LidServo;
void setup() 
{
  LidServo.attach(8);
  LidServo.write(180);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println();
  Serial.println();

}
void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "59 06 BF D4")
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(550);
  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }

 if (content.substring(1) == "59 06 BF D4");
  state =! state;
 if (state){
  LidServo.write(90);}
 else {LidServo.write(180);}
}
