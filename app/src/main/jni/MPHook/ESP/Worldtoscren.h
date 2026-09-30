// world_to_screen_custom.hpp
#pragma once
#include <cmath>
#include <cstdint>
#include <cstring>

// ----------------- Basic math types -----------------
struct FRotator {
    float Pitch; // X
    float Yaw;   // Y
    float Roll;  // Z
};

// 4x4 matrix (row-major)
struct Mat4 {
    float m[4][4];
};

// ----------------- Engine function offsets (adjust to your dump) -----------------
// These must be set to the correct offsets for your game/library.
static uintptr_t G_BASE = 0; // set to base address of game module if needed
static void* (*GetCameraLocation_fn)(void* owner) = (void*(*)(void*))0; // optional if member
// Example: if functions are global with relative offsets (replace with your real addresses)
static Vector3 (*GetCameraLocation_real)() = (Vector3(*)())(/*0x40FB7E4*/ 0x40FB7E4);
static FRotator (*GetCameraRotation_real)() = (FRotator(*)())(/*0x40FB76C*/ 0x40FB76C);
static float (*GetFovAngle_real)() = (float(*)())(/*0x40FB7CA*/ 0x40FB7CA);

// If your functions are instance methods, adapt signatures accordingly:
// e.g. Vector3 (*GetCameraLocation_real)(void* PlayerController) = (Vector3(*)(void*)) (g_base + OFFSET);

// ----------------- Helpers -----------------
static inline float DegToRad(float deg) { return deg * (3.14159265358979323846f / 180.0f); }

static inline bool is_valid_float(float v) {
    return std::isfinite(v);
}

static Mat4 Mat4Identity() {
    Mat4 I; std::memset(&I, 0, sizeof(I));
    I.m[0][0] = I.m[1][1] = I.m[2][2] = I.m[3][3] = 1.0f;
    return I;
}

// Multiply 4x4 matrices: R = A * B
static Mat4 Mat4Mul(const Mat4& A, const Mat4& B) {
    Mat4 R; std::memset(&R, 0, sizeof(R));
    for (int r=0;r<4;r++) for (int c=0;c<4;c++) {
        float s=0.0f;
        for (int k=0;k<4;k++) s += A.m[r][k] * B.m[k][c];
        R.m[r][c] = s;
    }
    return R;
}

// Transform world pos (x,y,z,1) by matrix M: out = M * vec4
static void Mat4MulVec4(const Mat4& M, const Vector3& v, float &outX, float &outY, float &outW) {
    outX = M.m[0][0]*v.x + M.m[0][1]*v.y + M.m[0][2]*v.z + M.m[0][3]*1.0f;
    outY = M.m[1][0]*v.x + M.m[1][1]*v.y + M.m[1][2]*v.z + M.m[1][3]*1.0f;
    outW = M.m[3][0]*v.x + M.m[3][1]*v.y + M.m[3][2]*v.z + M.m[3][3]*1.0f;
}

// ----------------- Build View Matrix from camera rot & pos -----------------
// NOTE: UE uses left-handed coordinates (X forward, Y right, Z up). Adjust if needed.
static Mat4 BuildViewMatrix(const Vector3& camPos, const FRotator& camRot) {
    // Convert rotator to radians
    float pitch = DegToRad(camRot.Pitch);
    float yaw   = DegToRad(camRot.Yaw);
    float roll  = DegToRad(camRot.Roll);

    // Compute forward, right, up vectors
    float sp = sinf(pitch), cp = cosf(pitch);
    float sy = sinf(yaw),   cy = cosf(yaw);
    float sr = sinf(roll),  cr = cosf(roll);

    // Using Unreal convention:
    // Forward vector
    Vector3 forward = { cp * cy, cp * sy, sp };
    // Right vector = cross(forward, worldUp)
    Vector3 up = { -sr*sp*cy + cr*-sy, -sr*sp*sy + cr*cy, -sr*cp };
    Vector3 right = { cr*cp*cy + sr*sy, cr*cp*sy - sr*cy, cr*sp };

    // Build rotation matrix (camera rotation)
    Mat4 R = Mat4Identity();
    // Row-major: rows are right, up, forward (for view matrix we need inverse rotation)
    // For view matrix we use transpose of rotation (inverse for orthonormal)
    // Here set as:
    R.m[0][0] = right.x; R.m[0][1] = right.y; R.m[0][2] = right.z; R.m[0][3] = 0.0f;
    R.m[1][0] = up.x;    R.m[1][1] = up.y;    R.m[1][2] = up.z;    R.m[1][3] = 0.0f;
    R.m[2][0] = forward.x;R.m[2][1] = forward.y;R.m[2][2] = forward.z;R.m[2][3] = 0.0f;
    R.m[3][0] = 0; R.m[3][1] = 0; R.m[3][2] = 0; R.m[3][3] = 1.0f;

    // Translation
    Mat4 T = Mat4Identity();
    T.m[0][3] = -camPos.x;
    T.m[1][3] = -camPos.y;
    T.m[2][3] = -camPos.z;

    // View = R * T
    Mat4 view = Mat4Mul(R, T);
    return view;
}

