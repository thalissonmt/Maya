#include <MayaMPU.h>    //FUNCIONANDO

MayaMPU mpu(22,21);

void setup() {

   Serial.begin(9600);
   mpu.inicializar();
}

void loop() {
  mpu.ativar(1);
}
