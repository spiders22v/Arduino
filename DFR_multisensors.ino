/*
 Example code for arduino with multi-sensors (DFRobot) 
 Editor     : spiders22v@gmail.com
 Date       : 10 July 2017
 Version    : 1.0
 */

// 디지털 핀 설정
int pushButton = 2;  // 버튼
int touchSensor = 4;  // 터치센서
int redLED = 6;       // LED 핀 설정

// 아날로그 핀 설정
int frameSensor = A0;     // 불꽃 센서
int rotationSensor = A1;  // 회전 센서
int soundSensor = A2;     // 사운드 센서
int moistureSensor = A3;  // 습도 센서
int lightSensor = A4;     // 조도 센서
int tempSensor = A5;      // 기온 센서

int ledPin = 13;       // LED 핀 설정
 
int state = LOW;      // LED 상태
int reading;          // 터치센서 상태
int button = LOW;     // 버튼 상태
int previous = LOW;   // 터치센서 이전 상태

int sensorMin = 0;        // minimum sensor value
int sensorMax = 1023;     // maximum sensor value

uint16_t temp;
double dat;

int rotationValue = 0;        // value read from the pot
int ledValue = 0;             // value output to the PWM (analog out)
 
void setup()
{
  Serial.begin(9600);
  pinMode(touchSensor, INPUT); // 터치센서 를 설정
  pinMode(ledPin, OUTPUT);    // ledPin 설정
}
 
void loop()
{
  // Touch sensor 
  reading = digitalRead(touchSensor);  // touchSensor 상태 읽음
 
  if (reading == HIGH && previous == LOW) {
    if (state == HIGH){    // ledPin 가 HIGH 면 LOW 로 바꿔준다.
      state = LOW;
      Serial.println("LED turns off");
    }  
    else{                  // ledPin 가 LOW 면 HIGH 로 바꿔준다.
      state = HIGH;      
      Serial.println("LED turns on"); 
    }
  } 
  digitalWrite(ledPin, state);   
  previous = reading;
  

  // Button
  button = digitalRead(pushButton);  // pushButton 상태 읽음

  if (button == HIGH){

    // Frame  sensor
    int frameValue = analogRead(frameSensor);
    Serial.print("Frame value is ");
    Serial.print(frameValue,DEC);  
    Serial.println(" [min:0, max: 1023].");

    // Sound sensor
    int soundValue = analogRead(soundSensor);
    Serial.print("Sound value is ");
    Serial.print(soundValue,DEC);
    Serial.println(" [min:0, max: 1023]."); 

    /* Moisture Sensor
       the sensor value description
        0  ~300     dry soil
        300~700     humid soil
        700~950     in water
    */
    int moistureValue = analogRead(moistureSensor);
    Serial.print("Moisture value is ");
    Serial.print(moistureValue);
    Serial.println(" [min:0, max: 1023].");
    

    // Light sensor (Illumination range : 1 Lux to 600 Lux)
    int lightValue = analogRead(lightSensor);
    int calValue = map(lightValue, sensorMin, sensorMax, 1, 600);    
    Serial.print("Light level is ");
    Serial.print(calValue);
    Serial.println(" LUX."); 

    // Tempurature Sensor
    temp = analogRead(tempSensor);
    dat = (double) temp * (5/10.24);     
    Serial.print("Temperature is ");
    Serial.print(dat);
    Serial.println(" C."); 

    // Rotation Sensor
    rotationValue = analogRead(rotationSensor);
    ledValue = map(rotationValue, sensorMin, sensorMax, 0, 255);
    analogWrite(redLED, ledValue);
    Serial.print("Rotation value is ");
    Serial.print(rotationValue);
    Serial.print(" \t RED LED output is ");
    Serial.println(ledValue); 


    Serial.println("");    
  }

  
  button = LOW; 


  delay(150);


  
}
