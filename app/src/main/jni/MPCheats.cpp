namespace Settings {static int Tab = 1;}
#include "MPHook/includes.h"
#include "MPHook/KittyMemory/MemoryPatch.h"
#include "MPHook/And64InlineHook/And64InlineHook.hpp"
#include "MPHook/Esp/Vector3.h"
#include "MPHook/Includes/msg.h"
#include "MPHook/Includes/classes.h"
#include "MPHook/KittyMemory/obfuscate.h"
#include "MPHook/ESP/Include.h"
#include "MPHook/Includes/monostring.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_android.h"
#include "ImGui/backends/imgui_impl_opengl3.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <sys/system_properties.h>
#include "ImGui/FONTS/DEFAULT.h"
#include <MPHook/Includes/Utils.h>
#include <MPHook/Includes/Dobby/dobby.h>
bool g_Initialized = false;
ImGuiWindow* g_window = NULL;
#include <MPHook/Substrate/SubstrateHook.h>
#include <MPHook/Substrate/CydiaSubstrate.h>
const char *libName = "libUE4.so";
const char *libName1 = "libgnustl_shared.so";
//#define targetLibName OBFUSCATE("libUE4.so")
//#define targetLibName OBFUSCATE("libgnustl_shared.so")
#include <cmath>
#include <cstdlib>
#include <dlfcn.h>
#include <android/log.h>
#include <cmath>
#include <iostream>
#include <dlfcn.h>
#include <string>
#include <EGL/egl.h>
#include <MPHook/MPCheats/GLES3/gl3.h>
#include <MPHook/MPCheats/GLES3/gl3ext.h>
#include <MPHook/MPCheats/GLES3/gl3platform.h>
std::unordered_set<void*> espAll;
//IDA 6.8 Version Pro Define (Bypass Thread)\\
typedef uint32_t _DWORD;
typedef uint64_t _QWORD;
#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long
#define _BYTE  uint8_t
#define _WORD  uint16_t
#define _DWORD uint32_t
#define _QWORD uint64_t
#define CS
#define PATCH_LIB
#define OBFUSCATE
#define HOOK_LIB_NO_ORIG
#define HOOK_LIB
#define HOOK
#define xhook_register
#define _cxa_get_globals_fast
#define Framerate
using namespace std;
//тоже важная хрень
extern "C" {
    
    JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_init(JNIEnv* env, jclass cls);
    JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_resize(JNIEnv* env, jobject obj, jint width, jint height);
    JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_step(JNIEnv* env, jobject obj);
    JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_imgui_Shutdown(JNIEnv* env, jobject obj);
    JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_MotionEventClick(JNIEnv* env, jobject obj,jboolean down,jfloat PosX,jfloat PosY);
    JNIEXPORT jstring JNICALL Java_com_mycompany_application_GLES3JNIView_getWindowRect(JNIEnv *env, jobject thiz);
    JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_real(JNIEnv* env, jobject obj, jint width, jint height);
    
};
// 4.2 Sfg2 Offsets \\ // for Sdk Templates but Sdk is not available for now \\
#define GetPlayerName_Offset 0x028BE9B4
#define GUObjectArray_Offset 0x05D0A198
#define GEngine_Offset 0x05BD967C
#define UEngine_Offset 0x04334BD4 //FindFirstLocalPlayerFromController
#define UEngine1_Offset 0x043306d4 //GetLocalPlayerFromController_UWorld
#define UlocalPlayer_Offset 0x044CAD84
#define GNativeAndroidApp_Offset 0x05BCF44C
#define PostRender_Offset 0x03E93010
#define eglSwapBuffers 0x05D29768
//#define onInputEvent 0x025B5CCC
#define Actors_Offset 0x02733E5C
//Macros for Hooking
#define MTR_NR(RET,NAME,ARGS) \
RET(*o##NAME)   \
ARGS;   \
RET h##NAME ARGS\ {   \
asm volatile( \
"mov r0,#0\n"  \
); \
}
#define MPCHEATS(RET,NAME,ARGS) \
  RET(*o##NAME) ARGS; \
  RET h##NAME ARGS
#define YAHDIKALLAH(RET,NAME,ARGS) \
  RET(*o##NAME) ARGS; \
  RET h##NAME ARGS
//------------HOOKS
typedef long long int64; 
typedef short int16;
DWORD libUE4Base = 0;
DWORD libEGLBase = 0;
DWORD libUE4Alloc = 0;
DWORD libEGLAlloc = 0;
unsigned int libUE4Size  = 0;
DWORD NewBase = 0;
#define HOOK
void * memcpy_chk(void *dest, const void *src, size_t len, size_t dest_len);
#define ARM64_SYSREG_S3_3_C13_C0_2 "S3_3_C13_C0_2"
#define _ReadStatusReg(reg) ({ uint64_t val; __asm__ volatile("mrs %0, " reg : "=r" (val)); val; })
#define READ_STATUS_REG() ({ uint64_t val; __asm__ volatile("mrs %0, S3_3_C13_C0_2" : "=r" (val)); val; })
char *Offset;
char aTERSIGStart[0x140] = "TERSIGStart test data...";  
struct Afghanistan {
MemoryPatch h;} hexPatches;
bool show_window;
bool initImGui = false;
int screenWidth = -1, glWidth, screenHeight = -1, glHeight;
bool isEnableESP,EspLine,EspBox,EspPlayerName,EspSkeleton,EspHealth,EspDistance,EspRadar,Aimbot;
void (*esp_update)(void*,float);
void update_Esp(void* thiz,float dly){
    if(thiz != nullptr){
       espAll.insert(thiz);
    }
    return esp_update(thiz,dly);
}
struct sRegion {
    uintptr_t start, end;
};

std::vector<sRegion> trapRegions; //Enable Delay\\

std::string utf16le_to_utf8(const std::u16string &u16str) {
    if (u16str.empty()) { return std::string(); }
    const char16_t *p = u16str.data();
    std::u16string::size_type len = u16str.length();
    if (p[0] == 0xFEFF) {
        p += 1;
        len -= 1;
    }

    std::string u8str;
    u8str.reserve(len * 3);

    char16_t u16char;
    for (std::u16string::size_type i = 0; i < len; ++i) {

        u16char = p[i];

        if (u16char < 0x0080) {
            u8str.push_back((char) (u16char & 0x00FF));
            continue;
        }
        if (u16char >= 0x0080 && u16char <= 0x07FF) {
            u8str.push_back((char) (((u16char >> 6) & 0x1F) | 0xC0));
            u8str.push_back((char) ((u16char & 0x3F) | 0x80));
            continue;
        }
        if (u16char >= 0xD800 && u16char <= 0xDBFF) {
            uint32_t highSur = u16char;
            uint32_t lowSur = p[++i];
            uint32_t codePoint = highSur - 0xD800;
            codePoint <<= 10;
            codePoint |= lowSur - 0xDC00;
            codePoint += 0x10000;
            u8str.push_back((char) ((codePoint >> 18) | 0xF0));
            u8str.push_back((char) (((codePoint >> 12) & 0x3F) | 0x80));
            u8str.push_back((char) (((codePoint >> 06) & 0x3F) | 0x80));
            u8str.push_back((char) ((codePoint & 0x3F) | 0x80));
            continue;
        }
        {
            u8str.push_back((char) (((u16char >> 12) & 0x0F) | 0xE0));
            u8str.push_back((char) (((u16char >> 6) & 0x3F) | 0x80));
            u8str.push_back((char) ((u16char & 0x3F) | 0x80));
            continue;
        }
    }

    return u8str;
}
// ==============================乇賳诏 賳賯胤賴 賴丕蹖 賲鬲乇蹖讴=========================================== // 
void *(*g_getWorld)(void*) = nullptr;
void *(*g_getFirstAplayerController)(void*) = nullptr;
bool (*g_ProjectWorldToScreen)(void*,Vector3,Vector2&,bool)=nullptr;
Vector3 (*g_getbonelocation)(void*,void*);
void*(*AController_K2_APawn)(void*);
void OnDrawESP(ImDrawList* draw, int width, int height) {
    // Basic safety
    if (!isEnableESP) return;

    // Helper structs
    struct _Vec2 { float X, Y; };
    struct _Vec3 { float X, Y, Z; };

    auto ToImVec2 = [&](const Vector2 &v)->ImVec2{ return ImVec2(v.X, v.Y); };

    // Helper math
    auto GetDistance = [](const Vector3 &a, const Vector3 &b)->float{
        float dx = a.X - b.X; float dy = a.Y - b.Y; float dz = a.Z - b.Z;
        return sqrtf(dx*dx + dy*dy + dz*dz);
    };

    auto GetPlayerHealth = [&](void* ent)->float{
        return 100.0f;
    };
    auto GetPlayerName = [&](void* ent)->const char*{
       //replace with real name retrieval
        return "Player";
    };
    auto GetPlayerOrigin = [&](void* ent, void* localPawn)->Vector3{
        return g_getbonelocation(ent, localPawn);
    };
    auto GetBoneHead = [&](void* ent, void* localPawn)->Vector3{
        Vector3 o = GetPlayerOrigin(ent, localPawn);
        o.Z += 70.0f;
        return o;
    };
    auto GetBoneFeet = [&](void* ent, void* localPawn)->Vector3{
        Vector3 o = GetPlayerOrigin(ent, localPawn);
        o.Z -= 20.0f;
        return o;
    };

    // find local world/controller/pawn once
    void* localWorld = nullptr;
    void* localController = nullptr;
    void* localPawn = nullptr;
    for (auto probe : espAll) {
        if(!probe) continue;
void* gw = g_getWorld(probe);
        if(!gw) continue;
        void* ctrl = g_getFirstAplayerController(gw);
        if(!ctrl) continue;
        void* pawn = (void*)AController_K2_APawn(ctrl);
        if(!pawn) continue;
        localWorld = gw; localController = ctrl; localPawn = pawn;
        break;
    }
    if(!localController || !localPawn) return; // cannot continue

    ImVec2 center(width*0.5f, height*0.5f);

    const float radarSize = 120.0f;
    const ImVec2 radarOrigin(80.0f, 80.0f);

    if (EspRadar) {
        draw->AddCircleFilled(radarOrigin, radarSize*0.5f, ImGui::GetColorU32(ImVec4(0,0,0,0.25f)));
        draw->AddCircle(radarOrigin, radarSize*0.5f, ImGui::GetColorU32(ImVec4(1,1,1,0.12f)));
    }
    // Aimbot tracking
    bool haveAimbot = false;
    void* bestTarget = nullptr;
    ImVec2 bestTargetScreen(0,0);
float bestDist = FLT_MAX;
    const float aimbotFOV = 150.0f;
    for (auto thiz : espAll) {
        if(!thiz) continue;

        void* gw = g_getWorld(thiz);
        if(!gw) continue;
        void* controller = g_getFirstAplayerController(gw);
        if(!controller) continue;
        void* pawn = (void*)AController_K2_APawn(controller);
        if(!pawn) continue;
        // world positions
        Vector3 head3 = GetBoneHead(thiz, pawn);
        Vector3 feet3 = GetBoneFeet(thiz, pawn);
        Vector2 head2, feet2;
        if(!g_ProjectWorldToScreen(controller, head3, head2, true)) continue;
        if(!g_ProjectWorldToScreen(controller, feet3, feet2, true)) continue;

        ImVec2 headP(head2.X, head2.Y);
        ImVec2 feetP(feet2.X, feet2.Y);

        ImVec4 color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
ImVec4 tColor = ImVec4(255,0,0,255);
        // Line ESP
        if (EspLine) {
            //draw->AddLine(center, feetP, ImGui::GetColorU32(color), 1.0f);
            DrawAddLine::DrawLine(ImVec2(width/2,0),ImVec2(head2.X,head2.Y),tColor,1);
        }

        // Box ESP
        if (EspBox) {
            float h = fabsf(headP.y - feetP.y);
            float w = h * 0.45f;
            ImVec2 topLeft(feetP.x - w*0.5f, headP.y);
            ImVec2 bottomRight(feetP.x + w*0.5f, feetP.y);
            draw->AddRect(topLeft, bottomRight, ImGui::GetColorU32(color), 0.0f, 0, 1.2f);
        }

        // Player name
        if (EspPlayerName) {
            const char* name = GetPlayerName(thiz);
            if (name && name[0]) {
                // compute distance (if localPawn/pawn available in scope)
                Vector3 localPos = GetPlayerOrigin(localPawn, localPawn);
                Vector3 tgtPos = GetPlayerOrigin(thiz, pawn);
                float dist = GetDistance(localPos, tgtPos);
                // scale and alpha by distance
                float scale = 1.0f;
                if (dist > 0.0f) scale = fmaxf(0.6f, fminf(1.4f, 1.1f - (dist / 800.0f)));
                float alphaF = fmaxf(0.22f, fminf(1.0f, 1.0f - (dist / 1500.0f)));
                int alpha = (int)roundf(alphaF * 255.0f);

                ImFont* font = ImGui::GetFont();
                float fontSize = ImGui::GetFontSize() * scale;
                // measure text with font at size
                ImVec2 txtSize = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, name);

                // truncate long names with ellipsis
                const float maxWidth = 220.0f;
                std::string drawName = name;
                if (txtSize.x > maxWidth) {
                    const char* ell = "...";
                    while (!drawName.empty()) {
                        drawName.pop_back();
                        ImVec2 attempt = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, drawName.c_str());
                        if (attempt.x + 20.0f <= maxWidth) { drawName += ell; break; }
                    }
                    txtSize = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, drawName.c_str());
                }

                ImVec2 textPos((headP.x + feetP.x)*0.5f, headP.y - 12.0f * scale);
                ImVec2 pos(textPos.x - txtSize.x*0.5f, textPos.y);

                // clamp to screen
                ImVec2 ioSize = ImGui::GetIO().DisplaySize;
                if (pos.x < 1.0f) pos.x = 1.0f;
                if (pos.x + txtSize.x > ioSize.x - 1.0f) pos.x = ioSize.x - txtSize.x - 1.0f;
                if (pos.y < 1.0f) pos.y = 1.0f;
                if (pos.y > ioSize.y - txtSize.y - 1.0f) pos.y = ioSize.y - txtSize.y - 1.0f;

                ImU32 textColor = ImGui::GetColorU32(ImVec4(1,1,1,1));
                ImU32 outlineColor = IM_COL32(0,0,0,(int)(alpha*0.9f));

                float off = 1.0f * scale;
                // outline
                draw->AddText(font, fontSize, ImVec2(pos.x - off, pos.y - off), outlineColor, drawName.c_str());
                draw->AddText(font, fontSize, ImVec2(pos.x + off, pos.y - off), outlineColor, drawName.c_str());
                draw->AddText(font, fontSize, ImVec2(pos.x - off, pos.y + off), outlineColor, drawName.c_str());
                draw->AddText(font, fontSize, ImVec2(pos.x + off, pos.y + off), outlineColor, drawName.c_str());
                // main
                draw->AddText(font, fontSize, pos, IM_COL32(255,255,255,alpha), drawName.c_str());
            }
        }

        // Heaith Esp
        if (EspHealth) {
            float hp = GetPlayerHealth(thiz);
            if (hp < 0) hp = 0; if (hp > 100) hp = 100;
            float h = fabsf(headP.y - feetP.y);
            float barW = 6.0f;
            ImVec2 tl(feetP.x - (h*0.45f)*0.5f - 10.0f, headP.y);
            ImVec2 br(tl.x + barW, feetP.y);
            draw->AddRectFilled(ImVec2(tl.x, tl.y), ImVec2(br.x, br.y), ImGui::GetColorU32(ImVec4(0,0,0,0.6f)));
            float pct = hp / 100.0f;
            float filled = (br.y - tl.y) * pct;
            draw->AddRectFilled(ImVec2(tl.x, br.y - filled), ImVec2(br.x, br.y), ImGui::GetColorU32(ImVec4(0,1,0,1)));
        }

        // Distance
        if (EspDistance) {
            Vector3 localPos = GetPlayerOrigin(localPawn, localPawn);
            Vector3 tgtPos = GetPlayerOrigin(thiz, pawn);
            float dist = GetDistance(localPos, tgtPos);
            char buf[64];
            if (dist >= 1000.0f) snprintf(buf, sizeof(buf), "%.1fk", dist/1000.0f);
            else snprintf(buf, sizeof(buf), "%.0fm", dist);
            draw->AddText(ImVec2(feetP.x, feetP.y + 6.0f), ImGui::GetColorU32(ImVec4(1,1,1,1)), buf);
        }

        // Skeleton (Approximate)
        if (EspSkeleton) {
            Vector3 origin = GetPlayerOrigin(thiz, pawn);
            Vector3 chest = origin; chest.Z += 30.0f;
            Vector3 pelvis = origin; pelvis.Z -= 10.0f;
            Vector3 lHand = chest; lHand.X -= 18.0f;
            Vector3 rHand = chest; rHand.X += 18.0f;
            Vector3 lFoot = pelvis; lFoot.X -= 10.0f; lFoot.Z -= 40.0f;
            Vector3 rFoot = pelvis; rFoot.X += 10.0f; rFoot.Z -= 40.0f;

            Vector2 pHead, pChest, pPelvis, pLHand, pRHand, pLFoot, pRFoot;
            if (g_ProjectWorldToScreen(controller, head3, pHead, true) &&
                g_ProjectWorldToScreen(controller, chest, pChest, true) &&
                g_ProjectWorldToScreen(controller, pelvis, pPelvis, true) &&
                g_ProjectWorldToScreen(controller, lHand, pLHand, true) &&
                g_ProjectWorldToScreen(controller, rHand, pRHand, true) &&
                g_ProjectWorldToScreen(controller, lFoot, pLFoot, true) &&
                g_ProjectWorldToScreen(controller, rFoot, pRFoot, true)) {
                draw->AddLine(ImVec2(pHead.X, pHead.Y), ImVec2(pChest.X, pChest.Y), ImGui::GetColorU32(color), 1.0f);
                draw->AddLine(ImVec2(pChest.X, pChest.Y), ImVec2(pPelvis.X, pPelvis.Y), ImGui::GetColorU32(color), 1.0f);
                draw->AddLine(ImVec2(pChest.X, pChest.Y), ImVec2(pLHand.X, pLHand.Y), ImGui::GetColorU32(color), 1.0f);
                draw->AddLine(ImVec2(pChest.X, pChest.Y), ImVec2(pRHand.X, pRHand.Y), ImGui::GetColorU32(color), 1.0f);
                draw->AddLine(ImVec2(pPelvis.X, pPelvis.Y), ImVec2(pLFoot.X, pLFoot.Y), ImGui::GetColorU32(color), 1.0f);
                draw->AddLine(ImVec2(pPelvis.X, pPelvis.Y), ImVec2(pRFoot.X, pRFoot.Y), ImGui::GetColorU32(color), 1.0f);
            }
        }

        // Radar dots
        if (EspRadar) {
            Vector3 localO = GetPlayerOrigin(localPawn, localPawn);
            Vector3 tgtO = GetPlayerOrigin(thiz, pawn);
            float dx = tgtO.X - localO.X;
            float dy = tgtO.Y - localO.Y;
            float maxRange = 2000.0f;
            float rx = (dx / maxRange) * (radarSize * 0.45f);
            float ry = (dy / maxRange) * (radarSize * 0.45f);
            ImVec2 dot = ImVec2(radarOrigin.x + rx, radarOrigin.y + ry);
            draw->AddCircleFilled(dot, 3.0f, ImGui::GetColorU32(color));
        }
        
        if (Aimbot) {
            // check on screen
            if (headP.x >= 0 && headP.y >= 0 && headP.x <= width && headP.y <= height) {
                float dx = headP.x - center.x; float dy = headP.y - center.y;
                float pd = sqrtf(dx*dx + dy*dy);
                if (pd < bestDist && pd <= aimbotFOV) {
                    bestDist = pd;
                    bestTarget = thiz;
                    bestTargetScreen = headP;
                    haveAimbot = true;
                }
            }
        }
    } // end loop

    // Visualize aimbot target and hint for implementer
    if (Aimbot && haveAimbot && bestTarget) {
        draw->AddCircle(ImVec2(bestTargetScreen.x, bestTargetScreen.y), 10.0f, ImGui::GetColorU32(ImVec4(1,1,0,1)), 16, 2.0f);
    }
}
typedef struct _monoString {
    void *klass;
    void *monitor;
    int length;
    char chars[1];
    int getLength() {
        return length;
    }
    const char *toChars(){
        u16string ss((char16_t *) getChars(), 0, getLength());
        string str = utf16le_to_utf8(ss);
        return str.c_str();
    }
    char *getChars() {
        return chars;
    }
    std::string get_string() {

      return std::string(toChars());
}
} monoString;

