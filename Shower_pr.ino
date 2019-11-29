#include <EEPROM.h>
#include <Countimer.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Countimer tDown;
int inPin = 8; //Potentiometer 
int val = 0;//value of pm high or low
String t; //for timer at 2 minute
String d = "00:02:00";
String g = "00:05:00";
String f = "00:00:30";
int c = 0;
int v;
int a;
uint8_t EEPROMaddress = 0;
void setup()
{
lcd.begin(16,2); // name suggests
Serial.begin(9600);
pinMode(inPin, INPUT); //potentio
pinMode(13,OUTPUT); //solenoid
tDown.setCounter(0,05, 0, tDown.COUNT_DOWN, tDownComplete);//timer
tDown.setInterval(print_time2, 1000); // Call print_time2() method every 1s.
lcd.clear();
lcd.setCursor(0,0); //top line of the lcd display
lcd.print("Rotate to Start"); //utility of potentio
lcd.setCursor(0,1); //bottom line of lcd display
lcd.print("Rotate to Pause");
}

void loop()
{
  Serial.print(a);
val = digitalRead(inPin);
tDown.run();
{
switch (val) // for resuming and pausing the timer and also stop the solenoid valve
{
case HIGH:
tDown.start();
digitalWrite(13,LOW);
break;
case LOW:
tDown.pause();
digitalWrite(13,HIGH);
break;
default:
break;
}
}
}

void print_time2() //function for printing the time on the display
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Shower :");
lcd.print(tDown.getCurrentTime());
t=(tDown.getCurrentTime());
if(t == d)//2 min left buzzer
{

tone(10,2000,1000); 
delay(1500);
tone(10,2000,1000);
tone(10,2000,1000); 
delay(1500);
tone(10,2000,1000);
    lcd.setCursor(0,1);
  lcd.print("Be Quick");
  delay(3500);
}
if(t == g)//5 min buzzer
{
tone(10,2000,1000);
delay(1500);
tone(10,2000,1000);
delay(1500);
tone(10,2000,1000);
}
if(t == f)//half min left buzzer
{

tone(10,2000,1000);
delay(1500);
tone(10,2000,1000);
tone(10,2000,1000); 
delay(1500);
tone(10,2000,1000);
  lcd.setCursor(0,1);
  lcd.print("Hurry Up");
    delay(3500);
}
}


void tDownComplete()
{
digitalWrite(13,HIGH); //Close solvenoid valve
tone(10,2000,1000); 
delay(1500);
tone(10,2000,1000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Shower Over"); //Text for line 1
lcd.setCursor(0,1);
lcd.print("Have a Good Day!"); //Text for line 2
delay(2000);
c++; // update the value for keeping the count of the number of use of the shower
v = EEPROM.read(EEPROMaddress); // reading the value at the 0th address
EEPROM.write(EEPROMaddress,c+v); // updating the value with the previous number of count +1
a=EEPROM.read(EEPROMaddress);// final value 
Serial.print(a*30);
exit(0); 
}
