#include <Servo.h>

#define I2C_ADDR    0x3F // Pin pantalla

// Definimos los diferentes pines de los micropulsadores para el movimiento del brazo
int button1 = 2; // pin del boton sube motor 2 
int button2 = 3; // pin del boton baja motor 2 
int button3 = 4; // pin del boton sube motor 3 
int button4 = 5; // pin del boton sube motor 3 
int button5 = 6; // pin del boton sube motor 1 (base)
int button6 = 7; // pin del boton baja motor 1 (base)

// Variables de impresion para la lectura de HIGH y LOW
int lecturaboton1 = 0;
int lecturaboton2 = 0;

/** PINES PARA LOS LED's */
int rled = 11; // Pin PWN 11 para led rojo
int gled = 12;  // Pin PWM 9  para led verde
int bled = 13; // Pin PWM 10 para led azul

// Constante de velocidad de los motores
const int velocidadpwmlinks = 10; 

// Pines donde se encuentran los motores
int servopos1 = 8;
int servopos2 = 9;
int servoposbase = 10;

// Posiciones iniciales de los motores
int pos = 0; // Motor 1
int pos1 = 90; // Motor 2
int posbase = 60; // Motor base

// Definimos 3 objetos del tipo Servo
Servo servo1;
Servo servo2;
Servo servobase;

void setup()
{
  // Abrimos terminal a 9600 baudios
  Serial.begin(9600);      
  // Declaración de los motores paso a paso    
  servo1.attach(servopos1);
  servo2.attach(servopos2);
  servobase.attach(servoposbase);

  // Declaración de los diferentes pins para los micropulsadores
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  pinMode(button6, INPUT);

  /** Seleccion del tipo de pin para los Led's OUTPUT */
  pinMode(rled, OUTPUT);
  pinMode(bled, OUTPUT);
  pinMode(gled, OUTPUT);

  /** LCD */

}

void loop()
{
  //Posiciones iniciales a los motores
  servo1.write(pos);
  servo2.write(pos1);
  servobase.write(posbase);

  
  //lecturaboton1 = digitalRead(button1);
  //lecturaboton2 = digitalRead(button6);
  //Serial.print(lecturaboton2);
  
  if(digitalRead(button1) == HIGH && digitalRead(button2) == LOW){
    pos++;
    servo1.write(pos);
    ledrgb(50, 1);
    //velocidad();
  }
  else if(digitalRead(button2) == HIGH && digitalRead(button1) == LOW){
    pos--;
    servo1.write(pos);
    ledrgb(150, 1);
   // velocidad();
  }
  
  if(digitalRead(button3) == HIGH && digitalRead(button4) == LOW){
    pos1--;
    servo2.write(pos1);
    ledrgb(50, 2);
    velocidad();
  }
  else if(digitalRead(button4) == HIGH && digitalRead(button3) == LOW){
    pos1++;
    servo2.write(pos1);
    ledrgb(150, 2);
 //   velocidad();
  }
  if(digitalRead(button5) == HIGH && digitalRead(button6) == LOW){
    posbase++;
    servobase.write(posbase);
    ledrgb(50, 3);
   // velocidad();
  }
  else if(digitalRead(button6) == HIGH && digitalRead(button5) == LOW){
    posbase--;
    servobase.write(posbase);
    ledrgb(50,3);
   // velocidad();
  }
}

void reset(){

}

// Metodo que modifica la velocidad entre cada pulso de un motor 
void velocidad(){
      delay(velocidadpwmlinks);
}

// Metodo va cambiando de color los led RGB
void rgbon(){
  analogWrite(rled,255); // Se enciende color rojo
  delay(500);            // Se esperan 500 ms
  analogWrite(rled,0);   // Se apaga color rojo 
  analogWrite(bled,255); // Se enciende color azul
  delay(500);            // Se esperan 500 ms
  analogWrite(bled,0);   // Se apaga color azul
  analogWrite(gled,255); // Se enciende color verde
  delay(500);            // Se esperan 500 ms
  analogWrite(gled,0);   // Se apaga colo verde
}

// Sistema de LED's RGB para los diferentes movimientos 
void ledrgb(int ndelay, int color){
    if(color == 1){  
      analogWrite(rled,255); // Se enciende color rojo
    }
    else if(color == 2){
      analogWrite(bled,255); // Se enciende color azul
    }
    else if(color == 3){
      analogWrite(gled,255); // Se enciende color verde
    }
    delay(ndelay);
    // Se apagan todos los colores en los led's
    analogWrite(rled,0);
    analogWrite(bled,0);
    analogWrite(gled,0);
}

