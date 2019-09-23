#include "MayaNuvem.h"
#include <ArduinoJson.h>  
#include <HTTPClient.h>
 MayaNuvem::MayaNuvem(){
    periodo_ = 3600000; 
    tempo_   = 0;
    url_     = "http://3.88.193.51/joao/send-post.php";
  }

  void MayaNuvem::setPeriodo(int periodo){
    periodo_ = periodo;
  }

  void MayaNuvem::setTempo(int tempo){
    tempo_ = tempo;
  }


  bool MayaNuvem::ativar(){
    if( millis() >  tempo_ + periodo_ ){
      tempo_ = millis();
      return true;
    }
    return false;
  }

  bool MayaNuvem::enviar(const JsonDocument& doc){
	  String output;
    serializeJson(doc, output);

    Serial.println(output);
    Serial.println("Enviando Para o servidor.");
	
    HTTPClient http;
    http.begin(url_);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(output);
    http.end();

    Serial.print("Cod HTTP: ");    
    Serial.print(httpCode); 
    Serial.println("");    
    return true;
  }
