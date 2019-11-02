#ifndef TESTE_H
#define TESTE_H

void set_speed_motors(unsigned char spd_m0, unsigned char spd_m1);

void set_speed_motor(unsigned char id, unsigned char speed);

void get_time(unsigned int* t);

unsigned short read_sonar(unsigned char sonar_id);

#endif // API_ROBOT_H
