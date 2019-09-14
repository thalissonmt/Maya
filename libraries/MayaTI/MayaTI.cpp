#include "MayaTI.h"

	MayaTI::MayaTI(int pino){
			periodo_ = 0;
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
	
	int (&MayaTI::getDados(int (&dados)[1])) [1]{
		dados[1] = temperatura_;
		return dados;
	}
	
	void MayaTI::ativar(int tipo){
		if( millis() >  tempo_ + periodo_ ){
			tempo_        = millis();
			OneWire ourWire(pino_);
			DallasTemperature sensors(&ourWire);
			sensors.begin();
			sensors.requestTemperatures();
			temperatura_ = sensors.getTempCByIndex(0);
		}
			
		if(tipo == 1){
			Serial.println("[TEMPERATURA]");
			Serial.println("[INTERNA]");
			Serial.print("Temperatura: ");
			Serial.println(temperatura_);
			Serial.println("");
		}
		
	}