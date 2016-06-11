//
// Created by passe on 2016/6/11.
//
#include <jni.h>
#include <android/log.h>
#include <string.h>
#include "com_passerbywhu_jnistudy_MainActivity.h"

JNIEXPORT jstring JNICALL Java_com_passerbywhu_jnistudy_MainActivity_getText
  (JNIEnv * env, jobject object) {
    const char* str = "Hello JNI";
    return env->NewStringUTF(str);
}

JNIEXPORT jstring JNICALL Java_com_passerbywhu_jnistudy_MainActivity_show
  (JNIEnv * env, jobject thiz) {
   /* 通过JNI函数GetObjectClass得到传入对象的类信息，这里传入的对象
   *就是调用Native方法的jmethodID
   */
   jclass jcls = env->GetObjectClass(thiz);
   //根据类信息得到callback方法的jmethodID
   jmethodID jmId = env->GetMethodID(jcls, "callback", "()V");
   //调用callback方法
   env->CallVoidMethod(thiz, jmId);
   /*因为在Java层的callback中抛出了未捕获的异常，所以上面的JNI函数调用必然出现异常
   *，这里必须检查并处理异常，否则异常将抛给Java层的callback方法，此时，进程将挂掉
   */
   if (env->ExceptionCheck()) {
       env->ExceptionDescribe();
       env->ExceptionClear(); //消除异常
   }
   return env->NewStringUTF("Show message from JNI !");
}
