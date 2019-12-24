/**
 *  Self Test application for Invensense's MPU6050/MPU6500/MPU9150.
 */
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <features.h>
#include <dirent.h>
#include <string.h>
#include <poll.h>
#include <stddef.h>
#include <linux/input.h>
#include <time.h>
#include <linux/time.h>
#include <android/log.h>
#include "./include/encoder_test.h"
#define MAX_SYSFS_NAME_LEN     (100)
#define MAX_SYSFS_ATTRB        (sizeof(struct sysfs_attrbs) / sizeof(char*))
#define IIO_SYSFS_PATH      "/sys/devices/platform/encoder_demo0"

#define LOG_TAG    "encoder0"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
struct sysfs_attrbs {
    char *down_step;
    char  *up_step;
} mpu;

static char *sysfs_names_ptr;
/** read a sysfs entry that represents an integer */
static int read_sysfs_int(char *filename, int *var)
{
    int res=0;
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp!=NULL) {
        fscanf(fp, "%d\n", var);
    fclose(fp);
    } else {
        //MPL_LOGE("inv_self_test: ERR open file to read");
		LOGE("inv_self_test: ERR open file to read\n");
		LOGE("%s\n", filename);
        res= -1;
    }
    return res;
}

/** write a sysfs entry that represents an integer */
static int write_sysfs_int(char *filename, int data)
{
    int res=0;
    FILE  *fp;
    fp = fopen(filename, "w");
    if (fp != NULL) {
        fprintf(fp, "%d\n", data);
    fclose(fp);
    } else {
        //MPL_LOGE("inv_self_test: ERR open file to write");
		LOGE("inv_self_test: ERR open file to write\n");
		LOGE("%s\n", filename);
        res= -1;
    }
    return res;
}

static int inv_init_sysfs_attributes(void)
{
    unsigned char i = 0;
    char sysfs_path[MAX_SYSFS_NAME_LEN];
    char *sptr;
    char **dptr;
    sysfs_names_ptr =
            (char*)malloc(sizeof(char[MAX_SYSFS_ATTRB][MAX_SYSFS_NAME_LEN]));
    sptr = sysfs_names_ptr;
    if (sptr != NULL) {
        dptr = (char**)&mpu;
        do {
            *dptr++ = sptr;
            sptr += sizeof(char[MAX_SYSFS_NAME_LEN]);
        } while (++i < MAX_SYSFS_ATTRB);
    } else {
        //MPL_LOGE("inv_self_test: couldn't alloc mem for sysfs paths");
        return -1;
    }
    // Setup IIO sysfs path & build MPU's sysfs paths
    sprintf(sysfs_path, "%s", IIO_SYSFS_PATH);
    sprintf(mpu.down_step, "%s%s", sysfs_path, "/down_step");
    sprintf(mpu.up_step, "%s%s", sysfs_path, "/up_step");

#if 0
    // test print sysfs paths
    dptr = (char**)&mpu;
    for (i = 0; i < MAX_SYSFS_ATTRB; i++) {
        LOGE("inv_self_test: sysfs path: %s\n", *dptr++);
    }
#endif
    return 0;
}

/*******************************************************************************
 *                       M a i n
 ******************************************************************************/
int getEncoder0Data(int dir)
{
    int result;
    int encoder_up;
    int encoder_down;
    result = inv_init_sysfs_attributes();
    if(dir == 0){
        read_sysfs_int(mpu.down_step, &encoder_down);
        LOGD("encoder_down:%d", encoder_down);
        return encoder_down;
    }
    if(dir == 1){
        read_sysfs_int(mpu.up_step, &encoder_up);
        LOGD("encoder_up:%d", encoder_up);
        return encoder_up;
    }
    return result;
}

int setEncoder0Data(int dir)
{
    int result;
    result = inv_init_sysfs_attributes();
    if(dir == 0){
        write_sysfs_int(mpu.down_step, 0);
    }
    if(dir == 1){
        write_sysfs_int(mpu.up_step, 0);
    }
    return result;
}

