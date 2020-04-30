//
// Created by Administrator on 2020/4/24.
//
#include <jni.h>
#include <android/native_window_jni.h>
#include <android/native_window.h>
#include "utilbase.h"

void nativeStartServer(JNIEnv *env,jobject jobj){

}

void nativeStopServer(JNIEnv *env,jobject jobj){

}

void naviteGetFrame(JNIEnv *env,jobject jobj){

}

void nativeSetView(JNIEnv *env,jobject jobj){

}

void naviteTest(JNIEnv *env,jobject jobj)
{

}


jint registerNativeMethods(JNIEnv* env, const char *class_name, JNINativeMethod *methods, int num_methods) {
    int result = 0;
    jclass clazz = env->FindClass(class_name);
    if (LIKELY(clazz)) {
        int result = env->RegisterNatives(clazz, methods, num_methods);
        if (UNLIKELY(result < 0)) {
            LOGE("registerNativeMethods failed(class=%s)", class_name);
        }
    } else {
        LOGE("registerNativeMethods: class'%s' not found", class_name);
    }
    return result;
}

static JNINativeMethod methods[] = {
        {"nativeStartServer", "()J", (void *) nativeStartServer},
};

int register_vsairplay(JNIEnv *env) {
    LOGV("register :");
    if (registerNativeMethods(env,
                              "com/vsoon/airplay/AirPlayView",
                              methods, NUM_ARRAY_ELEMENTS(methods)) < 0) {
        return -1;
    }
    return 0;
}
