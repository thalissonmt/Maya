#include "MayaNET.h"
	
	WiFiMulti WiFiMulti;
	WiFiUDP ntpUDP;
	NTPClient timeClient(ntpUDP, "a.st1.ntp.br", -10800); //(UDP, "servidor_ntp", timezone em s)
	
	MayaNET::MayaNET(const char* ssid,const char* password){
		data_;
		ssid_ = ssid;
		password_ = password;
		periodo_ = 3000;
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
		timeClient.forceUpdate();
	}


	String MayaNET::receberData(){
		int splitString;
		data_ = timeClient.getFormattedDate();
		splitString = data_.indexOf("T");
  		return data_.substring(0, splitString);
	}

	String MayaNET::receberHora(){
		return timeClient.getFormattedTime();
	}

	unsigned long MayaNET::receberEpoch(){
		return timeClient.getEpochTime();
	}
	
	void MayaNET::ativar(int tipo){
		timeClient.update();

		if( millis() >  tempo_ + periodo_ ){
			tempo_  = millis();
			if(tipo == 1){
				Serial.print("Data: ");
	  			Serial.print(receberData()); Serial.print("\t");
	  			Serial.print("Hora: ");
	  			Serial.println(receberHora());
	  			Serial.println("");
			}
		}
	}