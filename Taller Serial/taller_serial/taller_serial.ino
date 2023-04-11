// librerias
#include <Servo.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
// servos
Servo Myservo;
Servo Myservo1;
//variables globales
const byte numChars = 100;
char receivedChars[numChars];
char tempChars[numChars];  
int caso = 0;
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
int delay_led_1 = 0;
int delay_led_2 = 0;
int pos_servo_1 = 0;
int pos_servo_2 = 0;
unsigned long current_time = 0;
unsigned long current_time_2 = 0;
unsigned long current_stepper = 0;
unsigned long tx_send = 0;
bool led1 = LOW;
bool led2 = LOW;
bool stepper = LOW;
float floatFromPC = 0.0;
boolean newData = false;
int i = 0;
int a = 0;
int stepper_steps = 0;
char dir[10];
bool direction = LOW;
int POT1 = 0;
int POT2 = 0;
int slider = 0;
long global_steps = 0;
//prototipos de funciones
void Initial_menu (void);
void Read_data (void);
boolean isValidNumber(char * str);
void send_vals (void);
void sep_vals (char * str);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2,LOW);
  pinMode(4, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  Myservo.attach(3);
  Myservo1.attach(11);

}

void loop() {
  // put your main code here, to run repeatedly:
 Read_data(); //leer y verificar los datos recibidos
    if (newData == true){//si el dato fue correcto, separar y asignar a cada elemento el valor correspondiente
      sep_vals(receivedChars);
      memset(receivedChars, 0, sizeof(receivedChars));
      caso = 0;
      newData = false;
      Myservo.write(pos_servo_1);
      Myservo1.write(pos_servo_2);
    }
  //parpadeo de los LEDs dependiendo de los valores ingresados por el usuario 
  if ((millis() - current_time) >= delay_led_1){
    if (led1){
      digitalWrite(2,LOW);
      led1 = LOW;
    }else{
      led1 = HIGH;
      digitalWrite(2,HIGH);
    }
    current_time = millis();
  }
  if ((millis() - current_time_2) >= delay_led_2){
    if (led2){
      digitalWrite(12,LOW);
      led2 = LOW;
    }else{
      led2 = HIGH;
      digitalWrite(12,HIGH);
    }
    current_time_2 = millis();
  }
  
  if ((millis() - tx_send) >= 50){ //enviar valores cada 50 ms
    send_vals();
    tx_send = millis();    
  }
  
digitalWrite(13,direction);
if (a < stepper_steps){
  if (i< 800) {
    if ((micros() - current_stepper) >= 500){
    if (stepper){
      digitalWrite(4,LOW);
      stepper = LOW;
    }else{
      stepper = HIGH;
      digitalWrite(4,HIGH);
    }
    current_stepper = micros();
   }
   i++;
  }else{
    i = 0;
    a++;
  }
}else{
  a = 0;
  if (direction){
    global_steps = global_steps + stepper_steps;
  }else{
    global_steps = global_steps - stepper_steps;
  }
  stepper_steps = 0;
}
POT1 = analogRead(A0);
POT2 = analogRead(A1);
slider = analogRead(A2);

}

void Initial_menu (void){
  Serial.println("<1> Cambiar LEDs");
  Serial.println("<2> Cambiar stepper");
  Serial.println("<3> Cambiar servo");
  Serial.println("<4> Obtener valores del sistema");
  Serial.println("<5> Cargar valores al sistema completo");
}
void Read_data (void){
  static byte ndx = 0;
  char endMarker = '>';
  char rc;
  static bool onTransmission = false;
  while (Serial.available() > 0 && newData == false) {
      rc = Serial.read();
    if (onTransmission == true){
      if (rc != endMarker) {
          receivedChars[ndx] = rc;
          ndx++;
          if (ndx >= numChars) {
              ndx = numChars - 1;
          }
      }
      else {
          receivedChars[ndx] = '\0'; // terminate the string
          ndx = 0;
          newData = true;
          onTransmission = false;
      }
    } else if (rc == '<'){
      onTransmission = true;
    }
  }
  
}

boolean isValidNumber(char* str){
  int check = 0;
  for(byte i=0;i<sizeof(str);i++)
  {
  if(isalpha(str[i])) check++;
  }
  if (check>0) {
    return false;
  } else {
    return true;
  }
}

void send_vals (void){
  Serial.print("POT1=");
  Serial.print(POT1);
  Serial.print(",");
  Serial.print("POT2=");
  Serial.print(POT2);
  Serial.print(",");
  Serial.print("slider=");
  Serial.println(slider);
}
void sep_vals (char * str){
  char * aux_str;
  char * aux_str_2;
  char * aux_str_3;
  char * aux_str_4;
  char * aux_str_5;
  char * aux_str_6;
  aux_str = strtok(str,",");
  aux_str_2 = strtok(NULL,",");
  aux_str_3 = strtok(NULL,",");
  aux_str_4 = strtok(NULL,",");
  aux_str_5 = strtok(NULL,",");
  aux_str_6 = strtok(NULL,",");
  strtok(aux_str,"=");
  delay_led_1 = atoi(strtok(NULL,"="));
  strtok(aux_str_2,"=");
  delay_led_2 = atoi(strtok(NULL,"="));
  strtok(aux_str_3,"=");
  pos_servo_1 = atoi(strtok(NULL,"="));
  strtok(aux_str_4,"=");
  pos_servo_2 = atoi(strtok(NULL,"="));
  strtok(aux_str_5,"=");
  stepper_steps = atoi(strtok(NULL,"="));
  strtok(aux_str_6,"=");
  if (atoi(strtok(NULL,"="))==1){
   direction = HIGH;
  }else{
    direction = LOW;
  }

}