monoString*(*il2cpp_string_new)(const char* str);


monoString *CreateMonoString(const char *str) {
monoString *(*String_CreateString)(void *instance, const char *str) = (monoString *(*)(void *, const char *))getAbsoluteAddress("libUE4.so",0x1179674); //private unsafe string CreateString(sbyte* value)

    return String_CreateString(NULL, str);
}
//================================== Define constants
#define pkgName "com.ForgeGames.SpecialForcesGroup2"
void* sex = dlopen("libMP.so",RTLD_LAZY);
#include "MPHook/oxorany.cpp"
void mystyle() {
}
void SetCustomImGuiStyle()
{
    ImGuiStyle *style = &ImGui::GetStyle();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = NULL;
    //InitTexture();
        style->WindowTitleAlign = ImVec2(0.5, 0.5);
        style->ButtonTextAlign = ImVec2(0.5,0.5);
        //اطار الصوره تحديد
        style->WindowRounding = 8.0f;
        style->FrameRounding = 7.0f;
        style->ScrollbarRounding = 9;
        style->WindowBorderSize = 0.5;//2    
        style->FrameBorderSize = 2.5;// обводки кнопок
//اطار الصوره تحديد
        style->WindowTitleAlign = ImVec2(0.5, 0.5);
        style->ButtonTextAlign = ImVec2(0.5,0.5);
        style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
        style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
        style->Colors[ImGuiCol_WindowBg] = ImColor(0, 0, 0, 210);
        style->Colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        style->Colors[ImGuiCol_Border] = ImColor(0, 255, 0); // حدود الخط باللون الأخضر الفاتح
        style->Colors[ImGuiCol_BorderShadow] = ImColor(0, 255, 0); // ظلال الحدود باللون الأخضر الفاتح
        style->Colors[ImGuiCol_FrameBg] = ImColor(0, 0, 0, 235);
        style->Colors[ImGuiCol_FrameBgHovered] = ImColor(0, 0, 0, 235);
        style->Colors[ImGuiCol_FrameBgActive] = ImColor(0, 0, 0, 235);
        style->Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.70f);
        style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0, 155);
        style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.70f);
        style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.70f);
        style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
        style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
        style->Colors[ImGuiCol_CheckMark] = ImColor(255, 0, 0, 255);
        style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
        style->Colors[ImGuiCol_Separator]             = ImColor(255, 255, 255, 255);
        style->Colors[ImGuiCol_SeparatorActive]       = ImColor(255, 255, 255, 255);
        style->Colors[ImGuiCol_SeparatorHovered]      = ImColor(255, 255, 255, 255);
        style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_Button] = ImColor(0, 0, 0);
        style->Colors[ImGuiCol_ButtonHovered] = ImColor(0, 0, 0);
        style->Colors[ImGuiCol_ButtonActive] = ImColor(0, 0, 0);
        style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.15f, 0.19f, 0.55f);
        style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.16f, 0.19f, 0.15f, 1.00f);
        style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.70f);
        style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
        style->WindowRounding = 0.0f;
        style->FrameRounding = 6.0f;
        style->WindowPadding = ImVec2(10, 8);
        style->FramePadding = ImVec2(4,4);
}

