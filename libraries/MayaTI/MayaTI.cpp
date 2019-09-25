#include "MayaTI.h"

	MayaTI::MayaTI(int pino){
			periodo_ = 10000;
			tempo_ = 0;
			pino_ = pino;
			temperatura_ = 0;
	}

	void MayaTI::setPeriodo(int periodo){
		periodo_ = periodo;
	}
	
	void MayaTI::setTempo(int tempo){
		tempo_ = tempo;
	}
	
	float (&MayaTI::getDados(float (&dados)[1])) [1]{
		dados[0] = temperatura_;
		return dados;
	}
	
	void MayaTI::ativar(int tipo){
		OneWire pino(pino_);
		DallasTemperature barramento(&pino);
		DeviceAddress sensor;
		barramento.begin();
  		barramento.getAddress(sensor, 0); 

		if( millis() >  tempo_ + periodo_ ){
			tempo_        = millis();
			barramento.requestTemperatures(); 
  			temperatura_ = barramento.getTempC(sensor);
			
			if(tipo == 1){
				Serial.println("[TEMPERATURA INTERNA]");
				Serial.println(temperatura_);
				Serial.println("");
			}
		}	
		
	}