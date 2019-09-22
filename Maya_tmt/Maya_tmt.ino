#include <MayaMPU.h>    //FUNCIONANDO
#include <MayaNET.h>    //FUNCIONANDO
#include <MayaDHT.h>    //FUNCIONANDO

MayaMPU mpu(22,21);
MayaNET internet("iPhone de Thalisson","k0u3jtc2"); //passar como parametro ("nome_da_rede","senha_da_rede")
MayaDHT dht(16,DHT11);

void setup() {
  Serial.begin(9600);
  
  mpu.inicializar();
  internet.inicializar();
}

void loop() {
  mpu.ativar(1);
  internet.ativar(1); 
  dht.ativar(1);
  
}
