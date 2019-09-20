#ifndef MAYAMPU_H
    #define MAYAMPU_H
    #include <Arduino.h>
	#include <Wire.h>
	#include "I2Cdev.h" //Protocologo I2C
	#include "ADXL345.h" //Acelerometro
	#include "L3G4200D.h" //Gyroscopio
	#include "BMP085.h" //Barometro
	#include "HMC5883L.h" // Magnetometro
	
	class MayaMPU{
		public:
			MayaMPU(int pinosda, int pinoscl);
			
			void setPeriodo(int periodo);
			void setTempo(int tempo);
			void ativar(int tipo);
			int (&getDados(int (&dados)[4])) [4];
			void inicializar();
			void acelerometro();
			void giroscopio();
			void barometro();
			void magneto();
	
		private:
			int periodo_;
			int tempo_;
			int pinosda_;
			int pinoscl_;
			uint8_t data_;
			int sentado_;
			int deitado_;
			int empe_;
			int passos_;
			int16_t ax; //Eixo X Acelerometro
			int16_t ay; //Eixo Y Acelerometro
			int16_t az;	//Eixo Z Acelerometro
			int16_t gx; //Eixo X Giroscopio
			int16_t gy; //Eixo Y Giroscopio
			int16_t gz; //Eixo Z Giroscopio
			int16_t mx; //Eixo X Magnetometro
			int16_t my; //Eixo Y Magnetometro
			int16_t mz; //Eixo Z Magnetometro
			float temperatura; 
			float pressao;
			float altitude;
			int32_t lastMicros;
			ADXL345 accel; //Acelerometro
			L3G4200D gyro; //Gyroscopio
			BMP085 baro; //Barometro
			HMC5883L mag; //magnetometro		
		};    
#endif