#include "bico.h"

unsigned int emparelha();

void _start(void)
{
  unsigned int distancias[16];
  unsigned int flag = 20;
  unsigned int flag2 = 1;

  unsigned int distancia_referencia;

  motor_cfg_t motor0;
  motor_cfg_t motor1;

  motor0.id = 0;
  motor1.id = 1;

  motor0.speed = 32;
  motor1.speed = 32;
  set_motors_speed(&motor0, &motor1);

  while(1)
  {
    distancias[3] = read_sonar(3);
    distancias[4] = read_sonar(4);
    while((distancias[3] > 1000) && (distancias[4] > 1000))
    {
      distancias[3] = read_sonar(3);
      distancias[4] = read_sonar(4);
    }

    motor0.speed = 0;
    motor1.speed = 5;
    set_motors_speed(&motor0, &motor1);

    distancia_referencia = emparelha();

    motor0.speed = 32;
    motor1.speed = 32;
    set_motors_speed(&motor0, &motor1);
  }
}

/*Funcao que, caso o robo encontre uma parede, emparelha-o com ela*/
unsigned int emparelha()
{

  unsigned int distancia0;
  unsigned int distancia15;

  motor_cfg_t motor0;
  motor_cfg_t motor1;

  int diferenca_distancia = 30;

  /*Verifica se a diferenca entre as distancias dos radares eh baixa, indicando que estao em paralelo com a parede*/
  while(diferenca_distancia > 10)
  {
    distancia0 = read_sonar(0);
    distancia15 = read_sonar(15);

    if((distancia0 >= distancia15) && (distancia0 < 1000) && (distancia15 < 1000))
    {
      diferenca_distancia = distancia0 - distancia15;
    }
    else if((distancia0 <= distancia15) && (distancia0 < 1000) && (distancia15 < 1000))
    {
      diferenca_distancia = distancia15 - distancia0;
    }
  }

  motor0.speed = 0;
  motor1.speed = 0;
  set_motors_speed(&motor0, &motor1);

  return distancia0;
}
