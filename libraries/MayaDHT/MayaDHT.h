#ifndef MAYADHT_H
    #define MAYADHT_H
    #include <Arduino.h>
	#include <DHT.h>
	
	class MayaDHT{
		public:
			MayaDHT(int pino, unsigned char dht);
			
			void setPeriodo(int periodo);
			void setTempo(int tempo);
			void ativar(int tipo);
			float (&getDados(float (&dados)[2])) [2];
	
		private:
			int periodo_;
			int tempo_;
			float t_;
			float u_;
			int pino_;	
			unsigned char dht_;
	};    
#endif