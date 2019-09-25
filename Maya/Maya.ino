#include <MayaNET.h>    //FUNCIONANDO
#include <MayaMPU.h>    //FUNCIONANDO
#include <MayaDHT.h>    //FUNCIONANDO
#include <MayaLED.h>    //FUNCIONANDO
#include <MayaLDR.h>    //FUNCIONANDO
#include <MayaTI.h>     //FUNCIONANDO
//#include <MayaBLE.h>    //FUNCIONANDO
#include <MayaNuvem.h>  //FUNCIONANDO
#include <ArduinoJson.h>

MayaNET net("MAYA_NET","projetomaya"); //passar como parametro ("nome_da_rede","senha_da_rede")
//MayaNET net("iPhone de Thalisson","k0u3jtc2"); 
MayaMPU mpu(22,21);
MayaDHT dht(16,DHT11);
MayaLED led(5,19,23);
MayaLDR ldr(32);    
MayaTI ti(4);
//MayaBLE ble;
MayaNuvem nuvem;

const int dados = JSON_OBJECT_SIZE(17);
StaticJsonDocument<dados> doc;

String dataInicio;
String horaInicio;
String dataFim;
String horaFim;
float ti_lida[1] = {};
float dados_ti;

void atualizarDataHoraInicio(){
  dataInicio = net.receberData();
  horaInicio = net.receberHora(); 
  nuvem.setTempo(millis()); //Atualizar o contator para o momento que recebeu a hora 
  Serial.println(horaInicio);
}

void setup() {
  Serial.begin(9600);
  led.inicializar();
  led.branco(0);
  net.inicializar();
  mpu.inicializar();
 // ble.inicializar();
  
  led.desligar();

  atualizarDataHoraInicio();
}

void loop() {
  mpu.ativar(0);
  ldr.ativar(0);
  net.ativar(0); 
  dht.ativar(0);
  ti.ativar(0);
 // ble.ativar(0);

  ti.getDados(ti_lida);
  if(ti_lida[0]>0){
    dados_ti = ti_lida[0];
    led.verde(0);
  }else{
    led.desligar();
  }

  if(nuvem.ativar()){
    dataFim = net.receberData(); //Receber a data de fim da leitura
    horaFim = net.receberHora(); //Receber a hora de fim da leitura
    
    doc["codigo"] = 1;
    
    int dados_ldr[3] = {};
    ldr.getDados(dados_ldr);
    Serial.print("LDR: "); Serial.print(" C: "); Serial.print(dados_ldr[0]); Serial.print(" S: ");  Serial.print(dados_ldr[1]); Serial.print(" E: "); Serial.print(dados_ldr[2]); Serial.print(" Lumi: "); Serial.println(ldr.luminosidade());
    doc["luz_c"]  = dados_ldr[0];
    doc["luz_s"]  = dados_ldr[1];
    doc["luz_e"]  = dados_ldr[2];

    float dados_dht[2] = {};
    dht.getDados(dados_dht);  
    Serial.print("DHT: "); Serial.print(" Temp: "); Serial.print(dados_dht[0]); Serial.print(" Umid: ");  Serial.println(dados_dht[1]);
    doc["temp"] = dados_dht[0];
    doc["umid"] = dados_dht[1];

    int dados_mpu[4] = {};
    mpu.getDados(dados_mpu);
    Serial.print("MPU: "); Serial.print(" S: "); Serial.print(dados_mpu[0]); Serial.print(" PE: ");  Serial.print(dados_mpu[1]); Serial.print(" D: "); Serial.print(dados_mpu[2]); Serial.print(" P: "); Serial.println(dados_mpu[3]);
    doc["pos_sent"]   = dados_mpu[0];  
    doc["pos_empe"]   = dados_mpu[1];
    doc["pos_deita"]  = dados_mpu[2];
    doc["passos"]     = dados_mpu[3];

    Serial.print("TI: "); Serial.print(" Temp_Int: "); Serial.println(dados_ti);
    doc["temp_int"] = dados_ti;
    dados_ti = 0;
    
    doc["dt_ini"] = dataInicio;
    doc["hr_ini"] = horaInicio;
    doc["dt_fim"] = dataFim;
    doc["hr_fim"] = horaFim;

//    int dados_ble[1] = {};
//    ble.getDados(dados_ble);
//    Serial.print("BLE - Batimento: "); Serial.println(dados_ble[0]);
//    doc["cardiaco"] = dados_ble[0];

    nuvem.enviar(doc);
    atualizarDataHoraInicio();
  }
}
