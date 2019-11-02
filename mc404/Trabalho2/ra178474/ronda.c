#include "bico.h"

void vira_robo();

void _start(void)
{
  unsigned int distancias[16];
  unsigned int time;
  unsigned int j = 1;

  motor_cfg_t motor0;
  motor_cfg_t motor1;


  motor0.id = 0;
  motor1.id = 1;

  motor0.speed = 32;
  motor1.speed = 32;
  set_motors_speed(&motor0, &motor1);

  add_alarm(vira_robo, 1);
  while(1)
  {
    motor0.speed = 32;
    motor1.speed = 32;
    set_motors_speed(&motor0, &motor1);

    while(j < 10000)
    {
      j++;
    }
  }
}

/*Vira o robo em aproximadamente 90 graus*/
void vira_robo()
{
  motor_cfg_t motor0;
  motor_cfg_t motor1;
  unsigned int time;
  unsigned int i;

  motor0.id = 0;
  motor1.id = 1;

  for(i = 0; i < 19; i++)
  {
    motor0.speed = 0;
    motor1.speed = 20;
    set_motors_speed(&motor0, &motor1);
  }

  /*Adiciona um novo alarme*/
  get_time(&time);
  time = time + 2;
  add_alarm(vira_robo, time);
}
