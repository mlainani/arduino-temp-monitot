#include <LiquidCrystal.h>

#include "DHT.h"



#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

const int relayPin = 13
bool relayIsOpen = true;

LiquidCrystal lcd(7,8,9,10,11,12);  //Pins for the LCD display, as taken from arduino.cc 

DHT dht(DHTPIN, DHTTYPE);

 

void setup() {

  //Serial.begin(9600); 

  dht.begin();

  lcd.begin(16, 2);
  
  pinMode(relayPin, OUTPUT);
  
  digitalWrite(relayPin, HIGH); // open relay i.e. turn switch off
}

 

void loop() {

  // Reading temperature or humidity takes about 250 milliseconds!
	delay(250); // I guess this can be in the order of minutes, humidity/temp doesn't change so fast

  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  float h = dht.readHumidity();

  float t = dht.readTemperature();

  if (isnan(t) || isnan(h)) {
      lcd.setCursor(0, 0);
	  lcd.print("Failed to read from DHT");
	  return; // Jump to the next iteration without executing the code below
  }

  t = (t * 9 / 5) + 32;

 
    lcd.clear();

    lcd.setCursor(0, 0);

    lcd.print("Humidity: ");

    lcd.print(h);

    lcd.print("%");

    lcd.setCursor(0, 1);

    lcd.print("Temp: ");

    lcd.print(t);

    lcd.print("f");
	
	if (h < 70) { // 70 is just to put a real figure
		// We want to leave the relay closed as long as needed for humidity to reach 70%
		// and close the relay (start water supply) only if it was previously open
		if (relayIsOpen == true)
		{
			digitalWrite(relayPin, LOW);
			relayIsOpen = false;
		}
	}
	else
	{
		// We've reached or exceeded 70%, time to re-open the relay (stop water supply)
		digitalWrite(relayPin, HIGH);
		relayIsOpen = true;
	}
}
