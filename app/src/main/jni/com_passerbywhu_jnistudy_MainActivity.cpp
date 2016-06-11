//
// Created by passe on 2016/6/11.
//
#include <jni.h>
#include <android/log.h>
#include "com_passerbywhu_jnistudy_MainActivity.h"

JNIEXPORT jstring JNICALL Java_com_passerbywhu_jnistudy_MainActivity_getText
  (JNIEnv * env, jobject object) {
    const char* str = "Hello JNI";
    return env->NewStringUTF(str);
}
