#include <SoftwareSerial.h>
#define rxPin 0 // Broche 0 en tant que RX, à raccorder sur TX du HC-05
#define txPin 1 // Broche 1 en tant que TX, à raccorder sur RX du HC-05
#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_NeoPixel.h>
#define RST_PIN         9          
#define SS_PIN          10          
#include <stdlib.h>
#define NR_KNOWN_KEYS   8
#define CW  0// CCW marche arrière
#define CCW 1 // CW marche avant
#define MOTOR_A 0 // moteur droit
#define MOTOR_B 1 // moteur gauche (sens du véhicule)
// Pin Assignments //
// Don't change these! These pins are statically defined by shield layout
const byte PWMA = 3;  // PWM control (speed) for motor A
const byte PWMB = 5 ; // PWM control (speed) for motor B
const byte DIRA = 6; // Direction control for motor A
const byte DIRB = 7; // Direction control for motor B






// Known keys
byte knownKeys[NR_KNOWN_KEYS][MFRC522::MF_KEY_SIZE] =  {
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}, // FF FF FF FF FF FF = factory default
    {0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5}, // A0 A1 A2 A3 A4 A5
    {0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5}, // B0 B1 B2 B3 B4 B5
    {0x4d, 0x3a, 0x99, 0xc3, 0x51, 0xdd}, // 4D 3A 99 C3 51 DD
    {0x1a, 0x98, 0x2c, 0x7e, 0x45, 0x9a}, // 1A 98 2C 7E 45 9A
    {0xd3, 0xf7, 0xd3, 0xf7, 0xd3, 0xf7}, // D3 F7 D3 F7 D3 F7
    {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff}, // AA BB CC DD EE FF
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}  // 00 00 00 00 00 00
};






// Bluetooth Serial connection to mobile
SoftwareSerial bthSerial(rxPin, txPin);


// Arduino Pin connected to Neopixel
int NEOPIN = 2;


// Number of LEDs on Neopixel
int NUMPIXELS = 12;


// Global variable for the Neopixel
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);


// Create MFRC522 instance.
MFRC522 mfrc522(SS_PIN, RST_PIN);  
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;


String read_msg; // for incoming serial data


int counter = 0;


String message ="";
int k = 0 ;
String indication ;
char messagelu ;
int vitesse ;
String dir;
String vitesselue;
int pattern = 0;
String lights = "on";


byte base_color[] = {0,0,32,32,32,0};


void setup()
{
  // define pin modes for tx, rx pins:
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  bthSerial.begin(9600);
  Serial.begin(9600);
  setupArdumoto();


  SPI.begin();                // Init SPI bus
  mfrc522.PCD_Init();         // Init MFRC522 card
  pixels.begin();
}


