#include "teste.h"

void _start(void)
{
  unsigned int distancia3;
  unsigned int distancia4;

  set_speed_motors(36, 36);

  while(1)
  {
    distancia3 = read_sonar(3);
    distancia4 = read_sonar(4);

    while((distancia3 > 1200) && (distancia4 > 1200))
    {
      distancia3 = read_sonar(3);
      distancia4 = read_sonar(4);
    }

    set_speed_motors(0, 0);

    distancia3 = read_sonar(3);
    distancia4 = read_sonar(4);

    set_speed_motors(0, 5);

    while((distancia3 < 1200) || (distancia4 < 1200))
    {
      distancia3 = read_sonar(3);
      distancia4 = read_sonar(4);
    }

    set_speed_motors(36, 36);

  }
}
