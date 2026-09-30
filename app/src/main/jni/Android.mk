LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

# Here is the name of your lib.
# When you change the lib name, change also on System.loadLibrary("") under OnCreate method on StaticActivity.java
# Both must have same name
LOCAL_MODULE    := MP

# -std=c++17 is required to support AIDE app with NDK
LOCAL_CFLAGS := -w -s -Wno-error=format-security -fvisibility=hidden -fpermissive -fexceptions
LOCAL_CPPFLAGS := -w -s -Wno-error=format-security -fvisibility=hidden -Werror -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fpermissive -Wall -fexceptions
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all,-llog
LOCAL_LDLIBS := -lz -landroid -lEGL -lGLESv2
LOCAL_LDFLAGS += -Wl,-z,max-page-size=16384 -Wl,-z,common-page-size=16384

LOCAL_LDFLAGS += $(LOCAL_PATH)/libraries/$(TARGET_ARCH_ABI)/libdobby.a

LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Includes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/ImGui
LOCAL_C_INCLUDES += $(LOCAL_PATH)/ImGui/backends

# Here you add the cpp file to compile
LOCAL_SRC_FILES := MPCheats.cpp \
        ImGui/imgui.cpp \
    ImGui/imgui_draw.cpp \
    ImGui/imgui_widgets.cpp \
    ImGui/imgui_tables.cpp \
    ImGui/backends/imgui_impl_opengl3.cpp \
    ImGui/backends/imgui_impl_android.cpp \
    MPHook/Substrate/SubstrateDebug.cpp \
        MPHook/Substrate/SubstrateHook.cpp \
        MPHook/Substrate/SubstratePosixMemory.cpp \
MPHook/Substrate/hde64.c \
    MPHook/KittyMemory/KittyMemory.cpp \
    MPHook/KittyMemory/MemoryPatch.cpp \
    MPHook/KittyMemory/MemoryBackup.cpp \
    MPHook/KittyMemory/KittyUtils.cpp \
    MPHook/And64InlineHook/And64InlineHook.cpp

include $(BUILD_SHARED_LIBRARY)
