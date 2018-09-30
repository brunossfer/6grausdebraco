/*
vetor de ints 

cintura             pino 3    faixa 10-100, pos ini 10
ombro               pino 5    faixa 50-140, pos ini 100
cotovelo            pino 6    faixa 50-170, pos ini 110
pulso sobe desce    pino 9    faixa 10-150, pos ini 130
pulso giratorio     pino 10   faixa 10-150, pos ini 150
garra               pino 11    faixa 80-150, pos ini 100

velocidade delay 15 rápido, 50 normal, 100 lento

*/


// bib de servos
#include <Servo.h>

// criar os objetos servos
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
String comando, primeiro, segundo, terceiro, quarto, quinto, sexto, velocidade;

int passo(int origem, int destino){  
  return (destino - origem)/10;
  }

void movimentar(){
  int vel, moverCintura, moverOmbro, moverCotovelo, moverPulsoSD, moverPulsoG, moverGarra;

  if(velocidade.equalsIgnoreCase("l"))
    vel = 100;
  else if(velocidade.equalsIgnoreCase("n"))
    vel = 50;
  else
    vel = 15;

    // se nao for mexer, o passo e 0
    moverCintura = 0;
    moverOmbro = 0;
    moverCotovelo = 0;
    moverPulsoSD = 0;
    moverPulsoG = 0;
    moverGarra = 0;
    
    // mover em 10 passos 
    if(destinoCintura != 0)
      moverCintura = passo(cintura.read(),destinoCintura);
    if(destinoOmbro != 0)  
      moverOmbro = passo(ombro.read(),destinoOmbro);
    if(destinoCotovelo != 0)
      moverCotovelo = passo(cotovelo.read(),destinoCotovelo);
    if(destinoPulsoSD != 0)
      moverPulsoSD = passo(pulsoSD.read(),destinoPulsoSD); 
    if(destinoPulsoG != 0)
      moverPulsoG = passo(pulsoG.read(),destinoPulsoG);
    if(destinoGarra != 0)
      moverGarra = passo(garra.read(),destinoGarra);
  
    for(int t = 0; t < 9; t++){
        cintura.write(cintura.read() + moverCintura);
        ombro.write(ombro.read() + moverOmbro);
        cotovelo.write(cotovelo.read() + moverCotovelo);
        pulsoSD.write(pulsoSD.read() + moverPulsoSD);
        pulsoG.write(pulsoG.read() + moverPulsoG);
        garra.write(garra.read() + moverGarra);
        delay(vel);
      }
   
    cintura.write(destinoCintura);
    ombro.write(destinoOmbro);
    cotovelo.write(destinoCotovelo);
    pulsoSD.write(destinoPulsoSD);
    pulsoG.write(destinoPulsoG);
    garra.write(destinoGarra);
  }

/**
 * Partindo do pressuposto que recebo no serial angulo de cada motorseguido de espaço ou virgula ou ponto e virgula seguido de char velocidade
*/
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

  velocidade = comando.substring(0,comando.indexOf(' ')); // sexto
  
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
  Serial.print("velocidade = ");
  Serial.println(velocidade);
  Serial.println();
  Serial.println();
  
  movimentar();
  }
  
void setup() {
  Serial.begin(9600);
  // posicoes iniciais
  cintura.write(10);
  ombro.write(100);
  cotovelo.write(110);
  pulsoSD.write(90);
  pulsoG.write(150);
  garra.write(100);
  
 // associa servo aos nomes que os identificam 
  cintura.attach(3);
  ombro.attach(5);
  cotovelo.attach(6);
  pulsoSD.attach(9);
  pulsoG.attach(10);
  garra.attach(11);
}


void loop(){
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
