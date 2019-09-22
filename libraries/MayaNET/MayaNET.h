#ifndef MAYANET_H
	#define MAYANET_h		
	#include "NTPClient.h"
	#include "WiFiUdp.h"
	#include "WiFiMulti.h"

	class MayaNET{
		public:
			MayaNET(const char* ssid, const char* password);

			void setPeriodo(int periodo);
			void setTempo(int tempo);
			void inicializar();
			void ativar(int tipo);
			String receberData();
			String receberHora();
			unsigned long receberEpoch();
			
		private:
			String data_;
			const char* ssid_;
			const char* password_;
			int periodo_;
			int tempo_;
	};

#endif