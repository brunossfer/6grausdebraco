/*g
vetor de shorts 

cintura             pino 3  faixa 10-100, pos ini 10
ombro               pino 11 faixa 50-140, pos ini 100
cotovelo            pino 9  faixa 50-170, pos ini 110
pulso sobe desce    pino 7  faixa 10-150, pos ini 130
pulso giratorio     pino 5  faixa 10-150, pos ini 150
garra               pino 13 faixa 80-150, pos ini 100

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

short passo(short origem, short destino){  
  return (destino - origem)/10;
  }

void movimentar(short destinoCintura, short destinoOmbro, short destinoCotovelo, short destinoPulsoSD, short destinoPulsoG, short destinoGarra, char velocidade){
  short vel;

  if(velocidade == 'l')
    vel = 100;
  else if(velocidade = 'n')
    vel = 50;
  else
    vel = 15;
    
    // mover em 10 passos 
  short moverCintura = passo(cintura.read(),destinoCintura);
  short moverOmbro = passo(ombro.read(),destinoOmbro);
  short moverCotovelo = passo(cotovelo.read(),destinoCotovelo);
  short moverPulsoSD = passo(pulsoSD.read(),destinoPulsoSD); 
  short moverPulsoG = passo(pulsoG.read(),destinoPulsoG);
  short moverGarra = passo(garra.read(),destinoGarra);
  
    for(short t = 0; t < 9; t++){
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

//---- tem que ser incremental, senão dá bosta por mexer rápido demais

void setup() {
  // associa servo aos nomes que os identificam
  cintura.attach(3);
  ombro.attach(11);
  cotovelo.attach(9);
  pulsoSD.attach(7);
  pulsoG.attach(5);
  garra.attach(13);

// posicoes iniciais
  cintura.write(10);
  ombro.write(100);
  cotovelo.write(110);
  pulsoSD.write(130);
  pulsoG.write(150);
  garra.write(100);

  Serial.begin(9600);
}

void loop() {  
  // velocidades
  delay(15);    // rapido
  delay(50);    // normal
  delay(100);   // lento

  if(valor recebido = 0)
    destino = atualposicao

}
