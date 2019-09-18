#include "MayaMPU.h" 
	float roll, pitch, rollF, pitchF, m_posicao; //Variaveis do Acelerometro

	MayaMPU::MayaMPU(int pinosda, int pinoscl){
			periodo_ = 3000;
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
			ax = 0; //Eixo X Acelerometro
			ay = 0; //Eixo Y Acelerometro
			az = 0;	//Eixo Z Acelerometro
			gx = 0; //Eixo X Giroscopio
			gy = 0; //Eixo Y Giroscopio
			gz = 0; //Eixo Z Giroscopio
			temperatura = 0; 
			pressao = 0;
			altitude = 0;
			lastMicros = 0;
			mx = 0; //Eixo X Magnetometro
			my = 0; //Eixo Y Magnetometro
			mz = 0; //Eixo Z Magnetometro
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
	}

	void converter_g_to_angle(int16_t x, int16_t y, int16_t z){ //Converte o valor do acelerometro em G para Angulo do eixo x e y;
		float x_out, y_out, z_out;
		x_out = (float)x/256; //Converte leitura do acelerometro LSB/G para G
    	y_out = (float)y/256; //Converte leitura do acelerometro LSB/G para G
    	z_out = (float)z/256; //Converte leitura do acelerometro LSB/G para G

    	roll = atan(y_out / sqrt(pow(x_out, 2) + pow(z_out, 2))) * 180 / PI; //Angulo eixo Y
    	pitch = atan(-1 * x_out / sqrt(pow(y_out, 2) + pow(z_out, 2))) * 180 / PI; //Angulo eixo X

    	rollF = 0.94 * rollF + 0.06 * roll; //Filtro para suavizar a variação do angulo do eixo Y
   		pitchF = 0.94 * pitchF + 0.06 * pitch; //Filtro para suavizar a variação do angulo do eixo X
	}

	void MayaMPU::acelerometro(){
   		accel.getAcceleration(&ax, &ay, &az); //Recebe os valores do acelerometro em LSB/g
		converter_g_to_angle(ax, ay, az);
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
	    
	    m_posicao = atan2(my, mx); //calcular a posição em graus, 0 graus indica Norte
	    if(m_posicao < 0)
	      m_posicao += 2 * M_PI;

	  	m_posicao *= 180/M_PI; 
	}
	
	void MayaMPU::ativar(int tipo){
		acelerometro();
		//giroscopio();
		//barometro();
		//magneto();

		/*if( millis() >  tempo_ + periodo_ ){
			tempo_ = millis();
		}*/

			if(tipo == 1){
			    Serial.print("Acelerometro:\t");
			    Serial.print(rollF); Serial.print("\t");
			    Serial.print(pitchF); Serial.print("\n");
			    // Serial.print("Velocidade Angular:\t");
			    // Serial.print(gx); Serial.print("\t");
			    // Serial.print(gy); Serial.print("\t");
			    // Serial.println(gz); Serial.print("\n");
	    		// Serial.print("Temperatura:\t");
	    		// Serial.print(temperatura); Serial.print("\n");
	    		// Serial.print("Pressao:\t");
	    		// Serial.print(pressao); Serial.print("\n");
	    		// Serial.print("Altitude:\t");
	    		// Serial.print(altitude); Serial.print("\n");
	    		// Serial.print("Magnetometro:\t");
	    		// Serial.print(mx); Serial.print("\t");
	    		// Serial.print(my); Serial.print("\t");
	    		// Serial.print(mz); Serial.print("\n");
	    		// Serial.print("Bussula:\t");
	    		// Serial.print(m_posicao); Serial.print("\n");
			}
	}