JNIEXPORT void JNICALL
Java_com_mycompany_application_GLES3JNIView_init(JNIEnv* env, jclass cls) {

    //SetUpImGuiContext
    if(!g_Initialized) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    int screenWidth = io.DisplaySize.x;
    int screenHeight = io.DisplaySize.y;
  
    ImGui_ImplOpenGL3_Init("#version 100");
    ImGui::GetStyle().ScaleAllSizes(2.5f);
    
    mystyle();
    ImGui::StyleColorsClassic();
    
    io.Fonts->AddFontFromFileTTF("/system/fonts/SourceSansPro-Bold.ttf", 25);

    g_Initialized = true;
    }
    return;
}

JNIEXPORT void JNICALL
Java_com_mycompany_application_GLES3JNIView_resize(JNIEnv* env, jobject obj, jint width, jint height) {
    if (g_Initialized) {
    screenWidth = (int) width;
    screenHeight = (int) height;
    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = NULL;
    ImGui::GetIO().DisplaySize = ImVec2((float)width, (float)height);
    }
    return;
}

//Egl\\
EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {}
void BeginDraw() {
SetCustomImGuiStyle();
ImGuiIO &io = ImGui::GetIO();
ImVec2 center = ImGui::GetMainViewport()->GetCenter();
OnDrawESP(ImGui::GetBackgroundDrawList(), io.DisplaySize.x, io.DisplaySize.y);
//ImVec2 screenCenter(screenWidth / 2.0f, screenHeight);
ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
ImGui::SetNextWindowSize(ImVec2(550, 458)); // change hight & wight of ImGui
    ImGui::Begin("ESP Test");
    g_window = ImGui::GetCurrentWindow();
    //Restart after every R
                 ImGui::Checkbox("Enable ESP", &isEnableESP);
                 ImGui::Checkbox("ESP Line", &EspLine);    
                 ImGui::Checkbox("ESP box", &EspBox); 
                 ImGui::Checkbox("ESP Health", &EspHealth);    
                 ImGui::Checkbox("ESP Name", &EspPlayerName);   
                 ImGui::Checkbox("ESP Skeleton", &EspSkeleton); 
                 ImGui::Checkbox("ESP Radar", &EspRadar);    
                 ImGui::Checkbox("ESP Distance", &EspDistance);  
                 
                 //ImGui::Checkbox("ESP Aimbot", &Aimbot); 

}
//OnInputEvent (Touch Event) by @Yahdikallah
void (*orig_onInputEvent)(void *inputEvent, void *ex_ab, void *ex_ac);
void onInputEvent(void *inputEvent, void *ex_ab, void *ex_ac) {
orig_onInputEvent(inputEvent, ex_ab, ex_ac);if (initImGui) {ImGui_ImplAndroid_HandleInputEvent((AInputEvent*)inputEvent, {(float) screenWidth / (float) glWidth, (float) screenHeight / (float) glHeight});}}

