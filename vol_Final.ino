#include <dht11.h>
#define DHT11PIN 4
int led = 13;                // the pin that the LED is atteched to
int sensor = 2;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)
int RelayPin = 8;            // the pin that the relay is atteched to
int lowTemp = 5;             // lower limit of fan working temprature
int highTemp = 40;           // upper limit of fan workiing temprature
int val2 = 2;
int num = 2;
int flag = 0;

dht11 DHT11;

void setup() 
{
  pinMode(led, OUTPUT);                                       // initalize LED as an output
  pinMode(RelayPin, OUTPUT);                                  // initalize Relay as an output
  pinMode(sensor, INPUT);                                     // initialize sensor as an input
  Serial.begin(9600);                                         // initialize serial
}

void loop()
{
 if (flag == 0)                                              
 {                                                            //  if flag is 0 Relay is off and change flag to 1
   digitalWrite(RelayPin, HIGH);
   flag = 1;
 }
  DHT11.read(DHT11PIN);                                       //  read  DHT sensor value
  
  if(lowTemp < (DHT11.temperature) && (DHT11.temperature) < highTemp)              // condition for fan operation
    {
      val = digitalRead(sensor);                              // read sensor value
     if (Serial.available() > 0)                              //if some date is sent, reads it and saves in state
    {
      val2 = Serial.readString().toInt();                     // change input string "1" to int 1..
      
      if(val2 == 1)                                          //  if input is 1
      
        {
           digitalWrite(RelayPin, LOW);
          // Serial.println("Fan on");
            num = 1;
        }
  
       else if(val2 == 2)                                    //  if input is 2
       
        {
           digitalWrite(RelayPin, HIGH);
            //Serial.println("Fan off");
            num = 2;
        }
       else if(val2 == 3)                                    //  if input is 3
 
       {
          Serial.println("Motion Not detected!");            //print Motion Not detected!
          Serial.print("Temperature (C): ");                 //print Temperature (C):
          Serial.println(DHT11.temperature);
          if(num == 1)
          Serial.println("Fan on");
       else if (num == 2)
            Serial.println("Fan off");  
        }
  
    }
    else if (val == HIGH)                                           // check if the sensor is HIGH
        {           
          digitalWrite(led, HIGH);                                  // turn LED ON
          digitalWrite(RelayPin, LOW);
          delay(10000);
          digitalWrite(led, LOW);                                   // turn LED OFF
          digitalWrite(RelayPin, HIGH);
        }
       
    }

  else                                                             
    {
      digitalWrite(led, LOW); 
      digitalWrite(RelayPin, HIGH);                                // Temprature between range then this wil
       Serial.println(" Temprature Exceeded");                     //  execute 
    }
}
