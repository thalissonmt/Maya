#include "MayaMPU.h" 
		int	MPU_ADDR_ 		= 0x68; 
		int	WHO_AM_I_ 		= 0x75; 
		int	PWR_MGMT_1_ 	= 0x6B; 
		int	GYRO_CONFIG_ 	= 0x1B; 
		int	ACCEL_CONFIG_ 	= 0x1C; 
		int	ACCEL_XOUT_ 	= 0x3B; 
		int	AcX_ = 0;
		int	AcY_ = 0;
		int	AcZ_ = 0;

	MayaMPU::MayaMPU(int pinosda, int pinoscl){
			periodo_ = 3000;
			tempo_ = 0;
			pinosda_ = pinosda;
			pinoscl_ = pinoscl;
			AcX = 0;
			AcY = 0;
			AcZ = 0;
			MPU_ADDR_ 		= 0x68; 
			WHO_AM_I_ 		= 0x75; 
			PWR_MGMT_1_ 	= 0x6B; 
			GYRO_CONFIG_ 	= 0x1B; 
			ACCEL_CONFIG_ 	= 0x1C; 
			ACCEL_XOUT_ 	= 0x3B; 
			data_;
			sentado_;
			deitado_;
			empe_;
			passos_;
			reg_;
			val_;
	}
	
	void MayaMPU::setPeriodo(int periodo){
		periodo_ = periodo;
	}
	
	void MayaMPU::setTempo(int tempo){
		tempo_ = tempo;
	}
	
	void writeRegMPU(int reg_, int val_){
		
	  Wire.beginTransmission(MPU_ADDR_);     
	  Wire.write(reg_);                      
	  Wire.write(val_);                      
	  Wire.endTransmission(true);           
	}
	
	uint8_t readRegMPU(uint8_t reg_){
	  uint8_t data;
	  Wire.beginTransmission(MPU_ADDR_);     
	  Wire.write(reg_);                      
	  Wire.endTransmission(false);          
	  Wire.requestFrom(MPU_ADDR_, 1);      
	  data = Wire.read();                   
	  return data;                          
	}
	
	void findMPU(int MPU_ADDR_){
	  Wire.beginTransmission(MPU_ADDR_);
	  int data = Wire.endTransmission(true);
	 
	  if(data == 0){
		Serial.print("Dispositivo encontrado no endereço: 0x");
		Serial.println(MPU_ADDR_, HEX);
	  }else{
		Serial.println("Dispositivo não encontrado!");
	  }
	}

	void checkMPU(int MPU_ADDR_){
	  findMPU(MPU_ADDR_);
	  int data = readRegMPU(WHO_AM_I_); 

	  if( data == 104 ){
		Serial.println("MPU6050 Dispositivo respondeu OK! (104)");
	 	data = readRegMPU(PWR_MGMT_1_); 

		if(data == 64){
		  	Serial.println("MPU6050 em modo SLEEP! (64)");
		} else {
			Serial.println("MPU6050 em modo ACTIVE!"); 
		}
	  }else{
	  	Serial.println("Verifique dispositivo - MPU6050 NÃO disponível!");
	  } 
	}
	
	void setSleepOff(){
	  writeRegMPU(PWR_MGMT_1_, 0); 
	}

	void setGyroScale(){
	  writeRegMPU(GYRO_CONFIG_, 0);
	}

	void setAccelScale(){
	  writeRegMPU(ACCEL_CONFIG_, 0);
	}
	
	void initMPU(){
	  setSleepOff();
	  setGyroScale();
	  setAccelScale();
	}

	void readRawMPU(){  
	  Wire.beginTransmission(MPU_ADDR_);       
	  Wire.write(ACCEL_XOUT_);                      
	  Wire.endTransmission(false);            
	  Wire.requestFrom(MPU_ADDR_, 14);         
	 
	  AcX_ = Wire.read() << 8;                 
	  AcX_ |= Wire.read();                    
	  AcY_ = Wire.read() << 8;
	  AcY_ |= Wire.read();
	  AcZ_ = Wire.read() << 8;
	  AcZ_ |= Wire.read(); 
	}
	
	int (&MayaMPU::getDados(int (&dados)[4])) [4]{
		dados[1] = sentado_;
		dados[2] = empe_;
		dados[3] = deitado_;
		dados[4] = passos_;
		sentado_ = empe_ = deitado_ = passos_ = 0;
		return dados;
	}
	
	void MayaMPU::montar(){
		Wire.begin(pinosda_, pinoscl_);
		initMPU();
		checkMPU(MPU_ADDR_);
		
	}
	
	void MayaMPU::ativar(int tipo){
		if( millis() >  tempo_ + periodo_ ){
			tempo_        = millis();
			readRawMPU();
			if(AcX_ > -7000 && AcX_ < 7000 && AcY_ > 5000 && AcY_ < 13000 && AcZ_ > -16000 && AcZ_ < -10000){
			  	empe_++;
			}else if(AcX_ > -2000 && AcX_ < 3000 && AcY_ > -7000 && AcY_ < 2000 && AcZ_ > -18000 && AcZ_ < -14000){
			  	deitado_++;			   
			}else if(((AcX_ > 10000 && AcX_ < 18000)||(AcX_ > -18000 && AcX_ < -10000)) && AcY_ > -1000 && AcY_ < 3000 && AcZ_ > -10000 && AcZ_ < 3000){
			  	deitado_++; 
			}else if(AcX_ > -4000 && AcX_ < 4000 && AcY_ > 12000 && AcY_ < 18000 && AcZ_ > -12000 && AcZ_ < 1000){
			 	sentado_++;
			}else{
				deitado_++;
			}
			
			if ((AcX_ < -6000 || AcZ_ < -6000 || AcX_ > 6000 || AcZ_ > 6000) && (AcY_ > 12000)) {
				passos_++;
			}

			if(tipo == 1){
				Serial.println("[POSICAO - POR MINUTO]");
				Serial.print("Em Pé: ");
				Serial.println(empe_);
				Serial.print("Deitado: ");
				Serial.println(deitado_);
				Serial.print("Sentado: ");
				Serial.println(sentado_);
				Serial.println("[PASSOS]");
				Serial.print("Quantidade: ");
				Serial.println(passos_);
				Serial.println(" -------------- ");					

				Serial.print("AcX = "); Serial.print(AcX_);
				Serial.print(" | AcY = "); Serial.print(AcY_);
				Serial.print(" | AcZ = "); Serial.print(AcZ_);
				Serial.println(); 
			}
		}
	}
