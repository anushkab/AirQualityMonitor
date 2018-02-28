float sensorValue;
float DustVal;
int gsen = A1;
int dsen = A0;
int pin2 = 3;
int pin3 = 5;
int pin4 = 6;

int measurePin = 2;
int ledPower = 2;
 
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
 
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

float Normal_upper=100;
float Polluted_upper=225;
float Toxic_upper=400;
float hazardL = 600;

void setup()
{
  Serial.begin(9600);      // sets the serial port to 9600
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  //pinMode(ledPower,OUTPUT);
}

void setColor(int red, int green, int blue)
{
  analogWrite(pin2, red);
  analogWrite(pin3, green);
  analogWrite(pin4, blue);  
}

void loop()
{
  //setColor(255,0,0);
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);
 
  voMeasured = analogRead(measurePin); // read the dust value
 
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
 
  // 0 - 3.3V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = voMeasured * (3.3 / 1024);
  dustDensity = 1000*0.17 * calcVoltage - 0.1;
 
  Serial.print("Raw Signal Value (0-1023): ");
  Serial.print(voMeasured);
 
  Serial.print(" - Voltage: ");
  Serial.print(calcVoltage);
 
  Serial.print(" - Dust Density: ");
  Serial.println(dustDensity);

  
  sensorValue = analogRead(gsen);       // read analog input pin 0
  
  Serial.print("Value of gas sensor : ");
  Serial.println(sensorValue);
  
  if (dustDensity < Normal_upper) {
    setColor(255, 255 , 255);  //white
  }
  else if (dustDensity <Polluted_upper) {
    setColor(255,255, 255);  //white
  }
  else if (dustDensity <Toxic_upper) {  
   setColor(0, 255, 0);  //green
  }
  else if (dustDensity < hazardL ){
    setColor(0,0,255);  //red
  }
  else {
    setColor(255, 0, 0);  // red
  }

  delay(1000);
}
