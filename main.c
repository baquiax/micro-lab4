// Plantilla de c�digo para la pr�ctica de laboratorio #4 de Microprocesadores
// Eduardo Corpe�o
// Universidad Galileo, FISICC

#include "LPC11xx.h" 

#define MASK(x) (1UL << (x))

void arriba() {
  
}

void abajo() {
  
}

void derecha() {
  
}

void izquierda() {
  
}

void encender(char color) {
  switch(color) {
    case 'r':
      break;
    case 'g':
      break;
    case 'b':
      break;
    case 'q':
      break;
    case 'a':
      break;     
  }
}

void apagar() {
  
}

void configure() {
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6); //Habilitando clock para el GPIO
  
  // HABILITANDO PINES DE ENTRADA
  LPC_GPIO2->DIR |= MASK(1); // sentido 1
  LPC_GPIO2->DIR |= MASK(2); // sentido 2
  LPC_GPIO2->DIR |= MASK(3); // sentido 3
  LPC_GPIO3->DIR |= MASK(4); // sentido 4
  LPC_GPIO2->DIR |= MASK(0); // presionar
  
  // HABILITANDO PINES DE SALIDA
  LPC_GPIO1->DIR &= ~MASK(9); // rojo
  LPC_GPIO1->DIR &= ~MASK(10); // verde
  LPC_GPIO1->DIR &= ~MASK(2); // azul
  
}
int main(void){
  // escriba su c�digo aqu�
  configure();
  while(1){
    if(arriba())
      encender('r');
    else if(abajo())
      encender('g');
    else if(derecha())
      encender('b');
    else if(izquierda())
      encender('q'); //Green,Blue like aQua 
    else if(boton())
      encender('a'); // a of All
    else
      apagar(); 
  }
}

// *******************************ARM University Program Copyright � ARM Ltd 2013*************************************   
