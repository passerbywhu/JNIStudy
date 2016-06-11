LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := native

LOCAL_SRC_FILES := com_passerbywhu_jnistudy_MainActivity.cpp

LOCAL_LDLIBS += -llog

include $(BUILD_SHARED_LIBRARY)