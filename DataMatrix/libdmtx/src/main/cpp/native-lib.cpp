#include <jni.h>
#include <string>
#include "libdmtx/dmtx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>
#include<android/bitmap.h>

const char *LOGTAG = "dmtx";

extern "C"
JNIEXPORT jstring JNICALL
Java_org_tcshare_libdmtx_DmtxDecoder_getDMListFromBitmap(JNIEnv *env, jobject instance,
                                                                jobject bitmap, jlong timout) {

    unsigned char  *pxl;
    DmtxImage      *img;
    DmtxDecode     *dec;
    DmtxRegion     *reg;
    DmtxMessage    *msg;


    int ret;
    AndroidBitmapInfo info;

    if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
        __android_log_print(ANDROID_LOG_VERBOSE, LOGTAG,"AndroidBitmap_getInfo() failed ! error=%d", ret);
        return NULL;
    }
    if ((ret = AndroidBitmap_lockPixels(env, bitmap,(void**)&pxl)) < 0) {
        __android_log_print(ANDROID_LOG_VERBOSE, LOGTAG,"AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return NULL;
    }

      // 开始解析
    img = dmtxImageCreate(pxl, info.width, info.height, DmtxPack32bppXRGB);
    if(img == NULL){
        AndroidBitmap_unlockPixels(env, bitmap);
        return NULL;
    }

    dec = dmtxDecodeCreate(img, 1);
    if(dec == NULL){
        AndroidBitmap_unlockPixels(env, bitmap);
        return NULL;
    }

    char *result = new char(0);
    DmtxTime tout = dmtxTimeAdd(dmtxTimeNow(), timout);
    reg = dmtxRegionFindNext(dec, &tout);
    if(reg != NULL) {
        msg = dmtxDecodeMatrixRegion(dec, reg, DmtxUndefined);
        if(msg != NULL) {
           // fputs("output: \"", stdout);
            result = (char *)msg->output;

           // fwrite(msg->output, sizeof(unsigned char), msg->outputIdx, stdout);
           // fputs("\"\n", stdout);
            dmtxMessageDestroy(&msg);
        }
        dmtxRegionDestroy(&reg);
    }

    dmtxDecodeDestroy(&dec);
    dmtxImageDestroy(&img);
    AndroidBitmap_unlockPixels(env, bitmap);
    //free(pxl);

    return env->NewStringUTF(result);

}

