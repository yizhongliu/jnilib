#ifndef DLP343X_HHHH
#define DLP343X_HHHH

#include <sys/ioctl.h>
#define MOTOR_MAGIC 'x'
struct dlp343x{
    unsigned char data_len;
    unsigned char addr;
    unsigned char data[10];
};
int dlp_write_data(unsigned char dlp_addr, unsigned char *dlp_data, unsigned char dlp_count);
unsigned char *dlp_read_data(unsigned char dlp_addr,  unsigned char dlp_count);
int controlProjectorCloseOpen(int powerState);
#define SET_POWER_ON_OFF   		 _IOWR(MOTOR_MAGIC, 0xa, int)
#define SET_DLP_DATA			 _IOWR(MOTOR_MAGIC, 0x8, struct dlp343x)

int setKeyStone(int angle);


#endif