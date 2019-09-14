#include "MayaDHT.h"

	MayaDHT::MayaDHT(int pino, unsigned char dht){
		periodo_ = 3000;
		tempo_ = 0;
		pino_ = pino;
		dht_ = dht;
		t_ = 0;
		u_ = 0;
	}
	
	void MayaDHT::setPeriodo(int periodo){
		periodo_ = periodo;
	}
	
	void MayaDHT::setTempo(int tempo){
		tempo_ = tempo;
	}

	int (&MayaDHT::getDados(int (&dados)[2])) [2]{
		dados[1] = t_;
		dados[2] = u_;
		return dados;
	}
	
	void MayaDHT::ativar(int tipo){
		if( millis() >  tempo_ + periodo_ ){
			tempo_        = millis();
			DHT dht(pino_, dht_);
			dht.begin();
			u_ = dht.readHumidity();
			t_ = dht.readTemperature();
			
			if(tipo == 1){
				Serial.println("[TEMPERATURA - POR MINUTO]");
				Serial.print("Temperatura: ");
				Serial.println(t_);
				Serial.print("Umidade: ");
				Serial.println(u_);
				Serial.println("");
			}
		}
	}