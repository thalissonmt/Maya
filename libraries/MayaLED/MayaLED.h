#ifndef MAYALED_H
    #include <Arduino.h>
    #define MAYALED_H
    #define FREQUENCIA 5000 //frequancia até 40kHz
    #define LED_CHANNEL_1 0 //canal PWM, esp32 0-15 canais
    #define LED_CHANNEL_2 1
    #define LED_CHANNEL_3 2
    #define RESOLUCAO 10 //Resolucao PWM, 8 - 10 - 12 - 15 bits

    class MayaLED{
      public:
        MayaLED(int pinoR, int pinoG, int pinoB);

        void vermelho(int brilho);
        void azul(int brilho);
        void verde(int brilho);
        void amarelo(int brilho);
        void magenta(int brilho);
        void ciano(int brilho);
        void branco(int brilho);
        void inicializar();
        void desligar();

      private:
        int blue;
        int green;
        int red;
    };

#endif