#pragma once
#include <jni.h>

void ShowKeyboardJNI(JNIEnv* env, jobject activity);

#include "imgui_mod.h"
#include "imgui.h"

void ShowKeyboardJNI(JNIEnv* env, jobject activity) {
    jclass activityClass = env->GetObjectClass(activity);
    jmethodID getSystemService = env->GetMethodID(activityClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    jstring inputMethodService = env->NewStringUTF("input_method");
    jobject inputMethodManager = env->CallObjectMethod(activity, getSystemService, inputMethodService);

    jclass immClass = env->GetObjectClass(inputMethodManager);
    jmethodID toggleSoftInput = env->GetMethodID(immClass, "toggleSoftInput", "(II)V");
    env->CallVoidMethod(inputMethodManager, toggleSoftInput, 0, 0);
}