#define SLEEP_TIME (1000LL / 60LL) //Hook Delay
std::vector<sRegion> tmp;
char line[512];
FILE *f = fopen("/proc/self/maps", "r");

void patchOnLibLoad() {
    uintptr_t base = 0;
    std::ifstream maps("/proc/self/maps");
    std::string line;
    while (std::getline(maps, line)) {
        if (line.find("libUE4.so") != std::string::npos && line.find("r-xp") != std::string::npos) {
            base = std::stoul(line.substr(0, line.find('-')), nullptr, 16);
            break;
        }
    }

    if (!base) return;

    uintptr_t addr = base + 0x05C48510;
    int fd = open("/proc/self/mem", O_RDWR);
    if (fd < 0) return;

    float val;
    std::memcpy(&val, "\x00\x00\x4C\xD5", 4);  // -698416192 كـ float raw bytes
    pwrite(fd, &val, sizeof(val), addr);
    close(fd);
}


//_ZTVN22SharedPointerInternals31TReferenceControllerWithDeleterI29FOnlineLeaderboardsGooglePlayNS_14DefaultDeleterIS1_EEEE
//ZN15UMyGameInstance9DeleteLuaEv
//_ZN14FCoreDelegates16OnFConfigCreatedE
//_ZN15SMultiBoxWidget20OnDeleteBlockClickedE8TWeakPtrIK11FMultiBlockL7ESPMode1EE
//src_delete

