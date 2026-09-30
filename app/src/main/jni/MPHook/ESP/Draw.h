#ifndef ImGuiAndroid_Draww
#define ImGuiAndroid_Draww

#include "ImGui/imgui_internal.h"
#include "Struc.h"
#include "Vector2.h"

namespace DrawAddLine
{
    void DrawLine(ImVec2 start, ImVec2 end, ImVec4 color, float thickness) {
        auto background = ImGui::GetBackgroundDrawList();
        if(background) {
            background->AddLine(start, end, ImColor(color.x, color.y, color.z, color.w), thickness);
        }
    }
    
    
    
    void DrawCrosshair(ImVec4 color, Vector2 center, float size) {
        float x = center.X - (size / 2.0f);
        float y = center.Y - (size / 2.0f);
        DrawLine(ImVec2(x, center.Y), ImVec2(x + size, center.Y), ImVec4(120, 120, 120, 120),1);
        DrawLine(ImVec2(center.X, y), ImVec2(center.X, y + size), ImVec4(120, 120, 120, 120),1);
    }
    
    void DrawBox(ImVec4 color, float stroke, Rect rect) {
        Vector2 v1 = Vector2(rect.x, rect.y);
        Vector2 v2 = Vector2(rect.x + rect.width, rect.y);
        Vector2 v3 = Vector2(rect.x + rect.width, rect.y + rect.height);
        Vector2 v4 = Vector2(rect.x, rect.y + rect.height);

        DrawLine(ImVec2(v1.X, v1.Y), ImVec2(v2.X, v2.Y), color, stroke); // LINE UP
        DrawLine(ImVec2(v2.X,v2.Y), ImVec2(v3.X, v3.Y),color, stroke); // LINE RIGHT
        DrawLine(ImVec2(v3.X,v3.Y), ImVec2(v4.X,v4.Y),color, stroke); // LINE DOWN
        DrawLine(ImVec2(v4.X, v4.Y), ImVec2(v1.X, v1.Y),color, stroke); // LINE LEFT
    }
    void DrawFilledBox(ImVec4 color, float stroke, Rect rect){
        for(float i = 0; i < rect.height; i += stroke){
            DrawLine(ImVec2(rect.x, rect.y + i), ImVec2(rect.x + rect.width, rect.y + i), color, stroke);
        }
    }
    
    void DrawBoxWithStats(
    ImVec4 boxColor, 
    ImVec4 healthColor, 
    ImVec4 armorColor, 
    float stroke, 
    Rect mainRect, 
    int health, 
    int armor
) {
    // Gambar kotak utama
    DrawBox(boxColor, stroke, mainRect);

    // Hitung posisi dan ukuran untuk bar Health (di kiri)
    float healthBarWidth = mainRect.width * 0.1f; // Lebar 10% dari kotak utama
    float healthBarHeight = mainRect.height; // Tinggi sama dengan kotak utama
    float healthBarX = mainRect.x - (healthBarWidth + stroke);
    float healthBarY = mainRect.y;
    Rect healthBarRect = Rect(healthBarX, healthBarY, healthBarWidth, healthBarHeight);

    // Gambar bar Health yang terisi
    if (health > 0) {
        float healthFillHeight = healthBarHeight * (health / 100.0f); // Persentase pengisian
        Rect healthFillRect = Rect(healthBarX, healthBarY + (healthBarHeight - healthFillHeight), healthBarWidth, healthFillHeight);
        DrawFilledBox(healthColor, stroke, healthFillRect);
    }
    
    // Hitung posisi dan ukuran untuk bar Armor (di kanan)
    float armorBarWidth = mainRect.width * 0.1f; // Lebar 10% dari kotak utama
    float armorBarHeight = mainRect.height; // Tinggi sama dengan kotak utama
    float armorBarX = mainRect.x + mainRect.width + stroke;
    float armorBarY = mainRect.y;
    Rect armorBarRect = Rect(armorBarX, armorBarY, armorBarWidth, armorBarHeight);

    // Gambar bar Armor yang terisi
    if (armor > 0) {
        float armorFillHeight = armorBarHeight * (armor / 100.0f); // Persentase pengisian
        Rect armorFillRect = Rect(armorBarX, armorBarY + (armorBarHeight - armorFillHeight), armorBarWidth, armorFillHeight);
        DrawFilledBox(armorColor, stroke, armorFillRect);
    }
}
static float radarSweepAngle = 0.0f;
void DrawCircle(float X, float Y, float radius, bool filled, ImVec4 color) {
        auto background = ImGui::GetBackgroundDrawList();
        if(background) {
            if(filled) {
                background->AddCircleFilled(ImVec2(X, Y), radius, ImColor(color.x, color.y, color.z, color.w));
            }
            else {
                background->AddCircle(ImVec2(X, Y), radius, ImColor(color.x, color.y, color.z, color.w));
            }
        }
    }
    
// Fungsi untuk menggambar radar
void DrawRadar(
    Vector3 myPlayerPosition, 
    Vector2 radarCenter, 
    float radarRadius, 
    Vector3 enemyPosition
) {
    // --- Langkah 1: Menggambar Radar dan Titik Pemain ---
    
    // Gambar lingkaran luar radar
    DrawCircle(radarCenter.X, radarCenter.Y, true, radarRadius, ImVec4(5,255,5,100));
    
    // Gambar titik di tengah radar (posisi pemain utama)
    DrawCircle(radarCenter.X, radarCenter.Y, true, 5.0f, ImVec4(0,255,0,255));
    
    // --- Langkah 2: Menggambar Garis Putar (Radar Sweep) ---
    
    // Tambah sudut rotasi setiap bingkai (sesuaikan kecepatan rotasinya)
    radarSweepAngle += 0.05f; 
    
    // Batasi sudut antara 0 dan 2*PI untuk mencegah overflow
    if (radarSweepAngle > 2 * M_PI) {
        radarSweepAngle -= 2 * M_PI;
    }

    // Hitung posisi ujung garis putar menggunakan trigonometri
    float sweepEndX = radarCenter.X + radarRadius * cos(radarSweepAngle);
    float sweepEndY = radarCenter.Y + radarRadius * sin(radarSweepAngle);
    
    Vector2 sweepEndPos = Vector2(sweepEndX, sweepEndY);
    
    // Gambar garis putar dari tengah radar ke posisi yang dihitung
    DrawLine(ImVec2(radarCenter.X, radarCenter.Y), ImVec2(sweepEndPos.X, sweepEndPos.Y), ImVec4(255,255,255,255), 1.0f);

    // --- Langkah 3: Menggambar Posisi Musuh ---
    
    // (Kode yang sama dari sebelumnya)
  //  for (const auto& enemyPosition : enemyPositions) {
        Vector3 relativePos = enemyPosition - myPlayerPosition;
        relativePos.Z = 0;
        
        float scaleFactor = 0.5f; 
        Vector3 scaledPos = relativePos * scaleFactor;
        
        if (Vector3::Magnitude(scaledPos) > radarRadius) {
            scaledPos = Vector3::Normalized(scaledPos) * radarRadius;
        }

        Vector2 finalRadarPos = Vector2(radarCenter.X + scaledPos.X, radarCenter.Y + scaledPos.Y);

        DrawCircle(finalRadarPos.X, finalRadarPos.Y, 5.0f, true, ImVec4(255,0,0,255)); 
   // }
}
    
