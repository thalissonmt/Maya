#ifndef MAYANUVEM_H
    #define MAYANUVEM_H
    #include <Arduino.h>
    #include <ArduinoJson.h>  

    class MayaNuvem{
      public:
        MayaNuvem();

        void setPeriodo(int periodo);
        void setTempo(int tempo);
        bool ativar();
        bool enviar(const JsonDocument& doc);

      private:
        int periodo_;
        int tempo_;
        String url_;
    };
#endif