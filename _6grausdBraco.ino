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
int destinoCintura, destinoOmbro, destinoCotovelo, destinoPulsoSD, destinoPulsoG, destinoGarra;
String comando, primeiro, segundo, terceiro, quarto, quinto, sexto, velocidade;

int passo(int origem, int destino){  
  return (destino - origem)/10;
  }

/**
 * Partindo do pressuposto que recebo no serial angulo de cada motor seguido de espaço ou virgula ou ponto e virgula seguido de char velocidade
*/
void processar(){
  if(comando.length() < 19){
    Serial.println("comando de entrada errado");
  }
  else if(comando.indexOf("inicial") >= 0){
    posicaoInicial();
  }
  else{  
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
  if(destinoPulsoG == 0 || destinoPulsoG < 10 || destinoPulsoG > 150){
      destinoPulsoG = pulsoG.read();
      Serial.println("PulsoG nao move, angulo invalido ou recebida ordem de nao mover");
  }
  if(destinoGarra == 0 || destinoGarra < 80 || destinoGarra > 140){
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
        
        if(velocidade.equalsIgnoreCase("r"))
          delay(15);
        else if(velocidade.equalsIgnoreCase("n"))
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
    velocidade = "l";
    movimentar();
}
  
void setup() {
  Serial.begin(9600); 
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
