// Plantilla de código para la práctica de laboratorio #4 de Microprocesadores
// Eduardo Corpeño
// Universidad Galileo, FISICC

#include "LPC11xx.h" 
#define puerto1  LPC_GPIO1->DATA
#define puerto2  LPC_GPIO2->DATA
#define puerto3  LPC_GPIO3->DATA
#define pinLEDRojo 9
#define pinLEDVerde 10
#define pinLEDAzul 2
#define pinPrimerSentido 1
#define pinSegundoSentido 2
#define pinTercerSentido 3
#define pinCuartoSentido 4
#define pinPush 0
 
#define MASK(x) (1UL << (x))

char sentido1() {
  return !(puerto2 & MASK(pinPrimerSentido));
}

char sentido2() {
  return !(puerto2 & MASK(pinSegundoSentido));
}

char sentido3() {
  return !(puerto2 & MASK(pinTercerSentido));
}

char sentido4() {
  return !(puerto3 & MASK(pinCuartoSentido));
}

char push() {
  return !(puerto2 & MASK(pinPush));
}

void apagar() {
  puerto1 &= ~(MASK(pinLEDRojo));
  puerto1 &= ~(MASK(pinLEDVerde));
  puerto1 &= ~(MASK(pinLEDAzul));
}

void encender(char color) {
  apagar();
  switch(color) {
    case 'r':
      puerto1 |= (MASK(pinLEDRojo));
      break;
    case 'g':
      puerto1 |= (MASK(pinLEDVerde));
      break;
    case 'b':
      puerto1 |= (MASK(pinLEDAzul));
      break;
    case 'q':
      puerto1 |= (MASK(pinLEDVerde));
      puerto1 |= (MASK(pinLEDAzul));
      break;
    case 'a':
      puerto1 |= (MASK(pinLEDRojo));
      puerto1 |= (MASK(pinLEDVerde));
      puerto1 |= (MASK(pinLEDAzul));
      break;     
  }
}

void configure() {
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6); //Habilitando clock para el GPIO
  
  // HABILITANDO PINES DE ENTRADA
  LPC_GPIO2->DIR &= ~MASK(1); // sentido 1
  LPC_GPIO2->DIR &= ~MASK(2); // sentido 2
  LPC_GPIO2->DIR &= ~MASK(3); // sentido 3
  LPC_GPIO3->DIR &= ~MASK(4); // sentido 4
  LPC_GPIO2->DIR &= ~MASK(0); // presionar
  
  // HABILITANDO PINES DE SALIDA
  LPC_GPIO1->DIR |= MASK(9); // rojo
  LPC_GPIO1->DIR |= MASK(10); // verde
  LPC_GPIO1->DIR |= MASK(2); // azul
  
  // HABILITANDO GPIO PARA EL PIN PIO1_2
  LPC_IOCON->R_PIO1_2 = (LPC_IOCON->R_PIO1_2 & ~0x7) | 0x1;
  
}
int main(void){
  configure();
	apagar();
  while(1){
    if(sentido4()) //Arriba
      encender('g');
    else if(sentido3()) //Abajo
      encender('r');
    else if(sentido2()) //Derecha
      encender('q');
    else if(sentido1()) //Izquierda
      encender('a'); //Green,Blue like aQua 
    else if(push()) // Push
      encender('b'); // a of All
    else
      apagar(); 
  }
}

// *******************************ARM University Program Copyright & ARM Ltd 2013*************************************   
