#ifndef MAYALDR_H
    #define MAYALDR_H
    #include <Arduino.h>

    class MayaLDR{
      public:
        MayaLDR(int pino);

        void setPeriodo(int periodo);
        void setTempo(int tempo);
        void ativar(int tipo);
        int (&getDados(int (&dados)[3]))[3];

      private:
        int periodo_;
        int tempo_;
        int pino_;
        int claro_;
        int sombra_;
        int escuro_;
        int luminosidade_;
    };
#endif