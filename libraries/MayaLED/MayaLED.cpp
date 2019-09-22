#include "MayaLED.h"

    MayaLED::MayaLED(int pinoR, int pinoG, int pinoB){
        red   = pinoR;
        green = pinoG;
        blue  = pinoB;
    }

    void MayaLED::inicializar(){
        pinMode(blue, OUTPUT);
        pinMode(green, OUTPUT);
        pinMode(red, OUTPUT);

        ledcSetup(LED_CHANNEL_1, FREQUENCIA, RESOLUCAO); //Confiurar canal PWM
        ledcSetup(LED_CHANNEL_2, FREQUENCIA, RESOLUCAO);
        ledcSetup(LED_CHANNEL_3, FREQUENCIA, RESOLUCAO);

        ledcAttachPin(red, LED_CHANNEL_1); //Atribuir canal PWM ao pino
        ledcAttachPin(green, LED_CHANNEL_2);
        ledcAttachPin(blue, LED_CHANNEL_3);
    }

    void MayaLED::vermelho(int brilho){
        if(brilho){
            ledcWrite(LED_CHANNEL_1, 200);
            ledcWrite(LED_CHANNEL_2, 1024);
            ledcWrite(LED_CHANNEL_3, 1024);
        }else{
            ledcWrite(LED_CHANNEL_1, 920);
            ledcWrite(LED_CHANNEL_2, 1024);
            ledcWrite(LED_CHANNEL_3, 1024); 
        }
    }

    void MayaLED::azul(int brilho){
        if(brilho){
            ledcWrite(LED_CHANNEL_1, 1024);
            ledcWrite(LED_CHANNEL_2, 1024);
            ledcWrite(LED_CHANNEL_3, 200);
        }else{
            ledcWrite(LED_CHANNEL_1, 1024);
            ledcWrite(LED_CHANNEL_2, 1024);
            ledcWrite(LED_CHANNEL_3, 920); 
        }
    }

    void MayaLED::verde(int brilho){
        if(brilho){
            ledcWrite(LED_CHANNEL_1, 1024);
            ledcWrite(LED_CHANNEL_2, 200);
            ledcWrite(LED_CHANNEL_3, 1024); 
        }else{
            ledcWrite(LED_CHANNEL_1, 1024);
            ledcWrite(LED_CHANNEL_2, 920);
            ledcWrite(LED_CHANNEL_3, 1024); 
        }
    }

    void MayaLED::amarelo(int brilho){
        if(brilho){
            ledcWrite(LED_CHANNEL_1, 200);
            ledcWrite(LED_CHANNEL_2, 200);
            ledcWrite(LED_CHANNEL_3, 1024);
        }else{
            ledcWrite(LED_CHANNEL_1, 920);
            ledcWrite(LED_CHANNEL_2, 920);
            ledcWrite(LED_CHANNEL_3, 1024);  
        }
    }

    void MayaLED::magenta(int brilho){
        if(brilho){
            ledcWrite(LED_CHANNEL_1, 200);
            ledcWrite(LED_CHANNEL_2, 1024);
            ledcWrite(LED_CHANNEL_3, 200); 
        }else{
            ledcWrite(LED_CHANNEL_1, 920);
            ledcWrite(LED_CHANNEL_2, 1024);
            ledcWrite(LED_CHANNEL_3, 920); 
        }
    }

    void MayaLED::ciano(int brilho){
        if(brilho){
            ledcWrite(LED_CHANNEL_1, 1024);
            ledcWrite(LED_CHANNEL_2, 200);
            ledcWrite(LED_CHANNEL_3, 200); 
        }else{
            ledcWrite(LED_CHANNEL_1, 1024);
            ledcWrite(LED_CHANNEL_2, 920);
            ledcWrite(LED_CHANNEL_3, 920);
        }
    }

    void MayaLED::branco(int brilho){
        if(brilho){
            ledcWrite(LED_CHANNEL_1, 200);
            ledcWrite(LED_CHANNEL_2, 200);
            ledcWrite(LED_CHANNEL_3, 200); 
        }else{
            ledcWrite(LED_CHANNEL_1, 920);
            ledcWrite(LED_CHANNEL_2, 920);
            ledcWrite(LED_CHANNEL_3, 920); 
        }
    }

    void MayaLED::desligar(){
        ledcWrite(LED_CHANNEL_1, 1024);
        ledcWrite(LED_CHANNEL_2, 1024);
        ledcWrite(LED_CHANNEL_3, 1024); 
    }
