
#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 9, 10, 11, 12 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 6, 8, 7}; 

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define ledpin 13
#define step_pin 3
#define dir_pin 2

int fullRotSteps = 1600;
int currSteps = 0;
int delayStep = 150;
int comboNums = 40;
  
void setup()
{
  
  pinMode(dir_pin, OUTPUT);
  pinMode(step_pin, OUTPUT);
  pinMode(ledpin,OUTPUT);
  digitalWrite(ledpin, HIGH);
  Serial.begin(9600);
  
}
void loop() 
{
  
  int key1 = kpd.waitForKey() - '0';
  int key2 = kpd.waitForKey() - '0';
  int key3 = kpd.waitForKey() - '0';
  int key4 = kpd.waitForKey() - '0';
  int key5 = kpd.waitForKey() - '0';
  int key6 = kpd.waitForKey() - '0';
  
  int num1 = key1 * 10 + key2;
  int num2 = key3 * 10 + key4;
  int num3 = key5 * 10 + key6;
  Serial.println(num1);
  Serial.println(num2);
  Serial.println(num3);
  //int num2 = 5;
  //int num3 = 5;
  int stepsPerNum = fullRotSteps / comboNums;
  
  digitalWrite(dir_pin,HIGH);
  currSteps =  fullRotSteps + (stepsPerNum * (comboNums - num1));
  while(currSteps > 0){
    digitalWrite(step_pin, LOW);
    delayMicroseconds(delayStep);
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(delayStep);
    currSteps--;
  }
  digitalWrite(dir_pin,LOW);
  currSteps = fullRotSteps + (stepsPerNum * (comboNums - num1)) + (stepsPerNum * num2);
 
  while(currSteps > 0){
    digitalWrite(step_pin, LOW);
    delayMicroseconds(delayStep);
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(delayStep);
    currSteps--;
  }
  
  digitalWrite(dir_pin,HIGH);
  currSteps = (fullRotSteps/fullRotSteps) * ((stepsPerNum * num2) + (stepsPerNum * (comboNums - num3))) ;
  
  
  while(currSteps > 0){
    digitalWrite(step_pin, LOW);
    delayMicroseconds(delayStep);
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(delayStep);
    currSteps--;
  }

  fullRotSteps = 0;
  
}
