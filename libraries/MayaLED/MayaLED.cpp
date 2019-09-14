#include "MayaLED.h"

  MayaLED::MayaLED(int pinoR, int pinoG, int pinoB){
    red   = pinoR;
    green = pinoG;
    blue  = pinoB;
    
    pinMode(blue, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(red, OUTPUT);

  }

  void MayaLED::vermelho(){
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
  }

  void MayaLED::azul(){
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
  }

  void MayaLED::verde(){
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
  }

/*
  void MayaLED::amarelo(){
    analogWrite(blue, 0);
    analogWrite(green, 50);
    analogWrite(red, 255);
  }

  void MayaLED::roxo(){
    analogWrite(blue, 207);
    analogWrite(green, 0);
    analogWrite(red, 255);
  }*/

  void MayaLED::branco(){
    digitalWrite(blue, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(red, HIGH);
  }
