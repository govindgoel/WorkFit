#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo1;
Servo myservo2;

// create servo object to control a servo
// twelve servo objects can be created on most boards
//
int ThermistorPin = A4;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
//
//
unsigned long t1;

unsigned long t2;

//
int pos = 0;    // 
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int upButton = 10;
int downButton = 9;
int selectButton = 8;
int entrada = 0;
int menu = 1;
int LDR = A5;
int LED = 7;
unsigned long t ; 
bool x = false ; 
int i=0;


//////
//quote
//////

//////
//////
// ####################################
// ############# Setup ################
// ####################################

void setup() {
  lcd.begin(16, 2);

  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(13, INPUT); 
  pinMode(LED, OUTPUT);
  pinMode(1, OUTPUT);
myservo1.attach(A0);
  myservo2.attach(A1);
  t1=millis();
  updateMenu();
}


// ####################################
// ############# Loop #################
// ####################################

void loop() {
  if (!digitalRead(downButton)) {
    menu++;
    updateMenu();
    delay(100);
    while (!digitalRead(downButton));
  }

  if (!digitalRead(upButton)) {
    menu--;
    updateMenu();
    delay(100);
    while (!digitalRead(upButton));
  }

  if (!digitalRead(selectButton)) {
    execute();
    updateMenu();
    delay(100);
    while (!digitalRead(selectButton));
  }	
  if(digitalRead(13)== HIGH){
    Serial.print("high");
    digitalWrite(6,HIGH);
  }
    if(digitalRead(13)== LOW){
    Serial.print("low");
    digitalWrite(6,LOW);
  }
  entrada = analogRead(LDR);
  if (entrada < 500){
  digitalWrite(6, HIGH); 
}
  t2 = millis();
}


// ####################################
// ############# Updating #############
// ####################################

void updateMenu() {
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
    lcd.clear();
    lcd.print(">which break");
    lcd.setCursor(0, 1);
    lcd.print("Eye Excercise");
    break;
    case 2:
      lcd.clear();
      lcd.print(">Eye Excercise");
      lcd.setCursor(0, 1);
      lcd.print("Foot Excercise");
      break;
    case 3:
      lcd.clear();
      lcd.print("Eye Excercise");
      lcd.setCursor(0, 1);
      lcd.print(">Foot Excercise");
      break;
    case 4:
      lcd.clear();
      lcd.print(">Rock,Paper Game");
      lcd.setCursor(0, 1);
      lcd.print("TEMP");
      break;
    case 5:
      lcd.clear();
      lcd.print("Rock,Paper Game");
      lcd.setCursor(0, 1);
      lcd.print(">TEMP");
      break;
    case 6:
      lcd.clear();
      lcd.print("TEMP");
      lcd.setCursor(0, 1);
      lcd.print(">Quote of day");
      break;    
    case 7:
      menu = 6;
      break;
  }
}


// ####################################
// ############ Executing #############
// ####################################
void fruits(){
  if(t2-t1>3000 && t2-t1<3500){
    lcd.clear();
    lcd.print("Fruits break");
    delay(500);
  }
  else if(t2-t1>4500 && t2-t1<5500){
     lcd.clear();
    lcd.print("Water break");
    delay(500); 
  }
  else if(t2-t1>6500 && t2-t1<7500){
     lcd.clear();
    lcd.print("5 min break");
    delay(500); 
  }
  else{
    lcd.clear();
    lcd.print("Keep Working");
    lcd.setCursor(0, 1);
    lcd.print("Soon a break");
    delay(500);
  }

}
         
void execute() {
  switch (menu) {
    case 0:
      break;
    case 1:
      fruits();
      break;
    case 2:
      action1();
      break;
    case 3:
      action2();
      break;
    case 4:
      action3();
      break;
    case 5:
      action4();
      break;
    case 6:
      quote();
      break;
    case 7:
      quote();
      break;
  }
}


// ####################################
// ############## Actions #############
// ####################################

void action1() {
  lcd.clear();
  lcd.print(">Let's Excercise");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  lcd.print(".");
  
  digitalWrite(LED, HIGH);
  for (pos = 0; pos <= 180; pos += 1) {
    // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos); 
        myservo2.write(pos);            
    delay(15);                       
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo1.write(pos); 
    myservo2.write(pos);      
    delay(15);                       
  }
  delay(500);
}
void action2() {
  lcd.clear();
  lcd.print(">LED Aus");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  
  digitalWrite(LED, LOW);
  
  delay(500);
}

void action3() {
  lcd.clear();
  lcd.print("enter");
  lcd.setCursor(0, 1);
  lcd.print("1-r,2-p,3-s");
  delay(3000);
  lcd.clear();
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("enter your");
  lcd.setCursor(0, 1);
  lcd.print("choice");
  delay(1500);
}

void action4() {
  lcd.clear();
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 
  lcd.print("Temp:");
  lcd.print(T);   
  lcd.print(" F");
  delay(3000);            
  lcd.clear();
}
void quote(){
  lcd.clear();
  lcd.print("You can do it");
  delay(500);
}
   
