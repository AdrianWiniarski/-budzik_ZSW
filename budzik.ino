#include <DHT.h>


#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <Time.h>
#include <TimeLib.h>
#include <DS1302.h>
#include <Wire.h>  
#define DHTPIN 10          // numer pinu sygnałowego
#define DHTTYPE DHT11     // typ czujnika (DHT11). Jesli posiadamy DHT22 wybieramy DHT22
 
DHT dht(DHTPIN, DHTTYPE); // definicja czujnika

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


DS1302 rtc(2, 3, 4);

// Init a Time-data structure
Time t;

 //int dht_dpin = A0;
 //DHT dht(dht_dpin, DHT11);
// Set the LCD address to 0x27 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x3F, 16, 2);
//#include <DS1302.h>

int pset = 8; // pushbutton for setting alarm
int psetH = 7; // pushbutton for godzina
int psetM = 6 ; // pushbutton for minuta
int psetS = 5; // pushbutton for sekunda


int buzzer = 9;
int h;
int m;
int s;
int activate=0;
 



void setup()
{
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);

    dht.begin();  
  
  // Setup LCD to 16x2 characters
  lcd.begin(16, 2);


pinMode(buzzer, OUTPUT);
}


void loop()
{  

// Odczyt temperatury i wilgotności powietrza
  int t = dht.readTemperature();
  int h = dht.readHumidity();
 
  // Sprawdzamy czy są odczytane wartości
  if (isnan(t) || isnan(h))
  {
  } else
  {

    lcd.setCursor(11, 0);
    // Jeśli tak, wyświetlamy wyniki pomiaru
    lcd.print(h);
    lcd.print("%");
    lcd.setCursor(11, 1);
    lcd.print(t);
    lcd.println("^C");
  }
 
  
 if (activate == 0) {
  // Display time centered on the upper line
  lcd.setCursor(0, 0);
  lcd.print(rtc.getTimeStr());
  
  
  // Display abbreviated Day-of-Week in the lower left corner
 // lcd.setCursor(0, 1);
 // lcd.print(rtc.getDOWStr(FORMAT_SHORT));
  
  // Display date in the lower right corner
  lcd.setCursor(0, 1);
  lcd.print(rtc.getDateStr());


 if ( rtc.getTime().hour== h &&  rtc.getTime().min== m &&  rtc.getTime().sec==s) {

  lcd.setCursor(4, 0);
  lcd.print(rtc.getTimeStr());
  
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  delay(300);
  digitalWrite(9, LOW);
  delay(50);
  digitalWrite(9, HIGH);
  delay(300);
  digitalWrite(9, LOW);
  delay(100);
  tone(6,400,300);
  delay (500);
 }


  
 } // setting button pressed




 if (digitalRead(pset) == HIGH) {
 activate=1;
 lcd.clear();
 delay(1000); 
 }

 
 while(activate == 1){
 lcd.setCursor(0,0);
 lcd.print("Podaj");
  if(h<10){
    lcd.setCursor(6,0);
 lcd.print("0");
  lcd.setCursor(7,0);
 lcd.print(h);
 }
 
 if(h>=10){
  
  lcd.setCursor(6,0);
 lcd.print(h); 
 }
 if (h>23){
 h=0;
 lcd.clear(); }

 
  lcd.setCursor(8,0);
 lcd.print(":");


 if(m<10){
  lcd.setCursor(9,0);
 lcd.print("0");
  lcd.setCursor(10,0);
 lcd.print(m);
 }
 
 if(m>=10){
  lcd.setCursor(9,0);
 lcd.print(m); 
 }
 if (m>59){
 m=0;
 lcd.clear(); }

 
 lcd.setCursor(11,0);
 lcd.print(":");



 if(s<10){
  lcd.setCursor(12,0);
 lcd.print("0");
  lcd.setCursor(13,0);
 lcd.print(s);
 }
 
 if(s>=10){
  lcd.setCursor(12,0);
 lcd.print(s); 
 }
 if (s>59){
 s=0;
 lcd.clear(); }
 
 if (digitalRead(psetH) == HIGH){
 h++;

 delay(300); 
 }
 if (digitalRead(psetM) == HIGH){
 m++;

delay(300);
 }

 if (digitalRead(psetS) == HIGH){
 s++;
 
 delay(300); 
 }

 if (digitalRead(pset) == HIGH){
 activate = 0;
 lcd.clear();
 delay(300);
 }
 }
 
}
