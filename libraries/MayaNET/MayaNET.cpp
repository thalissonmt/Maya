#include "MayaNET.h"
	
	WiFiMulti WiFiMulti;
	WiFiUDP ntpUDP;
	NTPClient timeClient(ntpUDP, "a.st1.ntp.br", -10800); //(UDP, "seridor_ntp", timezone em s)
	
	MayaNET::MayaNET(const char* ssid,const char* password){
		data_;
		ssid_ = ssid;
		password_ = password;
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

	void MayaNET::ativar(int tipo){
		timeClient.update();

		if(tipo == 1){
			Serial.print("Data: ");
  			Serial.print(receberData()); Serial.print("\t");
  			Serial.print("Hora: ");
  			Serial.print(receberHora()); Serial.print("\n");
		}
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