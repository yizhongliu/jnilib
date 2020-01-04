/**
 *  Self Test application for Invensense's encoder6050/encoder6500/encoder9150.
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
#include "encoder.h"
#define MAX_SYSFS_NAME_LEN     (100)
#define MAX_SYSFS_ATTRB        (sizeof(struct sysfs_attrbs) / sizeof(char*))
#define IIO_SYSFS_PATH      "/sys/devices/platform/encoder_demo1"

#define  LOG_TAG    "test1"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
struct sysfs_attrbs {
    char *left_step;
    char  *right_step;
    char *encoder_count;
    char *encoder_value;
} encoder;

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
        dptr = (char**)&encoder;
        do {
            *dptr++ = sptr;
            sptr += sizeof(char[MAX_SYSFS_NAME_LEN]);
        } while (++i < MAX_SYSFS_ATTRB);
    } else {
        //MPL_LOGE("inv_self_test: couldn't alloc mem for sysfs paths");
        return -1;
    }
    // Setright IIO sysfs path & build encoder's sysfs paths
    sprintf(sysfs_path, "%s", IIO_SYSFS_PATH);
    sprintf(encoder.left_step, "%s%s", sysfs_path, "/left_step");
    sprintf(encoder.right_step, "%s%s", sysfs_path, "/right_step");
    sprintf(encoder.encoder_count, "%s%s", sysfs_path, "/encoder_count");
    sprintf(encoder.encoder_value, "%s%s", sysfs_path, "/encoder_value");

#if 0
    // test print sysfs paths
    dptr = (char**)&encoder;
    for (i = 0; i < MAX_SYSFS_ATTRB; i++) {
        LOGE("inv_self_test: sysfs path: %s\n", *dptr++);
    }
#endif
    return 0;
}

/*******************************************************************************
 *                       M a i n
 ******************************************************************************/
int getEncoder1Data(int dir)
{
    int result;
    int encoder_right;
    int encoder_left;
    int encoder_value;
    int encoder_count;
    result = inv_init_sysfs_attributes();
    read_sysfs_int(encoder.encoder_count, &encoder_count);
    return encoder_count;
//    if(dir == 0){
//        read_sysfs_int(encoder.left_step, &encoder_left);
//        LOGD("encoder_left:%d", encoder_left);
//        read_sysfs_int(encoder.encoder_value, &encoder_value);
//                LOGD("encoder_value1:%d", encoder_value);
//                read_sysfs_int(encoder.encoder_count, &encoder_count);
//                LOGD("encoder_count1:%d", encoder_count);
//        return encoder_left;
//    }
//    if(dir == 1){
//        read_sysfs_int(encoder.right_step, &encoder_right);
//        LOGD("encoder_right:%d", encoder_right);
//        read_sysfs_int(encoder.encoder_value, &encoder_value);
//                LOGD("encoder_value1:%d", encoder_value);
//                read_sysfs_int(encoder.encoder_count, &encoder_count);
//                LOGD("encoder_count1:%d", encoder_count);
//        return encoder_right;
//    }
//    return result;
}

int setEncoder1Data(int dir)
{
    int result;
    result = inv_init_sysfs_attributes();
    write_sysfs_int(encoder.encoder_value, 0);
    write_sysfs_int(encoder.encoder_count, 0);
    if(dir == 0){
         write_sysfs_int(encoder.left_step, 0);
    }
   if(dir == 1){
        write_sysfs_int(encoder.right_step, 0);
   }

    return result;
}

int setEncoder1(int dir, int value)
{
    int result;
    result = inv_init_sysfs_attributes();
    write_sysfs_int(encoder.encoder_value, value);
    write_sysfs_int(encoder.encoder_count, value);
    if(dir == 0){
        write_sysfs_int(encoder.left_step, value);
    }
    if(dir == 1){
        write_sysfs_int(encoder.right_step, value);
    }

    return result;
}
