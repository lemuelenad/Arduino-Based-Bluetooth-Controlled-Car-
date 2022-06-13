/*
 * Created by Salvatore Fancello 
 * Project: Arduino Control Car via Bluetooth with Android Smartphone
 * More information at http://www.progettiarduino.com
 */
 
//L298 Connection   
  const int motorA1  = 5;  // Pin  in1 of L298
  const int motorA2  = 6;  // Pin  in2 of L298
  const int motorB1  = 10; // Pin in3 of L298
  const int motorB2  = 11;  // Pin in4 of L298
//Leds connected to Arduino UNO Pin 13-12-9
  const int ledAnt  = 13; // Led fari anteriori
  const int ledPost = 12; //led fari posteriori
  const int frecce = 9; // led luci di emergenza
//Buzzer / Speaker to Arduino UNO Pin 3
  const int buzzer = 3 ;   
//Useful Variables
  int i=0;
  int j=0;
  int state;
  int vSpeed=200;     // Default speed, from 0 to 255

void setup() {
    // Set pins as outputs:
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    pinMode(ledAnt, OUTPUT); 
    pinMode(ledPost, OUTPUT);  
    pinMode(frecce,OUTPUT); 
    // Initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
}
 
void loop() {

  //Save income data to variable 'state'
    if(Serial.available() > 0){     
      state = Serial.read();  
      Stop(); 
    }
  
     
  /***********************Forward****************************/
  //If state is equal with letter 'A', car will go forward!
    if (state == 'A') {
      analogWrite(motorA1, vSpeed); 
      analogWrite(motorA2, 0);
      analogWrite(motorB1, vSpeed);      
      analogWrite(motorB2, 0); 
     
    }
  /***********************Backward****************************/
  //If state is equal with letter 'I', car will go backward
    else if (state == 'I') {
      analogWrite(motorA1, 0);   
      analogWrite(motorA2, vSpeed); 
      analogWrite(motorB1, 0);  
      analogWrite(motorB2, vSpeed); 
    }
  /***************************Left*****************************/
  //If state is equal with letter 'S', wheels will turn left
    else if (state == 'S') {
      analogWrite(motorA1, 200);   
      analogWrite(motorA2, 0); 
      analogWrite(motorB1, 0); 
      analogWrite(motorB2, 200); 
    }
  /***************************Right*****************************/
  //If state is equal with letter 'D', wheels will turn right
    else if (state == 'D') {
      analogWrite(motorA1, 0);   
      analogWrite(motorA2, 200); 
      analogWrite(motorB1, 200);   
      analogWrite(motorB2, 0);     
    }
  /************************Luci Anteriori*****************************/
  //If state is equal with letter 'B', turn leds on or of off
    else if (state == 'B') {
      if (i==0){  
         digitalWrite(ledAnt, HIGH); 
         i=1;
      }
      else if (i==1){
         digitalWrite(ledAnt, LOW); 
         i=0;
      }
      state='n';
    }
     /************************Luci Posteriori*****************************/
  //If state is equal with letter 'E', turn leds on or of off
    else if (state == 'E') {
      if (i==0){  
         digitalWrite(ledPost, HIGH); 
         i=1;
      }
      else if (i==1){
         digitalWrite(ledPost, LOW); 
         i=0;
      }
      state='n';
    }
     /************************Luci di Emergenza*****************************/
  //If state is equal with letter 'E', turn leds on or of off
    else if (state == 'F') {
      if (i==0){  
         digitalWrite(frecce, HIGH);
         delay(1000);
         digitalWrite(frecce, LOW);
         delay(1000);
         digitalWrite(frecce, HIGH);
         delay(1000);
         digitalWrite(frecce, LOW);
         delay(1000);
         i=1;
      }
      else if (i==1){
         digitalWrite(frecce, LOW); 
         i=0;
      }
      state='n';
    }
  /**********************Horn sound***************************/
  //If state is equal with letter 'C', play (or stop) horn sound
    else if (state == 'C'){
      if (j==0){  
         tone(buzzer, 1000);//Speaker on 
         j=1;
      }
      else if (j==1){
         noTone(buzzer);    //Speaker off 
         j=0;
      }
      state='n';  
    }
  /************************Stop*****************************/
  //If state is equal with letter 'S', stop the car
    else if (state == 'P'){
        analogWrite(motorA1, 0);  
        analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  
        analogWrite(motorB2, 0);
        digitalWrite(ledPost, HIGH);
        
        noTone(buzzer);
    }

   
}

void Stop() {
  analogWrite(motorA1, 0);  
  analogWrite(motorA2, 0); 
  analogWrite(motorB1, 0);  
  
  analogWrite(motorB2, 0);
}


