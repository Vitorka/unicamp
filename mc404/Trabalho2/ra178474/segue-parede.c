#include "bico.h"

unsigned int emparelha();
void segue_parede();
void afasta_parede(unsigned int distancias[], unsigned int distancia_referencia);
void aproxima_parede(unsigned int distancias[], unsigned int distancia_referencia);

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

  while(1)
  {
    while(flag2)
    {
      distancias[0] = read_sonar(0);
      distancias[15] = read_sonar(15);

      if((distancias[0] < distancia_referencia) || (distancias[15] < distancia_referencia))
      {
        afasta_parede(distancias, distancia_referencia);
        flag2 = 0;
      }
      else
      {
        aproxima_parede(distancias, distancia_referencia);
        flag2 = 0;
      }
    }

    motor0.speed = 32;
    motor1.speed = 32;
    set_motors_speed(&motor0, &motor1);
  }
}

unsigned int emparelha()
{

  unsigned int distancia0;
  unsigned int distancia15;

  motor_cfg_t motor0;
  motor_cfg_t motor1;

  int flag = 30;

  while(flag > 10)
  {
    distancia0 = read_sonar(0);
    distancia15 = read_sonar(15);

    if((distancia0 >= distancia15) && (distancia0 < 1000) && (distancia15 < 1000))
    {
      flag = distancia0 - distancia15;
    }
    else if((distancia0 <= distancia15) && (distancia0 < 1000) && (distancia15 < 1000))
    {
      flag = distancia15 - distancia0;
    }
  }

  motor0.speed = 0;
  motor1.speed = 0;
  set_motors_speed(&motor0, &motor1);

  return distancia0;
}

void afasta_parede(unsigned int distancias[], unsigned int distancia_referencia)
{
  motor_cfg_t motor0;
  motor_cfg_t motor1;
  unsigned int flag = 1;

  motor0.speed = 0;
  motor1.speed = 2;
  set_motors_speed(&motor0, &motor1);

  distancias[0] = read_sonar(0);
  distancias[15] = read_sonar(15);

  while(flag)
  {
    distancias[0] = read_sonar(0);
    distancias[15] = read_sonar(15);

    if((distancias[0] >= distancias[15]) && (distancias[0] > distancia_referencia) && (distancias[15] > distancia_referencia))
    {
      flag = distancias[0] - distancias[15];
    }
    else if((distancias[0] <= distancias[15]) && (distancias[0] > distancia_referencia) && (distancias[15] > distancia_referencia))
    {
      flag = distancias[15] - distancias[0];
    }
  }

  motor0.speed = 0;
  motor1.speed = 0;
  set_motors_speed(&motor0, &motor1);
}

void aproxima_parede(unsigned int distancias[], unsigned int distancia_referencia)
{
  motor_cfg_t motor0;
  motor_cfg_t motor1;

  unsigned int flag = 1;

  motor0.speed = 2;
  motor1.speed = 0;
  set_motors_speed(&motor0, &motor1);

  distancias[0] = read_sonar(0);
  distancias[15] = read_sonar(15);

  while(flag)
  {
    distancias[0] = read_sonar(0);
    distancias[15] = read_sonar(15);

    if((distancias[0] >= distancias[15]) && (distancias[0] < distancia_referencia) && (distancias[15] < distancia_referencia))
    {
      flag = distancias[0] - distancias[15];
    }
    else if((distancias[0] <= distancias[15]) && (distancias[0] < distancia_referencia) && (distancias[15] < distancia_referencia))
    {
      flag = distancias[15] - distancias[0];
    }

  }

  motor0.speed = 0;
  motor1.speed = 0;
  set_motors_speed(&motor0, &motor1);
}
