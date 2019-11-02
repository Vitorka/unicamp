#ifndef TESTE_H
#define TESTE_H

void set_speed_motors(unsigned char spd_m0, unsigned char spd_m1);

unsigned short read_sonar(unsigned char sonar_id);

void set_time(unsigned int t);
void get_time(unsigned int* t);
void add_alarm(void (*f)(), unsigned int time);
void register_proximity_callback(unsigned char sensor_id, unsigned short dist_threshold, void (*f)());

#endif // API_ROBOT_H
