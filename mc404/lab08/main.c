#include "api_robot.h" /* Robot control API */

void delay();

/* main function */
void _start(void)
{
  unsigned int distances[16];

  set_speed_motors(60, 60);

  while(1)
  {
      /*Verifica se ha um obstaculo na frente*/
      distances[3] = read_sonar(3);
      distances[4] = read_sonar(4);

      /*Continua andando ate encontrar um obstaculo*/
      while((distances[3] > 1200) && (distances[4] > 1200))
      {
        distances[3] = read_sonar(3);
        distances[4] = read_sonar(4);
      }

      /*Para o robo quando um obstaculo for encontrado e realiza a medicao das distancias de todos os sonares*/
      set_speed_motors(0, 0);
      read_sonars(distances);

      /*Se o melhor caminho for o da direita, gira o robo para a direita*/
      if((distances[7] > distances[0]) || (distances[8] > distances[15]))
      {
          set_speed_motors(0, 5);
      }
      /*Caso contrario vira o robo para a esquerda*/
      else
      {
          set_speed_motors(5, 0);
      }

      /*Continua virando o robo ate que seja possivel seguir em frente*/
      while((distances[3] < 1200) || (distances[4] < 1200))
      {
        distances[3] = read_sonar(3);
        distances[4] = read_sonar(4);
      }
      set_speed_motors(60, 60);
  }
}

/* Spend some time doing nothing. */
void delay()
{
  int i;
  /* Not the best way to delay */
  for(i = 0; i < 10000; i++ );
}
