#include "./src/config.h"
#include "./src/player.h"
#include "raylib.h"

int main(void) {
  // Init window
  InitWindow(screenWidth, screenHeight, "TESTIES");
  InitAudioDevice();
  SetTargetFPS(60);

  Player player({screenWidth / 2.0f, groundYPos - 100});

  // game loop
  while (!WindowShouldClose()) {
    player.HandleControls();
    player.Update();

    BeginDrawing();
    ClearBackground(LIME);
    DrawRectangle(0, groundYPos, screenWidth, screenHeight - groundYPos,
                  DARKBROWN);
    player.Draw();
    EndDrawing();
  }

  // De init
  player.Unload();
  CloseAudioDevice();
  CloseWindow();

  return 0;
}
