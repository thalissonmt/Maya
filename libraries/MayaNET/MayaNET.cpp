#include "MayaNET.h"
	
	WiFiMulti WiFiMulti;
	WiFiUDP ntpUDP;
	NTPClient timeClient(ntpUDP, "a.st1.ntp.br", -3*3600, 60000); //(UDP, "servidor_ntp", timezone em s)
	
	MayaNET::MayaNET(const char* ssid,const char* password){
		data_;
		hora_;
		min_;
		seg_;
		ano_;
		mes_;
		dia_;
		ssid_ = ssid;
		password_ = password;
		periodo_ = 60000;
		tempo_ = 0;
	}

	void MayaNET::setPeriodo(int periodo){
		periodo_ = periodo;
	}
	
	void MayaNET::setTempo(int tempo){
		tempo_ = tempo;
	}

	void MayaNET::inicializar(){
		WiFiMulti.addAP(ssid_, password_);
  		while(WiFiMulti.run() != WL_CONNECTED) {
    		Serial.print(".");
    		delay(500);
  		}
		timeClient.begin();
    	while(!timeClient.update())
    	{
        	Serial.print(".");
        	timeClient.forceUpdate();
        	delay(500);
    	}
	}

	String MayaNET::atualizarDataHora(){
		int splitStringY, splitStringM, splitStringD;
		String anoS, mesS, diaS;
	
		data_ = timeClient.getFormattedDate();
		
		splitStringY = data_.indexOf("Y");
		splitStringM = data_.indexOf("M");
		splitStringD = data_.indexOf("D");
  		anoS = data_.substring(0, splitStringY);
  		mesS = data_.substring(splitStringY+1, splitStringM);
  		diaS = data_.substring(splitStringM+1, splitStringD);

  		ano_ = anoS.toInt();
  		mes_ = mesS.toInt();
  		dia_ = diaS.toInt();
  		hora_ = timeClient.getHours();
  		min_ = timeClient.getMinutes();
  		seg_ = timeClient.getSeconds();

  		return data_;
	}

	int MayaNET::receberHora(){
		return hora_;
	}

	int MayaNET::receberMin(){
		return min_;
	}

	int MayaNET::receberSeg(){
		return seg_;
	}

	int MayaNET::receberAno(){
		return ano_;
	}

	int MayaNET::receberMes(){
		return mes_;
	}

	int MayaNET::receberDia(){
		return dia_;
	}

	unsigned long MayaNET::receberEpoch(){
		return timeClient.getEpochTime();
	}
	
	void MayaNET::ativar(int tipo){
		if( millis() >  tempo_ + periodo_ ){
			while(!timeClient.update())
    		{
        		Serial.print(".");
        		timeClient.forceUpdate();
        		delay(500);
    		}
			tempo_  = millis();
			if(tipo == 1){
		  		Serial.print("Data: ");
				Serial.print(ano_); Serial.print("-");
				Serial.print(mes_); Serial.print("-");
				Serial.print(dia_);
				Serial.print("\t Hora: ");
				Serial.print(hora_); Serial.print(":");
				Serial.print(min_); Serial.print(":");
				Serial.println(seg_);
			}
		}
	}