// ----------------- Build Projection Matrix from FOV & aspect -----------------
// We'll build a standard RHS projection matrix (clip space w). Adjust near/far as needed.
static Mat4 BuildProjectionMatrix(float fovDeg, float aspect, float nearPlane = 10.0f, float farPlane = 10000.0f) {
    Mat4 P; std::memset(&P, 0, sizeof(P));
    float fovRad = DegToRad(fovDeg);
    float f = 1.0f / tanf(fovRad * 0.5f);
    // Using DirectX style (row-major), mapping to clip space [-1,1]
    P.m[0][0] = f / aspect;
    P.m[1][1] = f;
    P.m[2][2] = farPlane / (farPlane - nearPlane);
    P.m[2][3] = (-farPlane * nearPlane) / (farPlane - nearPlane);
    P.m[3][2] = 1.0f;
    P.m[3][3] = 0.0f;
    return P;
}

// ----------------- WorldToScreen core -----------------
static bool WorldToScreen_Custom(const Vector3& world, Vector2& outScreen, const Mat4& viewProj, float screenW, float screenH) {
    float cx, cy, cw;
    Mat4MulVec4(viewProj, world, cx, cy, cw);
    if (!is_valid_float(cx) || !is_valid_float(cy) || !is_valid_float(cw)) return false;

    // If cw is very small or negative (behind camera) -> reject
    if (cw < 0.0001f) return false;

    float invw = 1.0f / cw;
    float ndcX = cx * invw;
    float ndcY = cy * invw;

    // Convert NDC [-1,1] to screen coordinates
    outScreen.x = (screenW * 0.5f) + (ndcX * 0.5f * screenW);
    outScreen.y = (screenH * 0.5f) - (ndcY * 0.5f * screenH); // flip Y for top-left origin

    // Validate final coords
    if (!is_valid_float(outScreen.x) || !is_valid_float(outScreen.y)) return false;
    if (outScreen.x < -10000.0f || outScreen.x > screenW + 10000.0f) return false;
    if (outScreen.y < -10000.0f || outScreen.y > screenH + 10000.0f) return false;

    return true;
}

// ----------------- High-level helpers to get camera data -----------------
// These functions call your game's camera getters. You must set correct pointers/offsets.
static bool GetCameraData(Vector3 &outLoc, FRotator &outRot, float &outFov) {
    // try to read via functions (these addresses must be valid in your process)
    // If functions are actually member functions, change signature to pass instance pointer.
    // Example uses global (no-arg) functions as placeholders.
    if (!GetCameraLocation_real || !GetCameraRotation_real || !GetFovAngle_real) return false;

    outLoc = GetCameraLocation_real();
    outRot = GetCameraRotation_real();
    outFov = GetFovAngle_real();

    // validate
    if (!is_valid_float(outLoc.x) || !is_valid_float(outLoc.y) || !is_valid_float(outLoc.z)) return false;
    if (!is_valid_float(outRot.Pitch) || !is_valid_float(outRot.Yaw) || !is_valid_float(outRot.Roll)) return false;
    if (!is_valid_float(outFov) || outFov <= 0.0f || outFov > 180.0f) return false;

    return true;
}

// ----------------- Full routine: get viewProj matrix then world->screen -----------------
bool WorldToScreen_FromCamera(const Vector3& worldPos, Vector2& screenPos, float screenWidth, float screenHeight) {
    Vector3 camLoc;
    FRotator camRot;
    float fov;
    if (!GetCameraData(camLoc, camRot, fov)) return false;

    Mat4 view = BuildViewMatrix(camLoc, camRot);
    float aspect = (screenWidth > 0.0f && screenHeight > 0.0f) ? (screenWidth / screenHeight) : 1.0f;
    Mat4 proj = BuildProjectionMatrix(fov, aspect, 10.0f, 10000.0f);

    Mat4 viewProj = Mat4Mul(proj, view); // projection * view

    return WorldToScreen_Custom(worldPos, screenPos, viewProj, screenWidth, screenHeight);
}

// ----------------- Example integration into DrawESP -----------------
// Usage:
//   Vector3 actorPos = GetActorLocationSafe(player);
//   Vector2 screen; if (WorldToScreen_FromCamera(actorPos, screen, screenW, screenH)) { draw ... }

////////////////////////////////////////////////////////////////////////
// End of world_to_screen_custom.hpp
////////////////////////////////////////////////////////////////////////