#ifndef MAYABLE_H
    #define MAYABLE_H
    #include <Arduino.h>
	#include <BLEDevice.h>
	
	class MayaBLE{
		public:
			MayaBLE();

			void setPeriodo(int periodo);
			void setTempo(int tempo);
			void ativar(int tipo);
			int (&getDados(int (&dados)[1])) [1];
			void montar();
	
		private:
			int periodo_;
			int tempo_;
			//int batimentos_;
	};    
	

#endif