#include "bico.h"

void _start(void)
{
  unsigned int distancia3;
  unsigned int distancia4;

  motor_cfg_t motor0;
  motor_cfg_t motor1;

  motor0.speed = 36;
  motor1.speed = 36;
  motor0.id = 0;
  motor1.id = 1;

  set_motors_speed(&motor1, &motor0);


  while(1)
  {
    distancia3 = read_sonar(3);
    distancia4 = read_sonar(4);

    while((distancia3 > 1200) && (distancia4 > 1200))
    {
      distancia3 = read_sonar(3);
      distancia4 = read_sonar(4);
    }

    motor0.speed = 0;
    motor1.speed = 1;
    set_motors_speed(&motor0, &motor1);

    distancia3 = read_sonar(3);
    distancia4 = read_sonar(4);

    motor0.speed = 0;
    motor1.speed = 5;
    set_motors_speed(&motor0, &motor1);

    while((distancia3 < 1200) || (distancia4 < 1200))
    {
      distancia3 = read_sonar(3);
      distancia4 = read_sonar(4);
    }

    motor0.speed = 36;
    motor1.speed = 36;
    set_motors_speed(&motor0, &motor1);

  }

}
