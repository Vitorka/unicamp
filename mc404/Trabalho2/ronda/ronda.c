#include "bico.h"

void vira_robo();
void vira_robo2();

  int i;

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

  //register_proximity_callback(3, 1200, vira_robo2);
  //register_proximity_callback(4, 1200, vira_robo2);

  add_alarm(vira_robo, 1);
  while(1)
  {

    //add_alarm(vira_robo, 1);
    motor0.speed = 32;
    motor1.speed = 32;
    set_motors_speed(&motor0, &motor1);

    while(j < 10000)
    {
      j++;
    }
  }
}

void vira_robo()
{
  motor_cfg_t motor0;
  motor_cfg_t motor1;
  unsigned int time;

  motor0.id = 0;
  motor1.id = 1;

  for(i = 0; i < 19; i++)
  {
    motor0.speed = 0;
    motor1.speed = 20;
    set_motors_speed(&motor0, &motor1);
  }

  get_time(&time);
  time = time;
  add_alarm(vira_robo, time);
}

void vira_robo2()
{
  motor_cfg_t motor0;
  motor_cfg_t motor1;
  int i;
  unsigned int distancia3, distancia4;

  motor0.speed = 0;
  motor1.speed = 20;
  set_motors_speed(&motor0, &motor1);

  while((distancia3 < 1200) || (distancia4 < 1200))
  {
    distancia3 = read_sonar(3);
    distancia4 = read_sonar(4);
  }

}
