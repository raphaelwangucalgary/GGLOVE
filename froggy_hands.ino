#include <dht.h>

const int speaker = 7;
const int sensor_breath = 8;
const int sensor_light = A0;

//Variables//
dht DHT;
int threshold = 400;
int light_level = 500;
int counter = 30000;

void setup() {
  
pinMode(speaker,OUTPUT);//speaker output
pinMode(sensor_breath,INPUT);//dht11 sensor
pinMode(sensor_light,INPUT);//photoresistor
Serial.begin(9600);

}

void calibrate(){

  //get readings from the DHT11
  int x = DHT.read11(sensor_breath);
  int temp = DHT.temperature;
  int humidity = DHT.humidity;
  
if(temp != -999){
    
    //display humidity level
    /*
    Serial.print("humidity: ");
    Serial.print(humidity);
    Serial.println("%");
    */

    //if humidity is over 70%, register light level as new threshold
    if(humidity > 70){
      threshold = analogRead(sensor_light);
        Serial.print("new threshold set: ");
        Serial.println(sensor_light);
    }
  }
}//end Callibrate

void readBrightness(){
  light_level = analogRead(sensor_light);
  
  //display light level vs threshold
  /*
  Serial.print("light level: ");
  Serial.print(light_level);
  Serial.print("; threshold: ");
  Serial.println(threshold);
  */
}


void loop() {


  //when counter reaches 0, calibrate the sensors
  if(counter<=0){
    calibrate();
    readBrightness();
    counter=30000;
  }
  counter--;

  //if dark enough, play noise
  if(light_level <= threshold){
    
     //generate noise, play through speaker
     digitalWrite(speaker,random(2));
  }
  else{
    digitalWrite(speaker,LOW);
  }

}
