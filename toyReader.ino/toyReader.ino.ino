/*
 * 
 * All the resources for this project: http://randomnerdtutorials.com/
 * Modified by Rui Santos
 * 
 * Created by FILIPEFLOP
 * 
 */
 
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
using namespace std;

String zero = "93 7E 29 1A";
String one = "7D FF 7D 9B";
String two = "CD BD 7D 9B";
String three = "DD C8 79 9B";
String four = "9D 8F FE 96";
String five = "6D EB 76 9B";
String six = "CD D6 7D 9B";
String seven = "8D 2B 75 9B";
String eight = "3D 87 79 9B";

String board[9] = {zero, one, two, three, four, five, six, seven, eight};

bool s = true;
bool s1 = true;
unsigned long t;

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(3, OUTPUT);
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  { 
    if (s){
      analogWrite(3, 128);
    }
    if (s1){
      t = millis();
      s1 = false;
    }
    if (millis() - t > 2000) {
      analogWrite(3, 0);
    }
    s = true;
    return;
  } else {
    s = false;
    s1 = true;
    analogWrite(3, 0);
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
//  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
//     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();

//  Serial.println();
  for (int i = 0; i < 9; i++){
    if(content.substring(1) == board[i]){
      Serial.print("In board position: ");
      Serial.print(i);
      Serial.println();
    }  
   }
 
} 
