#include <MQ7.h>
int led1= 13;
int led2= 12;
int led3 = 11;
MQ7 mq7(A1,5.0);
#include <dht11.h>
const int AOUTpin=1;//the AOUT pin of the CO sensor goes into analog pin A0 of the arduino
int value;
#define dht_apin A0 // Analog Pin sensor is connected to 
dht11 DHT;
int row=0;
void setup(){
  Serial.begin(9600);
   pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);
   pinMode(led3, OUTPUT);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
   Serial.println("CLEARDATA");
  Serial.println("LABEL,Time,Humidity(%),Temperature(oC),CO(ppm)");
  
  delay(1000);//Wait before accessing Sensor 
}//end "setup()"
 
void loop(){
  //Start of Program 
   value= analogRead(AOUTpin);//reads the analaog value from the CO sensor's AOUT pin
  Serial.print("CO value: ");
   Serial.println(mq7.getPPM());//prints the CO value
  Serial.println("ppm");
    DHT.read(dht_apin);    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    Serial.print("DATA,TIME,"); Serial.print(DHT.humidity); Serial.print(","); Serial.print((DHT.temperature)/10);Serial.print(","); Serial.println(mq7.getPPM());
    row++;
    if (row>150){
      
    row=0;
    Serial.println("ROW,SET,2");
    }
    if ((DHT.temperature/10)>3.5&&(mq7.getPPM()>2.5)){
      digitalWrite(led2, HIGH);
    }
    if ((DHT.temperature/10)>4 && (mq7.getPPM()>3.0)){
      digitalWrite(led1, HIGH);
    }
    else {
       digitalWrite(led3, HIGH);
    }
    delay(1000);//Wait 5 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
 
}// end loop(
