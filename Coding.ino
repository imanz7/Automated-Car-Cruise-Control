#include <LiquidCrystal_I2C.h>
//#include <TimerOne.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

unsigned int counter = 0;   //set counter to 0
int potentiometer = A0;    // select the input pin for the potentiometer
int potentiometerValue = 0;  // variable to store the value coming from the sensor
int speedValue = 0;     // value of speed for motor moves and display from lcd
const int EN_A = 9;   // motor pin connection
int sensor = 2;
unsigned long starttime = 0;
unsigned long endtime = 0;
int steps = 0;
int stepsold = 0;
int temp = 0;
int rps = 0;
const int IR = 7;
const int buzzer = 12;
const int buttonPin = 10 ; 
int buttonState = 0; 
int i=0;

void forward(int pwmLeft)
{   analogWrite (EN_A, pwmLeft);
//Serial.println(rps);
   delay(100);
    //obstacle(); 
}


void displaylcd(int rotation)
{ lcd.setCursor(0,1);
  lcd.print(rotation);
  
}

void obstacle()
{  int irState = digitalRead (IR);
   if (irState == 1)
    digitalWrite (buzzer, LOW);
   else
   {
    digitalWrite (buzzer, HIGH);
    
      int newspeed= speedValue-100;
      forward(newspeed);
      Serial.println("speed decreased...."); 
      Serial.println(newspeed);
    }
}
void autocruise (int x)
{
  Serial.println(x);
  forward(x);
  
 
//Serial.println(rps);
   delay(100);
    //obstacle(); 


  
}
void manual()
{
  
   potentiometerValue = analogRead(potentiometer);
   speedValue = map(potentiometerValue, 0, 1023, 0, 255);  //set min and max value for speedValue
   Serial.println(speedValue);
   delay(500);
   forward (speedValue);
}


void setup() {
  // put your setup code here, to run once:

  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  // setup potentiometer as an INPUT: 
  pinMode(potentiometer, INPUT);
  //setup for motor as an OUTPUT
  pinMode (EN_A, OUTPUT);
  lcd.init();  // initialize the lcd 
  lcd.backlight();
  pinMode (sensor, INPUT);
  pinMode(IR, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 buttonState =digitalRead(buttonPin);
 if(buttonState == HIGH)
 {
   Serial.println(buttonState);
 
   i=i+1;

 }
    if((i%2)==1)
    {
      Serial.println("auto mode ..... ");
     autocruise(speedValue);
      
    }
 else
 {
  Serial.println("manual mode....");
  manual();
  
 }
 
      
     
     
 
    
  while (millis()<endtime)
  { if(digitalRead(sensor))
    { steps = steps+1;
      while(digitalRead(sensor));
    }
  }
   temp = steps - stepsold;
   stepsold = steps;
   rps = (temp/2);
   displaylcd(rps); 
   //Serial.println(rps);
   delay(100);
   //potentiometerValue = analogRead(potentiometer);
  // speedValue = map(potentiometerValue, 0, 1023, 0, 255);  //set min and max value for speedValue
   //Serial.println(speedValue);
  // delay(500);
   forward (speedValue);
   
   obstacle();    // detect obstacle

   starttime=millis();
   endtime = starttime + 1000;
   lcd.clear();
   // read the value 
}
