#include <LiquidCrystal.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#define pumpSwitch 4

#define humiditySensor A6
#define temperatureSensor 5

int humidityPercentage;
int humidityData;

float temperature;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

OneWire oneWirePin(temperatureSensor);
DallasTemperature tSensors(&oneWirePin);

void setup() {
 lcd.begin(16, 2);
 lcd.print("Starting up...");
 tSensors.begin();
 pinMode(pumpSwitch, OUTPUT);
}


void RequestSoilHumidity(){
  humidityData = analogRead(humiditySensor);
  humidityPercentage = map(humidityData, 1023, 0, 0, 100);
}

void RequestAmbiantTemperature(){
  tSensors.requestTemperatures();
  temperature = tSensors.getTempCByIndex(0);
}

int count =0; //ammmount of cycles needed in order to turn on the pump
const int secondsInADay=86400;

void loop() {
    
    
    RequestSoilHumidity();
    RequestAmbiantTemperature();

    lcd.clear();
    
    lcd.print("  Humidity: "); lcd.print(humidityPercentage); lcd.print("%");
    lcd.setCursor(2,1); lcd.print("Temp.: "); lcd.print(temperature ); lcd.print(" C");
    count++;

    
    if(count*10==secondsInADay) //takes roughly 10 seconds for a cycle scan- times the number of them
    {
       count=0;
       digitalWrite(pumpSwitch, HIGH);
       delay(5000);
       digitalWrite(pumpSwitch, LOW);
       lcd.begin(16, 2);
    }

     delay(9000); //break between scannin
}
