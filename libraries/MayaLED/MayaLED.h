#ifndef MAYALED_H
    #define MAYALED_H
    #include <Arduino.h>

    class MayaLED{
      public:
        MayaLED(int pinoR, int pinoG, int pinoB);

        void vermelho();
        void azul();
        void verde();
        void amarelo();
        void roxo();
        void branco();

      private:
        int blue;
        int green;
        int red;
    };

#endif