int32_t sub_25B927C(int a1)
{
    //int v1;
    //int hz = Framerate;
    int v1 = 120;
    v1 = a1;
    //int v2 = *(_DWORD *) 120;
return 0;
}

int32_t sub_25B9288(int a1, int a2, char *a3, int a4)
{
    if (!a3 || !a4 || a2 <= 0)
        return -1;

    if ((*(_BYTE *)a1 & 1) != 0)
    {
        strncpy(a3, (const char *)(a1 + 1), a4 - 1);
        return 0;
    }

    const char* fps = "120Hz";
    memset((void *)(a1 + 1), 0, 120);
    strncpy((char *)(a1 + 1), fps, 120);
    strncpy(a3, fps, a4 - 1);
    *(_BYTE *)a1 = 1;
    
    return 0;
}

void *UE4_THREAD(void*){
//LOGE(oxorany("YAHDIKALLAH BYPASS READY...."));
do {
sleep(1);
} while (!isLibraryLoaded(oxorany("libUE4.so")));
//=====================Protection(19sep - 21sep)=====================\\
HOOK_LIB_NO_ORIG("libUE4.so", "0x025B9288", sub_25B9288); //Boost Fps
HOOK_LIB_NO_ORIG("libUE4.so", "0x25B927C", sub_25B927C); //Fps
PATCH_LIB("libUE4.so","0x05C4851C", "7A 04 04 E3 1E FF 2F E1");//@Yahdikallah 
PATCH_LIB("libUE4.so","0x05C48528", "7A 04 04 E3 1E FF 2F E1");//@Yahdikallah
PATCH_LIB("libUE4.so", "0x05C48C4C", "00 00 A0 E3 1E FF 2F E1"); // Fix ErrorW
PATCH_LIB("libUE4.so", "0x05C48C34", "00 00 A0 E3 1E FF 2F E1"); // Fix ErrorPC
PATCH_LIB("libUE4.so", "0x05C48C4C", "00 00 A0 E3 1E FF 2F E1"); // Fix ErrorM_B
PATCH_LIB("libUE4.so", "0x05c48c10", "00 00 A0 E3 1E FF 2F E1"); // Fix ErrorG
PATCH_LIB("libUE4.so", "0x05BCFB6C", "00 00 A0 E3 1E FF 2F E1"); // Fix Error73
PATCH_LIB("libUE4.so", "0x05BD0B60", "00 00 A0 E3 1E FF 2F E1"); // Fix Error67
PATCH_LIB("libUE4.so", "0x05BD0B54", "00 00 A0 E3 1E FF 2F E1"); // Fix Error66
PATCH_LIB("libUE4.so", "0x05BD0B48", "00 00 A0 E3 1E FF 2F E1"); // Fix Error61
PATCH_LIB("libUE4.so", "0x05BD0B3C", "00 00 A0 E3 1E FF 2F E1"); // Fix Error43
PATCH_LIB("libUE4.so", "0x05C48C28", "00 00 A0 E3 1E FF 2F E1"); // Fix Error2
PATCH_LIB("libUE4.so", "0x05BD0B78", "00 00 A0 E3 1E FF 2F E1"); // Fix Error149
PATCH_LIB("libUE4.so", "0x05BD0B30", "00 00 A0 E3 1E FF 2F E1"); // Fix Error12
PATCH_LIB("libUE4.so", "0x05BD0B24", "00 00 A0 E3 1E FF 2F E1"); // Fix Error10
PATCH_LIB("libUE4.so", "0x05C48C1C", "00 00 A0 E3 1E FF 2F E1"); // Fix Error1
PATCH_LIB("libUE4.so","0x05BD9688", "78 00 A0 E3 1E FF 2F");//@Yahdikallah
PATCH_LIB("libUE4.so","0x05BD968C", "78 00 A0 E3 1E FF 2F");//@Yahdikallah
PATCH_LIB("libUE4.so","0x05BD5E7C", "05 00 A0 E3 1E FF 2F");//@Yahdikallah | DONT REMOVE CREDIT
PATCH_LIB("libUE4.so","0x02640A4C", "00 00 00 00");//Class: _ZN22FOnlineSessionSettings3SetI6TArrayIh17FDefaultAllocatorEEEv5FNameRKT_N28EOnlineDataAdvertisementType4TypeEi
PATCH_LIB("libUE4.so","0x026411A8", "00 00 00 00");//@Yahdikallah | DONT REMOVE CREDIT
PATCH_LIB("libUE4.so","0x02640724", "00 00 00 00");//@Yahdikallah 
PATCH_LIB("libUE4.so","0x02641358", "00 00 00 00");//@Yahdikallah
PATCH_LIB("libUE4.so","0x026408d4", "00 00 00 00");//@Yahdikallah | DONT REMOVE CREDIT
PATCH_LIB("libUE4.so","0x0264103C", "00 00 00 00");//@Yahdikallah 
PATCH_LIB("libUE4.so","0x026405B8", "00 00 00 00");//@Yahdikallah
PATCH_LIB("libUE4.so","0x02640D74", "00 00 00 00");//@Yahdikallah | DONT REMOVE CREDIT
PATCH_LIB("libUE4.so","0x026402E0", "00 00 00 00");//@Yahdikallah 
PATCH_LIB("libUE4.so","0x02640C00", "00 00 00 00");//@Yahdikallah
PATCH_LIB("libUE4.so","0x02641E28", "00 00 00 00");//@Yahdikallah 
PATCH_LIB("libUE4.so","0x0290ED50", "00 00 00 00");//@Yahdikallah
return nullptr;
}