void monochrom(byte r, byte g,byte b) {
  for (byte i=0; i<12; i++) {
    pixels.setPixelColor(i,pixels.Color(r,g,b));
  }
  pixels.show();
}
// One of the two moving patterns used by badge 1
void light1(byte *buffer, int i) {
  for (byte j=0;j<3;j++) {
    pixels.setPixelColor((4*j + i) % 12, pixels.Color(buffer[0],buffer[1],buffer[2]));
    pixels.setPixelColor((4*j + 1 + i) % 12, pixels.Color(buffer[0],buffer[1],buffer[2]));
    pixels.setPixelColor((4*j + 2 + i) % 12, pixels.Color(buffer[3],buffer[4],buffer[5]));
    pixels.setPixelColor((4*j + 3 + i) % 12, pixels.Color(buffer[3],buffer[4],buffer[5]));
  }
  pixels.show();
 
}
// Moving pattern used when badge is identified and name is shown
void light2(byte *buffer) {
    pixels.clear();
    for (byte i=0; i<16; i++) {    
          if (i<12) {
            pixels.setPixelColor(i, pixels.Color(buffer[3],buffer[4],buffer[5]));
          } else {
            if (i < 14 ) {
            pixels.clear();
          } else {
            monochrom(buffer[0],buffer[1],buffer[2]);
          }
        }
    pixels.show();
    delay(125);
    }
}
// One of the two moving patterns used by badge 2
void light3(byte *buffer, int i) {
  for (byte j=0;j<3;j++) {
    pixels.setPixelColor(11 - ((4*j + i) % 12), pixels.Color(buffer[0],buffer[1],buffer[2]));
    pixels.setPixelColor(11 - ((4*j + i + 1) % 12), pixels.Color(buffer[0],buffer[1],buffer[2]));
    pixels.setPixelColor(11 - ((4*j + i + 2) % 12), pixels.Color(buffer[3],buffer[4],buffer[5]));
    pixels.setPixelColor(11 - ((4*j + i + 3) % 12), pixels.Color(buffer[3],buffer[4],buffer[5]));
  }
  pixels.show();
 
}
// Second moving pattern used by badge 1
void light4(byte *buffer, int i) {
    monochrom(buffer[0],buffer[1],buffer[2]);
    pixels.setPixelColor(i % 12, pixels.Color(buffer[3],buffer[4],buffer[5]));
    pixels.setPixelColor((i + 4)% 12, pixels.Color(buffer[3],buffer[4],buffer[5]));
    pixels.setPixelColor((i + 8) % 12, pixels.Color(buffer[3],buffer[4],buffer[5]));
     
    pixels.show();
}
void light5(byte *buffer, int i) {
    pixels.setPixelColor(11 - (i % 12), pixels.Color(buffer[3],buffer[4],buffer[5]));
    pixels.setPixelColor(11 - ((i + 4)% 12), pixels.Color(buffer[3],buffer[4],buffer[5]));
    pixels.setPixelColor(11 - ((i + 8) % 12), pixels.Color(buffer[3],buffer[4],buffer[5]));
     
    pixels.show();
}


void rainbow(int i, float intensity) {
 
    pixels.setPixelColor(i % 12, pixels.Color(128*intensity,0,0));
    pixels.setPixelColor((i + 1) % 12, pixels.Color(98*intensity,32*intensity,0));
    pixels.setPixelColor((i + 2) % 12, pixels.Color(64*intensity,64*intensity,0));
    pixels.setPixelColor((i + 3) % 12, pixels.Color(32*intensity,98*intensity,0));
    pixels.setPixelColor((i + 4) % 12, pixels.Color(0,128*intensity,0));
    pixels.setPixelColor((i + 5) % 12, pixels.Color(0,98*intensity,32*intensity));
    pixels.setPixelColor((i + 6) % 12, pixels.Color(0,64*intensity,64*intensity));
    pixels.setPixelColor((i + 7) % 12, pixels.Color(0,32*intensity,98*intensity));
    pixels.setPixelColor((i + 8) % 12, pixels.Color(0,0,128*intensity));
    pixels.setPixelColor((i + 9) % 12, pixels.Color(32*intensity,0,98*intensity));
    pixels.setPixelColor((i + 10) % 12, pixels.Color(64*intensity,0,64*intensity));
    pixels.setPixelColor((i + 11) % 12, pixels.Color(98*intensity,0,32*intensity));
   
    pixels.show();
}


void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == MOTOR_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if (motor == MOTOR_B)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }  
}
// stopArdumoto makes a motor stop
void stopArdumoto(byte motor)
{
  driveArdumoto(motor, 0, 0);
}
// setupArdumoto initialize all pins
void setupArdumoto()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);




  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}
void avancer(int vitesse){
  driveArdumoto(MOTOR_A, CW, vitesse -5); // Set motor A to CCW at ma
  driveArdumoto(MOTOR_B, CW, vitesse);
}
void reculer(int vitesse){
  driveArdumoto(MOTOR_A, CCW, vitesse -5); // Set motor A to CCW at ma
  driveArdumoto(MOTOR_B, CCW, vitesse);
}
void tourneradroite(){
  driveArdumoto(MOTOR_A, CCW, 90);
  driveArdumoto(MOTOR_B, CW, 90);
}
void tourneragauche(){
  driveArdumoto(MOTOR_A, CW, 90);
  driveArdumoto(MOTOR_B, CCW, 90);
}
void arreter(){
  stopArdumoto(MOTOR_A);
  stopArdumoto(MOTOR_B);
}




