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

JNIEXPORT jstring JNICALL native_get_name
  (JNIEnv * env, jobject thiz) {
   return env->NewStringUTF("passerbywhu");
}

static JNINativeMethod gmethods[] = {
  {"getName", "()Ljava/lang/String;", (void*)native_get_name},
};

static int registerNativeMethods(JNIEnv* env, const char* className, JNINativeMethod* gMethods, int numMethods) {
    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

static int registerNatives(JNIEnv* env) {
    if (!registerNativeMethods(env, "com/passerbywhu/jnistudy/MainActivity", gmethods, sizeof(gmethods) / sizeof(gmethods[0]))) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

/*虚拟机执行System.loadLibrary("native")后，进入native.so后
 *会首先执行这个方法，所以我们在这里做注册的动作 */
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
   jint result = -1;
   JNIEnv* env = NULL;
   if (vm->GetEnv((void**) &env, JNI_VERSION_1_4)) {
      goto fail;
   }
   //最终调用env->RegisterNatives
   if (registerNatives(env) != JNI_TRUE) {
       goto fail;
   }
   result = JNI_VERSION_1_4;
   fail:
       return result;
}
