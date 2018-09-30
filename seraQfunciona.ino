#include <Servo.h>
Servo cintura; 
Servo ombro;
Servo cotovelo;
Servo pulsoSD;
Servo pulsoG;
Servo garra;

char c;
int destinoCintura = 10;
int destinoOmbro = 100;
int destinoCotovelo = 110;
int destinoPulsoSD = 130;
int destinoPulsoG = 150;
int destinoGarra = 100;
String comando, primeiro, segundo, terceiro, quarto, quinto, sexto;

void processar(){
  primeiro = comando.substring(0,comando.indexOf(' ')); // primeiro
  comando = comando.substring(comando.indexOf(' ')+1);
  destinoCintura = primeiro.toInt();
  
  segundo = comando.substring(0,comando.indexOf(' ')); // segundo
  comando = comando.substring(comando.indexOf(' ')+1);
  destinoOmbro = segundo.toInt();
  
  terceiro = comando.substring(0,comando.indexOf(' ')); // terceiro
  comando = comando.substring(comando.indexOf(' ')+1);
  destinoCotovelo = terceiro.toInt();
  
  quarto = comando.substring(0,comando.indexOf(' ')); // quarto
  comando = comando.substring(comando.indexOf(' ')+1);
  destinoPulsoSD = quarto.toInt();
  
  quinto = comando.substring(0,comando.indexOf(' ')); // quinto
  comando = comando.substring(comando.indexOf(' ')+1);
  destinoPulsoG = quinto.toInt();
   
  sexto = comando.substring(0,comando.indexOf(' ')); // sexto
  comando = comando.substring(comando.indexOf(' ')+1);
  destinoGarra = sexto.toInt();
  
  Serial.print("cintura = ");
  Serial.println(primeiro);
  Serial.print("ombro = ");
  Serial.println(segundo);
  Serial.print("cotovelo = ");
  Serial.println(terceiro);
  Serial.print("pulso sobe desce = ");
  Serial.println(quarto);
  Serial.print("pulso gira = ");
  Serial.println(quinto);
  Serial.print("garra = ");
  Serial.println(sexto);
  Serial.println();
  Serial.println();
  
  cintura.write(destinoCintura);
  ombro.write(destinoOmbro);
  cotovelo.write(destinoCotovelo);
  pulsoSD.write(destinoPulsoSD);
  pulsoG.write(destinoPulsoG);
  garra.write(destinoGarra);
}

void setup() {
  // initialize serial:
  Serial.begin(9600); //set serial monitor baud rate to match
 
  cintura.attach(3);
  //ombro.attach(5);
  //cotovelo.attach(6);
  //pulsoSD.attach(9);
  //pulsoG.attach(10);
  //garra.attach(11);
}

void loop() {
  // if there's any serial available, read it:
if(Serial.available() > 0){
  c = Serial.read();
  comando += c;
  if(c == '\n'){
      // acabou
      Serial.print("recebido = ");
      Serial.println(comando);
      processar();
      comando = "";
    }
  }
} 
