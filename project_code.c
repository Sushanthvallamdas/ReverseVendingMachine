#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_12C.h>

LiquidCrystal_12lcd(0*27,16,2)

#define calibration_factor 400.0 ??This value is obtained using the SparkFun_HX711_Calibration sketch

#define LOADCELL_DOUT_PIN  2
#define LOADCELL_SCK_PIN  3
#define Buzzer_PIN  4
HX711 scale;
int temp=0;
void setup(){
	lcd.intit();
	lcd.intit();
	lcd.backlight();
	lcd.setCursor(0,0);
	pinMode(Buzzer_PIN,OUTPUT);
	lcd.print("REVERSE VENDING");
	Serial.begin(9600);
	Serial.println("REVERSE VENDING");

	scale.begin(LOADCELL_DOUT_PIN,LOADCELL_SCK_PIN);
	scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
	scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

	Serial.println("Readings:");
	}

void loop(){
	Serial.print("Reading: ");
	Serial.print(scale.get_units(),1); //scale.get_units()returns a float
	Serial.print("Grams");
	Serial.println();
	if(scale.get_units() <5 && temp == 0){
	lcd.setCursor(0,1);
	lcd.print("Waiting..");
	digitalWrite(Buzzer_PIN,LOW);
	temp = 1;
	}
	
	if(scale.get_units() > 5 && temp == 1){
	temp = 0;
	lcd.setCursor(0,1);
	lcd.print("Get it   ..");
	lcd.setCursor(0,1);
	lcd.print("                        ");
	lcd.setCursor(0,1);
	lcd,print('Weight : ");
	lcd.setCursor(10,1);
	lcd.print(scale.get_units());
	int rewards = scale.get_units();
	rewards = rewards/50;
	digitalWrite(Buzzer_PIN, 1);
	delay(1000);
	digitalWrite(Buzzer_PIN, 0);
	lcd.setCursor(0,1);
	lcd.print("                        ");
	lcd.setCursor(0,1);
	lcd.print("Recieved ");
	lcd.setCursor(10,1);
	lcd.print(rewards);
	lcd.setCursor(11,1);
	lcd.print("coins");

	}

}