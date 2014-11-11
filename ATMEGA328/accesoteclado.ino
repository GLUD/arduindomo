#include <Keypad.h> 
// include the library code:
#include <LiquidCrystal.h>
#include <Servo.h> 

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 13, 5, 4, 3, 2);

const byte ROWS = 4; // four rows
const byte COLS = 3; // three columns
 
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
 
byte rowPins[ROWS] = {0, 1 ,9, 10}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; // connect to the column pinouts of the keypad
 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int posicion=0; 
const char clave='1990';
char passinp;
int led = 11;
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
int pos = 0;    // variable to store the servo position                  
                
void setup() {
  //   myservo.attach(11);  // attaches the servo on pin 9 to the servo object 
  lcd.begin(16, 2);
   pinMode(led, OUTPUT);
//Serial.begin(9600);
// Print a message to the LCD.
  lcd.print("Ingresa el pass");
}
void loop() {
 
char key = keypad.getKey();
if (key){
switch(posicion){
case 0:
 lcd.setCursor(posicion, 1);
  // print the number of seconds since reset:
  lcd.print(key);
  posicion++;
  passinp=key;
  break;
case 1:
lcd.setCursor(posicion, 1);
  // print the number of seconds since reset:
  lcd.print(key);
  posicion++;
  passinp=key;
  break;
case 2:
lcd.setCursor(posicion, 1);
  // print the number of seconds since reset:
  lcd.print(key);
  posicion++;
  passinp=key;
  break;

case 3:
lcd.setCursor(posicion, 1);
  // print the number of seconds since reset:
  lcd.print(key);
  posicion++;
  passinp=key;
case 4:
//lcd.setCursor(0, 0);
  // print the number of seconds since reset:
  //lcd.print("Confirme con #");
  if(passinp==clave){
  lcd.setCursor(0, 0);
  lcd.print("Autorizado.......");
  delay(1000);
  digitalWrite(led, HIGH);
  
    for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
lcd.setCursor(0,1 );
  lcd.print("Hackaton por la paz y la cultura libre");
  lcd.scrollDisplayLeft(); 
  delay(500);
    }
      for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
        lcd.setCursor(0,1 );
  lcd.scrollDisplayLeft(); 
 delay(500);
  }
//   for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
//  {                                  // in steps of 1 degree 
//    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
//    delay(150);                       // waits 15ms for the servo to reach the position 
//  } 
//  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
//  {                                
//    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
//    delay(150);                       // waits 15ms for the servo to reach the position 
//  } 
  
  }
  else{
  lcd.setCursor(0, 0);
  lcd.print("No autorizado.........");
  lcd.setCursor(0,1 );
  lcd.print("Intenta de nuevo");
  break;
  }
  break;
  
}  
//Serial.println(key);
// break;
}
}
