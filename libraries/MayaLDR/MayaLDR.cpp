#include "MayaLDR.h"

  MayaLDR::MayaLDR(int pino){
    periodo_ = 1000; 
    tempo_   = 0;
    pino_    = pino;
    claro_   = 0;
    sombra_  = 0;
    escuro_  = 0;
  }

  void MayaLDR::setPeriodo(int periodo){
    periodo_ = periodo;
  }

  void MayaLDR::setTempo(int tempo){
    tempo_ = tempo;
  }

  int (&MayaLDR::getDados(int (&dados)[3])) [3]{
    dados[1] = claro_;
    dados[2] = sombra_;
    dados[3] = escuro_;
    claro_ = sombra_ = escuro_ = 0;
    return dados;
  }

  void MayaLDR::ativar(int tipo){
    if( millis() >  tempo_ + periodo_ ){
      tempo_        = millis();
      luminosidade_ = analogRead(pino_);

      if ( luminosidade_ >= 0 && luminosidade_ <= 300 ) {
        claro_++;
      } else if (luminosidade_ > 300 && luminosidade_ <= 3700) {
        sombra_++;
      } else {
        escuro_++;
      }

      if ( tipo == 1 ){
        Serial.println("[LUMINOSIDADE - POR MINUTO]");
        Serial.print("Claro: ");
        Serial.println(claro_);
        Serial.print("Sombra: ");
        Serial.println(sombra_);
        Serial.print("Escuro: ");
        Serial.println(escuro_);
        Serial.print("Luminosidade: ");
        Serial.println(luminosidade_);
        Serial.println("");
      }
    }
  }

  int MayaLDR::luminosidade(){
    return analogRead(pino_);
  }