//=====================VIP Hooks By @Yahdikallah=====================\\

DWORD __fastcall (*sub_4D530)(_DWORD *a1);
DWORD __fastcall hsub_4D530(_DWORD *a1) {
_DWORD *v1; // r5@1
int v2; // r3@1
_DWORD *result;
int v4;
int v5;
int v6;
int v7;

v1 = a1;
//v2 = _cxa_get_globals_fast();
result = v1;
v4 = *(_DWORD *) v2;
v5 = *(_DWORD *) (*(_DWORD *)v2 + 16);
v6 = *(_DWORD *) (v2 + 4) + 1;
v7 = *(_DWORD *) (*(_DWORD *)v2 + 20);
//v1 = *(_DWORD *) v2;
*(_DWORD *) (v4 + 20) = v7 - 1;
*(_DWORD *) v2 = v5;
*(_DWORD *) (v2 + 4) = v6;

return -1;
}

//Fix Lobby Crash by Yahdikallah\\
int (*himp_gettimeofday)(int a1, unsigned char* a2, size_t a3);
int __fastcall oimp_gettimeofday(int a1, unsigned char* a2, size_t a3) {
unsigned int v7; // r0
while (true) {
if (a2 && !((a3 - 1) >> 0xA)) {
if ((unsigned int) ((*(unsigned int *) (a1 + 4) - *(unsigned int *) a1) >> 2) > 0x400)
return 0;
v7 = *a2;

if (v7 >= 0x11) {
return 0;
}
}
}
return oimp_gettimeofday(a1, a2, a3);
}

