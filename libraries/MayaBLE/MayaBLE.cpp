#include "MayaBLE.h"
		static  BLEUUID serviceUUID(BLEUUID((uint16_t)0x180D));
		static  BLEUUID    charUUID(BLEUUID((uint16_t)0x2A37));
		static boolean doConnect = false;
		static boolean connected = false;
		static boolean doScan = false;
		static boolean notification = false;
		static BLERemoteCharacteristic* pRemoteCharacteristic;	
		static BLEAdvertisedDevice* myDevice;
		int batimentos_;

	MayaBLE::MayaBLE(){
		periodo_ 	= 0;
		tempo_ 		= 0;
		//batimentos_ = 0;		
	}
	
	void MayaBLE::setPeriodo(int periodo){
		periodo_ = periodo;
	}
	
	void MayaBLE::setTempo(int tempo){
		tempo_ = tempo;
	}

	class MyClientCallback : public BLEClientCallbacks {
		void onConnect(BLEClient* pclient) {}
	  	void onDisconnect(BLEClient* pclient) {
			connected = false;
			Serial.println("onDisconnect");
	  	}
	};
	
	class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
	  void onResult(BLEAdvertisedDevice advertisedDevice) {
		Serial.print("BLE Advertised Device found: ");
		Serial.println(advertisedDevice.toString().c_str());
		if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {
		  BLEDevice::getScan()->stop();
		  myDevice = new BLEAdvertisedDevice(advertisedDevice);
		  doConnect = true;
		  doScan = true;		  
		} 
	  } 
	};
	
	void notifyCallback(
	  BLERemoteCharacteristic* pBLERemoteCharacteristic,
	  uint8_t* pData,
	  size_t length,
	  bool isNotify) {
		if(length == 2){
		  batimentos_ = pData[1];
		}
	}
	
	int (&MayaBLE::getDados(int (&dados)[1])) [1]{
		dados[1] = batimentos_;
		return dados;
	}
	

	
	bool connectToServer() {
    Serial.print("Forming a connection to ");
    Serial.println(myDevice->getAddress().toString().c_str());
    
    BLEClient*  pClient  = BLEDevice::createClient();
    Serial.println(" - Created client");

    pClient->setClientCallbacks(new MyClientCallback());

 
    pClient->connect(myDevice); 
    Serial.println(" - Connected to server");
    BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
    if (pRemoteService == nullptr) {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(serviceUUID.toString().c_str());
      pClient->disconnect();
      return false;
    }
    Serial.println(" - Found our service");
    pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
    if (pRemoteCharacteristic == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(charUUID.toString().c_str());
      pClient->disconnect();
      return false;
     
    }
    Serial.println(" - Found our characteristic");
    if(pRemoteCharacteristic->canRead()) {
      std::string value = pRemoteCharacteristic->readValue();
      Serial.print("The characteristic value was: ");
      Serial.println(value.c_str());
    }

    if(pRemoteCharacteristic->canNotify())
      pRemoteCharacteristic->registerForNotify(notifyCallback);

    connected = true;
}
void MayaBLE::montar() {
	  Serial.println("Iniciando BLE...");
	  BLEDevice::init("");
	  BLEScan* pBLEScan = BLEDevice::getScan();
	  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
	  pBLEScan->setInterval(1349);
	  pBLEScan->setWindow(449);
	  pBLEScan->setActiveScan(true);
	  pBLEScan->start(5, false);
}
void MayaBLE::ativar(int tipo){
		if( millis() >  tempo_ + periodo_ ){
			tempo_        = millis();			
			  if (connected) {
					if (notification == false) {
				  const uint8_t onPacket[] = {0x1, 0x0};
				  pRemoteCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t*)onPacket, 2, true);
				  notification = true;
				}
			  }
				if(tipo == 1){
					if (doConnect == true) {
						if (connectToServer()) {
						  Serial.println("Conectado ao servidor BLE.");
						} else {
						  Serial.println("Falha ao conectar ao servidor BLE.");
						}
						doConnect = false;
					}
					Serial.println("[CARDIACO]");
					Serial.print("Batimentos (por minuto):");
					Serial.println(batimentos_);
					Serial.println("");
			}
		}
	}