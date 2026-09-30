#include <vector>
#include <string>
#include <chrono>

struct Notification {
    std::string message;
    std::chrono::steady_clock::time_point timestamp;
    float duration;
};

std::vector<Notification> notifications;

void AddNotification(const std::string& message, float duration = 3.0f) {
    notifications.push_back({ message, std::chrono::steady_clock::now(), duration });
}

void RenderNotifications() {
    float y = 10.0f;
    for (auto it = notifications.begin(); it != notifications.end();) {
        float elapsed = std::chrono::duration<float>(std::chrono::steady_clock::now() - it->timestamp).count();
        if (elapsed > it->duration) {
            it = notifications.erase(it);
            continue;
        }
/*
        ImGui::SetNextWindowBgAlpha(0.5f); // Прозрачность
        ImGui::SetNextWindowPos(ImVec2(10, y), ImGuiCond_Always);
        ImGui::Begin("##Notification", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoFocusOnAppearing);
        ImGui::Text("%s", it->message.c_str());
        ImGui::End();
*/
        y += 30.0f; // Расстояние между уведомлениями
        ++it;
    }
}