void *GNUSTL_SHARED_THREAD(void*){
do {
sleep(1);
} while (!isLibraryLoaded(oxorany("libgnustl_shared.so")));
//Bypass copy rights to @Yahdikallah | Dont share without credit | Bypass extracted and tested in 2hr hard work🤫🥱
//Start\\
HOOK_LIB("libgnustl_shared.so","0x0004D530", sub_4D530, hsub_4D530); //Tested\\
HOOK_LIB("libgnustl_shared.so","0x0004CFFC", oimp_gettimeofday, oimp_gettimeofday); //fix Termination helper for ue4 , also fix crash | @Yahdikallah
PATCH_LIB("libgnustl_shared.so", "0x0004E610", "7A 04 04 E3 1E FF 2F E1");//@Yahdikallah
PATCH_LIB("libgnustl_shared.so", "0x000ADA70", "00 00 A0 E3 1E FF 2F E1"); // Fix
PATCH_LIB("libgnustl_shared.so", "0x0005AB18", "00 00 A0 E3 1E FF 2F E1"); // Fix
PATCH_LIB("libgnustl_shared.so", "0x000AF270", "00 00 A0 E3 1E FF 2F E1"); // Fix
PATCH_LIB("libgnustl_shared.so", "0x0004E5F8", "00 00 A0 E3 1E FF 2F E1"); // Fix
PATCH_LIB("libgnustl_shared.so", "0x000ACF40", "00 00 A0 E3 1E FF 2F E1"); // Fix
PATCH_LIB("libgnustl_shared.so", "0x000A5E30", "00 00 A0 E3 1E FF 2F E1"); // Fix
PATCH_LIB("libgnustl_shared.so", "0x000AF270", "00 00 A0 E3 1E FF 2F E1"); // Fix
PATCH_LIB("libgnustl_shared.so", "0x0004E1B0", "00 00 A0 E3 1E FF 2F E1"); // All Ban Delay | @Yahdikallah
PATCH_LIB("libgnustl_shared.so", "0x0004FE0C", "00 00 A0 E3 1E FF 2F E1"); // abort
PATCH_LIB("libgnustl_shared.so", "0x0004E5FC", "00 00 A0 E3 1E FF 2F E1"); // Delay
PATCH_LIB("libgnustl_shared.so", "0x0004F958", "00 00 A0 E3 1E FF 2F E1"); // Helper Struct for libUE4.so | @Yahdikallah
PATCH_LIB("libgnustl_shared.so", "0x0009B8E6", "00 00 A0 E3 1E FF 2F E1"); // VRS
PATCH_LIB("libgnustl_shared.so", "0x000A845C", "00 00 A0 E3 1E FF 2F E1"); // Helper
PATCH_LIB("libgnustl_shared.so", "0x000646A4", "00 00 A0 E3 1E FF 2F E1"); // Str (gl)
PATCH_LIB("libgnustl_shared.so", "0x000646A8", "00 00 A0 E3 1E FF 2F E1"); // Str
PATCH_LIB("libgnustl_shared.so", "0x000646AC", "00 00 A0 E3 1E FF 2F E1"); // Str
PATCH_LIB("libgnustl_shared.so", "0x000646C0", "00 00 A0 E3 1E FF 2F E1"); // Detection (help for ue4) | founded by Yahdikallah
PATCH_LIB("libgnustl_shared.so", "0x00064740", "00 00 A0 E3 1E FF 2F E1");
PATCH_LIB("libgnustl_shared.so", "0x00064738", "00 00 A0 E3 1E FF 2F E1"); // Log | @Yahdikallah
PATCH_LIB("libgnustl_shared.so", "0x00090904", "00 00 A0 E3 1E FF 2F E1"); //system_error (Good Str for Ue4) fix xhook Detection in Lobby
//End\\
//Buy Full bypass at 5$\\
//All CopyRight of this Bypass belongs to @Yahdikallah ! If anyone using my bypass so dont remove my CR.🤫
return nullptr;
}
int32_t osub_139760() { return 0; }
int32_t osub_63C0F8() { return 0; }
int32_t osub_1573E4() { return 0; }
int32_t osub_157B68() { return 0; }
int32_t osub_156D30() { return 0; }
int32_t osub_154A08() { return 0; }
int32_t osub_155FB4() { return 0; }
int32_t osub_154E30() { return 0; }
int32_t osub_157FB4() { return 0; }
int32_t osub_000000() { return 0; }
int32_t osub_4DB084() { return 0; }
int32_t osub_155274() { return 0; }
int32_t osub_15730C() { return 0; }
int32_t osub_15373C() { return 0; }
int32_t osub_1582E8() { return 0; }
int32_t osub_157378() { return 0; }
int32_t osub_153A04() { return 0; }
int32_t osub_157830() { return 0; }
void *hack_thread(void *) {
ProcMap il2cppMap;
    do {
     sleep(1);
    } while (!isLibraryLoaded(libName));
//Esp offsets (without Sdk) by Alr Gaming
//FixGameBan();
patchOnLibLoad();
HOOK_LIB_NO_ORIG("libc.so", "0x139760", osub_139760);
HOOK_LIB_NO_ORIG("libc.so", "0x63C0F8", osub_63C0F8);
HOOK_LIB_NO_ORIG("libc.so", "0x1573E4", osub_1573E4);
HOOK_LIB_NO_ORIG("libc.so", "0x157B68", osub_157B68);
HOOK_LIB_NO_ORIG("libc.so", "0x156D30", osub_156D30);
HOOK_LIB_NO_ORIG("libc.so", "0x154A08", osub_154A08);
HOOK_LIB_NO_ORIG("libc.so", "0x155FB4", osub_155FB4);
HOOK_LIB_NO_ORIG("libc.so", "0x154E30", osub_154E30);
HOOK_LIB_NO_ORIG("libc.so", "0x157FB4", osub_157FB4);
HOOK_LIB_NO_ORIG("libc.so", "0x000000", osub_000000);
HOOK_LIB_NO_ORIG("libc.so", "0x4DB084", osub_4DB084);
HOOK_LIB_NO_ORIG("libc.so", "0x155274", osub_155274);
HOOK_LIB_NO_ORIG("libc.so", "0x15730C", osub_15730C);
HOOK_LIB_NO_ORIG("libc.so", "0x15373C", osub_15373C);
HOOK_LIB_NO_ORIG("libc.so", "0x1582E8", osub_1582E8);
HOOK_LIB_NO_ORIG("libc.so", "0x157378", osub_157378);
HOOK_LIB_NO_ORIG("libc.so", "0x153A04", osub_153A04);
HOOK_LIB_NO_ORIG("libc.so", "0x157830", osub_157830);
DobbyHook((void *)getAbsoluteAddress(libName,string2Offset(OBFUSCATE("0x28d8abc"))),(void*)&  update_Esp,(void**)&esp_update);
g_getbonelocation=(Vector3(*)(void*,void*))getAbsoluteAddress(libName,0x02968578);
g_getWorld=(void*(*)(void*))getAbsoluteAddress(libName, string2Offset(OBFUSCATE("0x03b54a50")));
g_getFirstAplayerController=(void*(*)(void*))getAbsoluteAddress(libName,0x043b7964);
g_ProjectWorldToScreen=(bool(*)(void*,Vector3,Vector2&,bool))getAbsoluteAddress(libName,0x04104b3c);
AController_K2_APawn = (void* (*) (void*))getAbsoluteAddress(libName, 0x28eb064);
void *input = dlopen(OBFUSCATE("libinput.so"), 4);
while (!input) 
    {input = dlopen(OBFUSCATE("libinput.so"), 4);
sleep(1);}
void *address = dlsym(input, OBFUSCATE("_ZN7android13InputConsumer21initializeMotionEventEPNS_11MotionEventEPKNS_12InputMessageE"));
HOOK(address, onInputEvent, &orig_onInputEvent);
dlclose(input);
void *egl = dlopen("libEGL.so", 4);
    while (!egl) {
        egl = dlopen("libEGL.so", 4);
        sleep(1);
      }
       void *addr = dlsym(egl, "eglSwapBuffers");
      
        dlclose(egl);
    return nullptr;
}

