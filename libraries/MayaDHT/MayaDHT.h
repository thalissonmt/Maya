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
			int (&getDados(int (&dados)[2])) [2];
	
		private:
			int periodo_;
			int tempo_;
			int pino_;	
			unsigned char dht_;
			float t_;
			float u_;
	};    
#endif