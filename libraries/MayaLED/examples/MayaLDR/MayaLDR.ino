#include <MayaLDR.h>

MayaLDR ldr(13);

void setup() {}

void loop() {
  led.ativar();
  delay(500);
  led.debug();
}