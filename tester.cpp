#include <chrono>
#include <raylib.h>

float getCurrentTime() {
  auto now = std::chrono::high_resolution_clock::now();
  auto timeSinceEpochs = now.time_since_epoch();

  return std::chrono::duration<float>(timeSinceEpochs).count();
}

void keepWithinBorder() {}

int main() {
  InitWindow(800, 800, "PLAYYAYYA");
  SetTargetFPS(60);

  Color color = {(unsigned char)GetRandomValue(0, 255),
                 (unsigned char)GetRandomValue(0, 255),
                 (unsigned char)GetRandomValue(0, 255), 255};

  while (!WindowShouldClose()) {

    BeginDrawing();
    DrawRectangle(400, 400, 50, 50, WHITE);
    EndDrawing();
  }

  return 0;
}
