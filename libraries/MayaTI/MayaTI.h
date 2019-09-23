#ifndef MAYATI_H
    #define MAYATI_H
    #include <Arduino.h>
	#include <OneWire.h>
    #include <DallasTemperature.h>
	
	
    class MayaTI{
      public:
        MayaTI(int pino);

        void setPeriodo(int periodo);
        void setTempo(int tempo);
        void ativar(int tipo);
        float (&getDados(float (&dados)[1]))[1];

      private:
        int periodo_;
        int tempo_;
        int pino_;
        float temperatura_;
    };
#endif