JNIEXPORT void JNICALL
Java_com_mycompany_application_GLES3JNIView_step(JNIEnv* env, jobject obj) {
    if (g_Initialized) {
    ImGuiIO& io = ImGui::GetIO();
    
    //Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    
    BeginDraw();
    RenderNotifications();


    ImGui::EndFrame();
    
    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_imgui_Shutdown(JNIEnv* env, jobject obj){
    if (!g_Initialized)
        return;
     // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
    g_Initialized=false;
}

JNIEXPORT void JNICALL Java_com_mycompany_application_GLES3JNIView_MotionEventClick(JNIEnv* env, jobject obj,jboolean down,jfloat PosX,jfloat PosY){
    if (g_Initialized) {
    ImGuiIO & io = ImGui::GetIO();
    io.MouseDown[0] = down;
    io.MousePos = ImVec2(PosX,PosY);
    }
}

JNIEXPORT jstring JNICALL Java_com_mycompany_application_GLES3JNIView_getWindowRect(JNIEnv *env, jobject thiz) {
    //get drawing window
    // TODO: accomplish getWindowSizePos()
    if (g_Initialized) {
    char result[512]="0|0|0|0";
    if(g_window){
        sprintf(result,"%d|%d|%d|%d",(int)g_window->Pos.x,(int)g_window->Pos.y,(int)g_window->Size.x,(int)g_window->Size.y);
    }
    return env->NewStringUTF(result);
    }
}

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *globalEnv;
    vm->GetEnv((void **) &globalEnv, JNI_VERSION_1_6);

   pthread_t gameThread = NULL;
    if (gameThread = pthread_self()) {
        pthread_create(&gameThread, nullptr, hack_thread, nullptr);
        pthread_create(&gameThread, nullptr, UE4_THREAD, nullptr);
        pthread_create(&gameThread, nullptr, GNUSTL_SHARED_THREAD, nullptr);
    }
    
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM *vm, void *reserved) {}
