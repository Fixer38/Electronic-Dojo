#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
// Setting up lcd screen
// Setting up keypad
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


String password = "1234"; 
byte pinRows[ROWS] = {8,7,6,5};
byte pinColumns[COLS] = {4,3,2,9};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), pinRows, pinColumns, ROWS, COLS);
String current_password;

LiquidCrystal_I2C lcd(0x3F, 16, 2);
void setup() {
  lcd.init();
  lcd.backlight();  
  Serial.begin(9600);
  // put your setup code here, to run once:
}

void loop() {
  lcd.setCursor(0, 0);
  char current_key=customKeypad.waitForKey();
  current_password += current_key;
  lcd.print(current_password);
  if(current_password[0] == '*') {
    
    lcd.clear();
    lcd.print("Entrez mdp");
    delay(3000);
    lcd.clear();
    current_password = "";
    while(current_password != password) {
  
      char current_key=customKeypad.waitForKey();
      current_password += current_key;
      lcd.print(current_key);
      if(current_password == password) {
        current_password = "";
        lcd.clear();
        lcd.print("Entrez le nouveau mot de passe (longueur max: 12");
        delay(5000);
        lcd.clear();
        while(current_password.length() <= 12 || current_key == '#') {
          
          char current_key=customKeypad.waitForKey();
          current_password += current_key;
          lcd.print(current_key);
          if(current_password.length() > 12) {
            lcd.clear();
            lcd.print("Trop long retour à 1234");
            password = "1234";
            break;
          }
          
          else if(current_key == '#') {
            password = current_password;
            lcd.clear();
            lcd.print("Mdp changé");
            current_password = "";
            break;
        }
      }}}}
    if(current_key == '#') {
      if(current_password.length() > password.length() || current_password != password) {
        lcd.clear();
        lcd.print("mdp Incorrect");
        current_password = "";
      }}
    if(current_key == 'D') {
      current_password = current_password.substring(0, current_password.length()-2);
      lcd.clear();
      lcd.print(current_password);
    }
    else if(current_password == password) {
      lcd.clear();
      lcd.print("mdp correct");
    }    
  }
   
