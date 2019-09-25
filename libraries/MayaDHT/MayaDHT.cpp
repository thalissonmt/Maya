#include "MayaDHT.h"

	MayaDHT::MayaDHT(int pino, unsigned char dht){
		periodo_ = 1000;
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

	float (&MayaDHT::getDados(float (&dados)[2])) [2]{
		dados[0] = t_-3.4;
		dados[1] = u_;
		t_ = u_ = 0;
		return dados;
	}
	
	void MayaDHT::ativar(int tipo){
		static int time_init = millis();
		DHT dht(pino_, dht_);
		dht.begin();

		if((millis()-time_init)>2000){ //O sensor retorna nova leitura a cada 2s
			u_ = dht.readHumidity();
			t_ = dht.readTemperature();
			time_init = millis();
		}
			
		if( millis() >  tempo_ + periodo_ ){
			tempo_  = millis();
			
			if(tipo == 1){
				if (isnan(u_) || isnan(t_)) {
					Serial.println(F("Failed to read from DHT sensor!"));
				}else{
					Serial.println("[TEMPERATURA - POR MINUTO]");
					Serial.print(F("Umidade: "));
					Serial.print(u_);
					Serial.print(F("%  Temperatura: "));
					Serial.print(t_);
					Serial.println("°C ");
					Serial.println("");
				}
			}
		}
	}