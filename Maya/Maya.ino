#include <MayaNET.h>    //FUNCIONANDO
#include <MayaMPU.h>    //FUNCIONANDO
#include <MayaDHT.h>    //FUNCIONANDO
#include <MayaLED.h>    //FUNCIONANDO
#include <MayaLDR.h>    //FUNCIONANDO
#include <MayaTI.h>     //FUNCIONANDO
#include <MayaNuvem.h>  //FUNCIONANDO
#include <ArduinoJson.h>

MayaNET net("MAYA_NET","projetomaya"); //passar como parametro ("nome_da_rede","senha_da_rede")
MayaMPU mpu(22,21);
MayaDHT dht(16,DHT11);
MayaLED led(5,19,23);
MayaLDR ldr(32);    
MayaTI ti(4);
MayaNuvem nuvem;

const int dados = JSON_OBJECT_SIZE(24);
StaticJsonDocument<dados> doc;

int anoInicio;
int mesInicio;
int diaInicio;
int horaInicio;
int minInicio;
int segInicio;
int anoFim;
int mesFim;
int diaFim;
int horaFim;
int minFim;
int segFim;
float ti_lida[1] = {};
float dados_ti;

void atualizarDataHoraInicio(){
  net.atualizarDataHora();
  horaInicio = net.receberHora(); 
  minInicio = net.receberMin(); 
  segInicio = net.receberSeg(); 
  anoInicio = net.receberAno(); 
  mesInicio = net.receberMes(); 
  diaInicio = net.receberDia(); 
  nuvem.setTempo(millis()); //Atualizar o contator para o momento que recebeu a hora 
}

void setup() {
  Serial.begin(9600);
  led.inicializar();
  led.branco(0);
  net.inicializar();
  mpu.inicializar();
  
  led.desligar();

  atualizarDataHoraInicio();
}

void loop() {
  mpu.ativar(0);
  ldr.ativar(0);
  net.ativar(0); 
  dht.ativar(0);
  ti.ativar(0);

  ti.getDados(ti_lida);
  if(ti_lida[0]>0){
    dados_ti = ti_lida[0];
    led.verde(0);
  }else{
    led.desligar();
  }

  if(nuvem.ativar()){
    net.atualizarDataHora(); //Receber a data de fim da leitura
    horaFim = net.receberHora(); 
    minFim = net.receberMin(); 
    segFim = net.receberSeg(); 
    anoFim = net.receberAno(); 
    mesFim = net.receberMes(); 
    diaFim = net.receberDia();
    
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
    if(dados_ti>0){
      doc["temp_int"] = dados_ti;
      dados_ti = 0;
    }
    
    doc["ano_ini"] = anoInicio;
    doc["mes_ini"] = mesInicio;
    doc["dia_ini"] = diaInicio;
    doc["hr_ini"] = horaInicio;
    doc["min_ini"] = minInicio;
    doc["seg_ini"] = segInicio;

    doc["ano_fim"] = anoFim;
    doc["mes_fim"] = mesFim;
    doc["dia_fim"] = diaFim;
    doc["hr_fim"] = horaFim;
    doc["min_fim"] = minFim;
    doc["seg_fim"] = segFim;

    nuvem.enviar(doc);
    atualizarDataHoraInicio();
  }
}
