#include <Servo.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x04

//dados do raspberry
int data[70];
int pos = 0;
int flag = 0;
int response;

// criar os objetos servos
Servo cintura; 
Servo ombro;
Servo cotovelo;
Servo pulsoSD;
Servo pulsoG;
Servo garra;

char c;
int destinoCintura, destinoOmbro, destinoCotovelo, destinoPulsoSD, destinoPulsoG, destinoGarra, velocidade;

int passo(int origem, int destino){  
  return (destino - origem)/10;
  }

/**
 * Partindo do pressuposto que recebo no serial angulo de cada motor seguido de espaço ou virgula ou ponto e virgula seguido de char velocidade
*/
void processar(){
  destinoCintura = data[0];
  destinoOmbro = data[1];
  destinoCotovelo = data[2];
  destinoPulsoSD = data[3];
  destinoPulsoG = data[4];
  destinoGarra = data[5];  
  velocidade = data[6];
    
  Serial.print("cintura = ");
  Serial.println(data[0]);
  Serial.print("ombro = ");
  Serial.println(data[1]);
  Serial.print("cotovelo = ");
  Serial.println(data[2]);
  Serial.print("pulso sobe desce = ");
  Serial.println(data[3]);
  Serial.print("pulso gira = ");
  Serial.println(data[4]);
  Serial.print("garra = ");
  Serial.println(data[5]);
  Serial.print("velocidade = ");
  Serial.println(data[6]);
  Serial.println();
  Serial.println();
    
  movimentar();
  flag = 0;
  pos = 0;

}

/**
 * trata entrada de valor para dentro dos limites, caso receba 0 ou angulo invalido, nao ha movimento
 */
void tratar(){
  if(destinoCintura == 0 || destinoCintura < 10 || destinoCintura > 100){
      destinoCintura = cintura.read();
      Serial.println("Cintura nao move, angulo invalido ou recebida ordem de nao mover");
  }
  if(destinoOmbro == 0 || destinoOmbro < 50 || destinoOmbro > 140){
      destinoOmbro = ombro.read();
      Serial.println("Ombro nao move, angulo invalido ou recebida ordem de nao mover");
  }
  if(destinoCotovelo == 0 || destinoCotovelo < 50 || destinoCotovelo > 170){
      destinoCotovelo = cotovelo.read();
      Serial.println("Cotovelo nao move, angulo invalido ou recebida ordem de nao mover");
  }
  if(destinoPulsoSD == 0 || destinoPulsoSD < 10 || destinoPulsoSD > 150){
      destinoPulsoSD = pulsoSD.read();  
      Serial.println("PulsoSD nao move, angulo invalido ou recebida ordem de nao mover");
  }
  if(destinoPulsoG == 0 || destinoPulsoG < 10 || destinoPulsoG > 151){
      destinoPulsoG = pulsoG.read();
      Serial.println("PulsoG nao move, angulo invalido ou recebida ordem de nao mover");
  }
  if(destinoGarra == 0 || destinoGarra < 80 || destinoGarra > 145){
      destinoGarra = garra.read();   
      Serial.println("Garra nao move, angulo invalido ou recebida ordem de nao mover");
  }  
}

/**
 * faz movimentacao dos motores utilizando os valores encontrados nas variaveis globais de destino
 */
void movimentar(){
  int moverCintura, moverOmbro, moverCotovelo, moverPulsoSD, moverPulsoG, moverGarra;

    // segura possiveis erros de comando
    tratar();

    // mover em 10 passos 
    moverCintura = passo(cintura.read(),destinoCintura);
    moverOmbro = passo(ombro.read(),destinoOmbro);
    moverCotovelo = passo(cotovelo.read(),destinoCotovelo);
    moverPulsoSD = passo(pulsoSD.read(),destinoPulsoSD);
    moverPulsoG = passo(pulsoG.read(),destinoPulsoG);
    moverGarra = passo(garra.read(),destinoGarra);
    
    for(int t = 0; t < 9; t++){
        cintura.write(cintura.read() + moverCintura);
        ombro.write(ombro.read() + moverOmbro);
        cotovelo.write(cotovelo.read() + moverCotovelo);
        pulsoSD.write(pulsoSD.read() + moverPulsoSD);
        pulsoG.write(pulsoG.read() + moverPulsoG);
        garra.write(garra.read() + moverGarra);
        
        if(velocidade == 2)
          delay(15);
        else if(velocidade == 1)
          delay(50);
        else
          delay(100);
      }

    cintura.write(destinoCintura);
    ombro.write(destinoOmbro);
    cotovelo.write(destinoCotovelo);
    pulsoSD.write(destinoPulsoSD);
    pulsoG.write(destinoPulsoG);    
    garra.write(destinoGarra);
  }


/**
 * da valores de posicao inicial 'as variaveis globais
 */
void posicaoInicial(){
// pos ini 10 100 110 130 150 100 n
    destinoCintura = 10;
    destinoOmbro = 100;
    destinoCotovelo = 110;
    destinoPulsoSD = 130;
    destinoPulsoG = 150;
    destinoGarra = 100;
    velocidade = 0;
    movimentar();
}

/**
 * Metodo para receber requisicao do raspberry
 */
void receiveData(int byteCount) {

  while (Wire.available()) {
    data[pos] = Wire.read();
    if (data[pos] != 255){
      pos++;
    }
    else{
      flag = 1;
    }      
  }
}

/**
 * Metodo para enviar dados do raspberry
 */
void sendData() {
  Wire.write(response);
}

/**
 * Inicializacao das variaveis
 */
void setup() {
  Serial.begin(9600); 
  
  //remover dados do arduino
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  
  // associa servo aos nomes que os identificam 
  cintura.attach(3);      //cintura             pino 3    faixa 10-100, pos ini 10
  ombro.attach(5);        //ombro               pino 5    faixa 50-140, pos ini 100
  cotovelo.attach(6);     //cotovelo            pino 6    faixa 50-170, pos ini 110
  pulsoSD.attach(9);      //pulso sobe desce    pino 9    faixa 10-150, pos ini 130
  pulsoG.attach(10);      //pulso giratorio     pino 10   faixa 10-150, pos ini 150
  garra.attach(11);       //garra               pino 11    faixa 80-140, pos ini 100

  delay(1000);
  posicaoInicial();
}

void loop(){
  if(flag == 1){
    processar();
  }
}
