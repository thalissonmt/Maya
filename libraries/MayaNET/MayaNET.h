#ifndef MAYANET_H
	#define MAYANET_h		
	#include "NTPClient.h"
	#include "WiFiUdp.h"
	#include "WiFiMulti.h"

	class MayaNET{
		public:
			MayaNET(const char* ssid, const char* password);

			void inicializar();
			void ativar(int tipo);
			String receberData();
			String receberHora();
		private:
			String data_;
			const char* ssid_;
			const char* password_;
	};

#endif