#include "MayaMPU.h" 
	float pitchF; //Acelerometro angulo Eixo X
	float rollF; //Acelerometro angulo Eixo Y
	float azF, axF, ayF; //Acelerometro, aceleracao dos Eixos
	float accel_magnitude; //modulo dos 3 eixos do acelerometro
	float mag_posicao; 
	bool accel_control = false; //Variavel de controle do acelerometro

	MayaMPU::MayaMPU(int pinosda, int pinoscl){
			periodo_ = 1000;
			tempo_ = 0;
			pinosda_ = pinosda;
			pinoscl_ = pinoscl;
			data_;
			sentado_;
			deitado_;
			empe_;
			passos_;
			accel; //acelerometro
			gyro; //giroscopio
			baro; //barometro
			mag; //magnetometro
			ax; //Eixo X Acelerometro
			ay; //Eixo Y Acelerometro
			az;	//Eixo Z Acelerometro
			gx; //Eixo X Giroscopio
			gy; //Eixo Y Giroscopio
			gz; //Eixo Z Giroscopio
			mx; //Eixo X Magnetometro
			my; //Eixo Y Magnetometro
			mz; //Eixo Z Magnetometro
			temperatura; 
			pressao;
			altitude;
			lastMicros;
	}
	
	void MayaMPU::setPeriodo(int periodo){
		periodo_ = periodo;
	}
	
	void MayaMPU::setTempo(int tempo){
		tempo_ = tempo;
	}
	
	int (&MayaMPU::getDados(int (&dados)[4])) [4]{
		dados[1] = sentado_;
		dados[2] = empe_;
		dados[3] = deitado_;
		dados[4] = passos_;
		sentado_ = empe_ = deitado_ = passos_ = 0;
		return dados;
	}
	
	void MayaMPU::inicializar(){
		Wire.begin(pinosda_, pinoscl_);
		accel.initialize();
		gyro.initialize();
   	 	baro.initialize();
   	 	mag.initialize();
		Serial.println("Testando sensores..."); //Imprimir no Serial a situação dos sensores ao iniciar a esp32
    	Serial.println(accel.testConnection() ? "Conexao com ACELEROMETRO bem sucedida" : "Conexao com ACELEROMETRO falhou");
    	Serial.println(gyro.testConnection() ? "Conexao com GIROSCOPIO bem sucedida" : "Conexao com GIROSCOPIO falhou");
    	Serial.println(baro.testConnection() ? "Conexao com BAROMETRO bem sucedida" : "Conexao com BAROMETRO falhou");
    	Serial.println(mag.testConnection() ? "Conexao com MAGNETOMETRO bem sucedida" : "Conexao com MAGNETOMETRO falhou");
    	tempo_ = millis();
	}

	void converter_g_to_angle(int16_t x, int16_t y, int16_t z){ //Converte o valor do acelerometro em G para Angulo do eixo x e y;
		float roll, pitch, ax_out, ay_out, az_out;
		ax_out = (float)x/256; //Converte leitura do acelerometro LSB/G para G
    	ay_out = (float)y/256; //Converte leitura do acelerometro LSB/G para G
    	az_out = (float)z/256; //Converte leitura do acelerometro LSB/G para G
    	if((ax_out || az_out) != 0){
	    	roll = atan(ay_out / sqrt(pow(ax_out, 2) + pow(az_out, 2))) * 180 / PI; //Angulo eixo Y
    	}
	    if((ay_out || az_out) != 0){
	    	pitch = atan(-1 * ax_out / sqrt(pow(ay_out, 2) + pow(az_out, 2))) * 180 / PI; //Angulo eixo X
	    }	
	    axF = 0.94 * axF + 0.06 * ax_out;
	    ayF = 0.94 * ayF + 0.06 * ay_out;
	    azF = 0.8 * azF + 0.2 * az_out;
	    accel_magnitude = sqrt(axF*axF+ayF*ayF+azF*azF); //Modulo dos 3 eixos
    	rollF = 0.94 * rollF + 0.06 * roll; //Filtro para suavizar a variação do angulo do eixo Y
   		pitchF = 0.94 * pitchF + 0.06 * pitch; //Filtro para suavizar a variação do angulo do eixo X
	}

	void MayaMPU::acelerometro(){
		static int time = millis();
   		
   		accel.getAcceleration(&ax, &ay, &az); //Recebe os valores do acelerometro em LSB/g
		converter_g_to_angle(ax, ay, az);

		if(accel_magnitude>1.25){ //Modulos dos eixos maior que 1.25g
    		time = millis();
    		if(!accel_control){
    			accel_control = true;
    			passos_++;
    		}
    	}
    	if(accel_magnitude<1.25 && accel_control){
    		if((millis()-time)>220){ //espera 220ms para diminuir a quantidade de passos falsos
    			accel_control = false;
    		}
    	}
	}

	void MayaMPU::giroscopio(){
	    gyro.getAngularVelocity(&gx, &gy, &gz); //Recebe os valores do giroscopio  
	}

	void MayaMPU::barometro(){
	    baro.setControl(BMP085_MODE_TEMPERATURE); //Solicita temperatura
	    
	    lastMicros = micros();
	    while (micros() - lastMicros < baro.getMeasureDelayMicroseconds()); //Espera pelo tempo apropriado para conversao (4.5ms)

	    temperatura = baro.getTemperatureC(); //Recebe o valor da temperatura calibrada em grau Celsius(C)

	    baro.setControl(BMP085_MODE_PRESSURE_3);  // Solicitada pressao
	    while (micros() - lastMicros < baro.getMeasureDelayMicroseconds()); //(23.5ms)

	    pressao = baro.getPressure(); //Recebe o valor da pressao calibrada em Pascals(Pa)

	    // Calcula a altitude em metros(m) baseada na pressao recebida
	    // Pode passar um segundo parametro "Pressao no nivel do mar"
	    // caso contrario usa o valor padrao de 101325 Pa)
	    altitude = baro.getAltitude(pressao); 
	}

	void MayaMPU::magneto(){
	    mag.getHeading(&mx, &my, &mz); //Recebe os valores do magnetometro
	    
	    mag_posicao = atan2(my, mx); //calcular a posição em graus, 0 graus indica Norte
	    if(mag_posicao < 0)
	      mag_posicao += 2 * M_PI;

	  	mag_posicao *= 180/M_PI; 
	}
	
	void MayaMPU::ativar(int tipo){
		acelerometro();
		//giroscopio();
		//barometro();
		//magneto();
		
		if( millis() >  tempo_ + periodo_ ){
			tempo_ = millis();

			if(pitchF>-30 && pitchF<30 && rollF>-30 && rollF<30 && azF>0){
				empe_++;
			}else if(rollF>30 && pitchF>-30 && pitchF<30 && azF>0){
				sentado_++;
			}else{
				deitado_++;
			}

			if(tipo == 1){
				Serial.println("[POSIÇAO - POR MINUTO]");
				Serial.print("pitch: ");
				Serial.print(pitchF);
				Serial.print(" roll: ");
				Serial.println(rollF);
		        Serial.print("Em pé: ");
		        Serial.println(empe_);
		        Serial.print("Sentado: ");
		        Serial.println(sentado_);
		        Serial.print("Deitado: ");
		        Serial.println(deitado_);
		        Serial.print("Passos: ");
		        Serial.println(passos_);
		        Serial.println("");
			}
		}
	}
