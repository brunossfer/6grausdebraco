/*
vetor de ints 

cintura             pino 3    faixa 10-100, pos ini 10
ombro               pino 5    faixa 50-140, pos ini 100
cotovelo            pino 7    faixa 50-170, pos ini 110
pulso sobe desce    pino 9    faixa 10-150, pos ini 130
pulso giratorio     pino 11   faixa 10-150, pos ini 150
garra               pino 13    faixa 80-150, pos ini 100

velocidade delay 15 rápido, 50 normal, 100 lento

Serial read
http://forum.arduino.cc/index.php?topic=396450.0
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

int destinoCintura = 10;
int destinoOmbro = 100;
int destinoCotovelo = 110;
int destinoPulsoSD = 130;
int destinoPulsoG = 150;
int destinoGarra = 100;
char velocidade = 'l';

int passo(int origem, int destino){  
  return (destino - origem)/10;
  }

void movimentar(){
  int vel, moverCintura, moverOmbro, moverCotovelo, moverPulsoSD, moverPulsoG, moverGarra;

  if(velocidade == 'l')
    vel = 100;
  else if(velocidade = 'n')
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
  cotovelo.attach(7);
  pulsoSD.attach(9);
  pulsoG.attach(11);
  garra.attach(13);
}
/* observar pulsoSD, parece ter algo estranho com ele */
//--- ate aqui ta certo---//

void loop() {  
  // suponho que serao enviados os 7 valores numericos em ordem, 
  // a posicao de cintura, ombro, cotovelo, pulso, pulso e garra
  // seguido da velocidade... suponho que vem o numero separado por espaço
  if(Serial.available() > 0){
    Serial.println("E la vamos nos");
    destinoCintura = Serial.parseInt();
        Serial.println(destinoCintura);
    destinoOmbro = Serial.parseInt();
        Serial.println(destinoOmbro);
    destinoCotovelo = Serial.parseInt();
        Serial.println(destinoCotovelo);
    destinoPulsoSD = Serial.parseInt();
        Serial.println(destinoPulsoSD);
    destinoPulsoG = Serial.parseInt();
        Serial.println(destinoPulsoG);
    destinoGarra = Serial.parseInt();
        Serial.println(destinoGarra);
    velocidade = Serial.read();
        Serial.println(velocidade);
    Serial.flush();

    // problema: serial não pega o char e tá lendo de novo e pegando so 0
    
    //movimentar(destinoCintura, destinoOmbro, destinoCotovelo, destinoPulsoSD, destinoPulsoG, destinoGarra, velocidade);
  }

}