    void DrawText2(float fontSize, ImVec2 position, ImVec4 color, const char *text)
    {
        auto background = ImGui::GetBackgroundDrawList();

        if(background)
        {
            background->AddText(NULL, fontSize, position, ImColor(color.x, color.y, color.z, color.w), text);
        }
    }
    
    
    
    
    float get_3D_Distance(float Self_x, float Self_y, float Self_z, float Object_x, float Object_y, float Object_z)
    {
        float x, y, z;
        x = Self_x - Object_x;
        y = Self_y - Object_y;
        z = Self_z - Object_z;
        return (float)(sqrt(x * x + y * y + z * z));
    }
    extern int (*GetCurrentTimeRound)(void* player);

   void DrawHorizontalHealthBar(Vector2 screenPos, float width,int maxHealth, int currentHealth) {
       int scaledMaxHealth =  maxHealth * 100;
       int scaledCurrentHealth = currentHealth * 100;
       screenPos -= Vector2(0.0f, 8.0f);
        DrawBox(ImVec4(0, 0, 0, 255), 3, Rect(screenPos.X - (width / 2) , screenPos.Y, width + 2, 5.0f));
        DrawBox(ImVec4(0, 0, 0, 255), 3, Rect(screenPos.X - (width / 2) , screenPos.Y - 2.5f, width + 2, 5.0f));
        screenPos += Vector2(1.0f, 1.0f);
        ImVec4 clr = ImVec4(0, 255, 0, 255);
        int hpWidth = (scaledCurrentHealth * width) / scaledMaxHealth;
      /*  if (scaledCurrentHealth <= (scaledMaxHealth * 0.6f)) {
            clr = ImVec4(255, 255, 0, 255);
        }
        if (scaledCurrentHealth < (scaledMaxHealth * 0.3f)) {
            clr = ImVec4(255, 0, 0, 255);
        }*/
        std::string hp = std::to_string(scaledCurrentHealth);
        DrawText2(25.5f, ImVec2(screenPos.X - (width / 2), screenPos.Y), ImVec4(255,1,1,255), hp.c_str()); 
        DrawBox(clr, 3, Rect(screenPos.X - (width / 2), screenPos.Y, hpWidth, 3.0f));
      //  DrawBox(ImVec4(0,255,0,255), 3, Rect(screenPos.X - (width / 2), screenPos.Y-2.5f, armor*width, 3.0f));
        }

    
	
    
}


#endif
