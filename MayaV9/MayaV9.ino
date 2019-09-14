#include <MayaLDR.h>

#include <MayaLED.h>
#include <MayaNuvem.h>  //FUNCIONANDO

#include <MayaTI.h>     //APARENTEMENTE FUNCIONANDO
#include <MayaDHT.h>    //FUNCIONANDO
#include <MayaMPU.h>    //FUNCIONANDO
#include <ArduinoJson.h>//FUNCIONANDO 
#include <MayaBLE.h>    //APARENTEMENTE FUNCIONANDO
#include <WiFiMulti.h>  //FUNCIONANDO
#include "time.h"

MayaLDR ldr(32);
MayaDHT dht(16, DHT11);
MayaMPU mpu(22,21);

//WiFiMulti WiFiMulti;
//MayaNuvem nuvem;

//MayaTI ti(4);
//MayaBLE ble;

//MayaLED led(5,19,23);

/*
const int dados = JSON_OBJECT_SIZE(15);
StaticJsonDocument<dados> doc;
*/
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = -3600*3;

String datahoraInicio;
String datahoraFim;

String getLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return "Time Error";
  }
  char output[80];
  strftime(output, 80, "%Y-%m-%d %H:%M:%S", &timeinfo);
  datahoraFim = String(output);
  return String(output);
}

int cor;

const int azul = 23;
const int verde = 19;
const int vermelho = 5;

void setup() {
  /*
  WiFiMulti.addAP("BBG_MARTINS", "q1w2e3r4");
  while(WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  //mpu.montar();
  configTime(0, 0, "pool.ntp.org");
  */
  
   Serial.begin(9600);
   pinMode(azul, OUTPUT);
   pinMode(verde, OUTPUT);
   pinMode(vermelho, OUTPUT);
}


//Funções responsáveis por executar o brilho selecionado

void vermelhoFuncao(){
  Serial.println("F1");
  digitalWrite(vermelho, 255);
  digitalWrite(azul, 0);
  digitalWrite(verde, 0);
}
void azulFuncao(){
  Serial.println("F2");
  digitalWrite(azul, 255);
  digitalWrite(verde, 0);
  digitalWrite(vermelho, 0);
}
void verdeFuncao(){
  Serial.println("F3");
  digitalWrite(verde, 255);
  digitalWrite(azul, 0);
  digitalWrite(vermelho, 0);
}

void brancoFuncao(){
  digitalWrite(azul, HIGH);
  digitalWrite(verde, HIGH);
  digitalWrite(vermelho, HIGH);
}

void loop() {
ldr.ativar(1);
dht.ativar(1);
mpu.ativar(1);

  
    vermelhoFuncao();
    delay(2000);
    azulFuncao();
    delay(2000);
    verdeFuncao();
    delay(2000);

  
/*
    if(Serial.available()){
      cor = Serial.readString();
      Serial.println(cor);
    }
  
    if(cor == "Vermelho"){
      led.vermelho();
    }
    if(cor == "Azul"){
      led.azul();
    }
    if(cor == "Verde"){
      led.verde();
    }
    /*
    if(cor == "Amarelo"){
      led.amarelo();
    }
    if(cor == "Roxo"){
      led.roxo();
    }
    if(cor == "Branco"){
      led.branco();
    } 
*/
/*
  ldr.ativar(1);
  dht.ativar(1);
  mpu.ativar(1);
  
  //ti.ativar(1);
  //ble.ativar(1);

  if ( nuvem.ativar() ){
    getLocalTime();
    int dados_ldr[3] = {};
    ldr.getDados(dados_ldr);

    doc["codigo"] = 1;

    doc["luz_c"]  = dados_ldr[1];
    doc["luz_s"]  = dados_ldr[2];
    doc["luz_e"]  = dados_ldr[3];

    int dados_dht[2] = {};
    dht.getDados(dados_dht);  
    
    doc["temp"] = dados_dht[1];
    doc["umid"] = dados_dht[2];

    int dados_mpu[4] = {};
    mpu.getDados(dados_mpu);
    
    doc["pos_sent"]   = dados_mpu[1];  
    doc["pos_empe"]   = dados_mpu[2];
    doc["pos_deita"]  = dados_mpu[3];
    doc["passos"]     = dados_mpu[4];
    
    doc["dthr_ini"] = datahoraInicio;
    doc["dthr_fim"] = datahoraFim;

    //int dados_ble[1] = {};
    //ble.getDados(dados_ble);
    //doc["cardiaco"] = dados_ble[1];
    //setDataHora("FIM");
    //setDataHora("ZERO")

    nuvem.enviar(doc);
 }
*/

}