void loop() {
  delay(10);
  // Block to read data on
  byte reading_block = 20;
  // Block to write data on
  byte writing_block = 0;


  while (bthSerial.available() > 0){
    /** messagelu= bthSerial.read();
    Serial.println(messagelu);*/
    for (int t=0 ; t<3; t++){
      messagelu= bthSerial.read();
      indication = indication + messagelu;
      delay(50);
    }
    
    if (indication.equals("dir")){
      for (int t=0 ; t<3; t++){
        messagelu=bthSerial.read();
        dir=dir+messagelu;
        delay(50);
      }
      if (dir.equals("dev")){
        for (int t=0 ; t<3; t++){
          messagelu=bthSerial.read();
          vitesselue = vitesselue + messagelu ;
        }
        vitesse = vitesselue.toInt();
        avancer(vitesse);
        delay(50);
      }
      if (dir.equals("der")){
        for (int t=0 ; t<3; t++){
          messagelu=bthSerial.read();
          vitesselue = vitesselue + messagelu ;
        }
        vitesse = vitesselue.toInt();
        reculer(vitesse);
        delay(50);
      }
      if (dir.equals("gau")){
        for (int t=0 ; t<3; t++){
          messagelu=bthSerial.read();      
          vitesselue = vitesselue + messagelu ;
        }
        vitesse = vitesselue.toInt();
        tourneragauche();
        delay(50);
      }
      if (dir.equals("dro")){
        for (int t=0 ; t<3; t++){
          messagelu=bthSerial.read();
          vitesselue = vitesselue + messagelu ;
        }
        vitesse = vitesselue.toInt();
        tourneradroite();
        delay(50);
      }
      if (dir.equals("sto")){
        for (int t=0 ; t<3; t++){
          messagelu=bthSerial.read();
          vitesselue = vitesselue + messagelu ;
        }
        vitesse = vitesselue.toInt();
        arreter();
        delay(50);
      }
    }
    if (indication.equals("led")){
      for (int t=0 ; t<3; t++){
        messagelu=bthSerial.read();
        dir=dir+messagelu;
        delay(50);
      }
      if (dir.equals("ton")){
        lights = "on";
      } else if (dir.equals("tof")){
        lights = "off";
      } else if (dir.equals("swt")){
        pattern = (pattern + 1) % 12;
      }
    }
    indication ="";
    vitesselue="";
    dir="";
  }


  if (lights.equals("on")) {
    if (pattern == 0) {
      rainbow(counter % 12,0.25);
      counter = (counter + 1) % 36;
    } else if (pattern == 1) {
      monochrom(32,0,0);
    } else if (pattern == 2) {
      monochrom(0,32,0);
    } else if (pattern == 3) {
      monochrom(0,0,32);
    } else if (pattern == 4) {
      monochrom(32,32,0);
    } else if (pattern == 5) {
      monochrom(32,0,32);
    } else if (pattern == 6) {
      monochrom(0,32,32);
    } else if (pattern == 7) {
      monochrom(32,32,32);
    } else if (pattern == 8) {
      light1(base_color, counter / 6);
      counter = (counter + 1) % 36;
    } else if (pattern == 9) {
      light3(base_color, counter / 6);
      counter = (counter + 1) % 36;
    } else if (pattern == 10) {
      light4(base_color, counter / 6);
      counter = (counter + 1) % 36;
    } else if (pattern == 11) {
      light5(base_color, counter / 6);
      counter = (counter + 1) % 36;
    }
  } else {
    monochrom(0,0,0);
  }


  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent())
      return;
    // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
      return;


  byte len = 16;
  // Stores data is read on badge
  byte read_data[16];


  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
 
  // Authentification for color block
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, reading_block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
    // Read block
  status = mfrc522.MIFARE_Read(reading_block, read_data, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }


  if (writing_block != 0) {


    byte buffer[] = {0x32, 0x16, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00};


    // Authentification for color block
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, writing_block, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("Authentication failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }




    status = mfrc522.MIFARE_Write(writing_block, buffer, &len);
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("MIFARE_Write() failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
  }


  byte test[] = {32,0,0,0,32,0};
  light2(test);
 
  String base_msg = "Block ";
  base_msg.concat(reading_block);
  base_msg.concat("\n");
 
  for (byte i=0;i<len;i++) {
    base_msg.concat(char(read_data[i]));
  }


  bthSerial.println(base_msg);


  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();


}


