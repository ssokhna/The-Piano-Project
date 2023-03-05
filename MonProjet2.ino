//pour le son
#include <Audio.h>
#include "midi.h"
//hc-06
#include <SoftwareSerial.h>
#define RxD 0 
#define TxD 1  
SoftwareSerial HC06(RxD,TxD);  //(RX,TX)
String msg;

midi midi1;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(midi1,0,out,0);
AudioConnection patchCord1(midi1,0,out,1);

void midi(float freq){
  //fonction qui permet de mettre le son en continue tant qu'un bouton est enfoncé sur l'application
  midi1.setParamValue("freq",freq);
 midi1.setParamValue("gain",0.8);
 midi1.setParamValue("gate",1);
 midi1.setParamValue("echo",0.1);
}

void mute(){
  delay(10);
  midi1.setParamValue("gate",0);
  //si le bouton est relaché, un signal est recu 
  //attendre 10ms secondes avant de muter 
  //pour ne pas interrompre le prochain midi en cours
}

void setup()  
{ 
  AudioMemory(2);
 audioShield.enable();
 audioShield.volume(0.7);
  Serial.begin(9600);
  pinMode(RxD, INPUT);    
  HC06.begin(9600);
}

void loop() {
  while (HC06.available())                  
   {
    delay(3);
    char c = HC06.read();
    msg +=c;
    //le message est recu charactere par charactere 
  }
  if (msg.length() > 0 )
  {
        if (msg == "son")
       {Serial.println("connexion activée");}
       
        else if (msg == "do1")
       {Serial.println("DO");
        midi(261.626);}
       
        else if (msg == "re1")
       {Serial.println("RE");
       midi(293.665);}
       
       else if (msg == "mi1")
       {Serial.println("MI");
        midi(329.628);}
       
       else if (msg == "fa1")
       {Serial.println("FA");
        midi(349.228);}
       
       else if (msg == "sol1")
       {Serial.println("SOL");
        midi(391.995);}
      
       else if (msg == "la1")
       {Serial.println("LA");
        midi(349.228);}
        
       else if (msg == "si1")
       {Serial.println("SI");
        midi(246.642);}
      
       else
       {mute();}
       //si le message recu est autre que ceux ci dessus alors muter le son
       
  }
      msg="";  
      
     
  };
