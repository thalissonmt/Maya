#ifndef MAYAMPU_H
    #define MAYAMPU_H
    #include <Arduino.h>
	#include <Wire.h>
	
	class MayaMPU{
		public:
			MayaMPU(int pinosda, int pinoscl);
			
			void setPeriodo(int periodo);
			void setTempo(int tempo);
			void ativar(int tipo);
			int (&getDados(int (&dados)[4])) [4];
			void montar();
	
		private:
			int periodo_;
			int tempo_;
			int pinosda_;
			int pinoscl_;
			int AcX;
			int AcY;
			int AcZ;			
			int MPU_ADDR_;
			int WHO_AM_I_;
			int PWR_MGMT_1_;
			int GYRO_CONFIG_; 
			int ACCEL_CONFIG_; 
			int ACCEL_XOUT_;
			uint8_t data_;
			int sentado_;
			int deitado_;
			int empe_;
			int passos_;
			int reg_;
			int val_;
		};    
#endif