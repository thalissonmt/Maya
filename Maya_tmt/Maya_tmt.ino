//#include <MayaMPU.h>    //FUNCIONANDO
#include <MayaNET.h>    //FUNCIONANDO
//#include <MayaDHT.H>

//MayaMPU mpu(22,21);
MayaNET internet("Main Fake","acm2017.2"); //passar como parametro ("nome_da_rede","senha_da_rede")

void setup() {
  Serial.begin(9600);
  
  //mpu.inicializar();
  internet.inicializar();
}

void loop() {
  //mpu.ativar(1);
  internet.ativar(1); 
  delay(1000);
}
