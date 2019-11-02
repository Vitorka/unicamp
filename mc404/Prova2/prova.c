short key;
short do_something(short* array, int v1, int v2, int v3, int v4, int v5);

void _start()
{

}

short key;
short do_something(short* array, int v1, int v2, int v3, int v4, int v5) {
unsigned int i=0;
short tmp;
do {
tmp = array[i];
i = i+1;
} while (tmp != key);
check(&tmp, v2);
return tmp+v5;
}
