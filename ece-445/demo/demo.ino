#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

int cnt;
float tempC, tempF;
const int rs = PIN_PB4, en = PIN_PB3, d4 = PIN_PD5, d5 = PIN_PD4, d6 = PIN_PD3, d7 = PIN_PD2, g_led = PIN_PC5, probe = PIN_PC4, solenoid = PIN_PB0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
OneWire oneWire(probe); // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature. 

void setup() {
  sensors.begin();
  lcd.begin(16, 2);
  pinMode(g_led, OUTPUT); 
  pinMode(solenoid, OUTPUT);
}

void loop(){
  digitalWrite(g_led, HIGH); //test point

  sensors.requestTemperatures(); // Send the command to get temperatures
  tempC = sensors.getTempCByIndex(0); // get the temperature - from the first sensor by default
  tempF = sensors.toFahrenheit(tempC);
  delay(2000);
  
  /* open & close valve if reading was successful */
  if(tempC != DEVICE_DISCONNECTED_C){
    //display temp
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("C: ");
    lcd.print(tempC);
    lcd.setCursor(4, 1); 
    lcd.print("F: ");
    lcd.print(tempF);
    lcd.setCursor(4, 0);

    if (tempF < 55){
      lcd.clear();
      lcd.setCursor(4, 0); 
      lcd.print("F: ");
      lcd.print(tempF);
      digitalWrite(solenoid, HIGH);
      // delay(5000);
      cnt = 0;
      while(cnt < 5){
        lcd.setCursor(1, 1);
        lcd.print("VALVE OPEN  ");
        lcd.setCursor(13, 1);
        lcd.print("0");
        lcd.setCursor(14, 1);
        lcd.print(5 - cnt);
        delay(1000);
        cnt++;
      }
      digitalWrite(solenoid, LOW);

      //wait 60s for valve to cool down after opening
      cnt = 0;
      while(cnt < 30){
        lcd.clear();
        lcd.setCursor(4, 0); 
        lcd.print("F: ");
        lcd.print(tempF);
        lcd.setCursor(4, 1);
        lcd.print("WAIT  ");
        if(cnt > 20){
          lcd.setCursor(10, 1);
          lcd.print("0");
          lcd.setCursor(11, 1);
        }
        lcd.print(30 - cnt);
        delay(1000);
        cnt++;
      }
    }
  }

  //atmega and pi trying to read at the same time
  else{ 
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Reading");
    lcd.setCursor(6, 1);
    lcd.print("....");
    lcd.setCursor(4, 0);
  }
} 
