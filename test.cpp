#include <raylib.h>

int main(void) {
  // Initialize player position
  int playerX = 400;
  int playerY = 400;

  // Initialize the window BEFORE loading textures
  InitWindow(800, 800, "PLAYYYA");
  SetTargetFPS(60);

  // Load texture AFTER initializing the window
  Texture2D scarfy = LoadTexture("./resources/scarfy.png");

  // Check if the texture loaded successfully
  if (scarfy.id == 0) {
    TraceLog(LOG_ERROR, "Failed to load texture scarfy.png");
    CloseWindow();
    return -1;
  }

  // Generate a random color
  Color color = {(unsigned char)GetRandomValue(0, 255),
                 (unsigned char)GetRandomValue(0, 255),
                 (unsigned char)GetRandomValue(0, 255), 255};

  // Main game loop
  while (!WindowShouldClose()) {
    // Event handling
    if (IsKeyDown(KEY_RIGHT))
      playerX += 3;
    if (IsKeyDown(KEY_LEFT))
      playerX -= 3;
    if (IsKeyDown(KEY_UP))
      playerY -= 3;
    if (IsKeyDown(KEY_DOWN))
      playerY += 3;

    // Drawing
    BeginDrawing();
    ClearBackground(GREEN);

    // Draw the loaded texture
    // Check whether it works the same with DrawTexture()
    // DrawTextureEx(scarfy, (Vector2){0, 0}, 0.0f, 1.0f, WHITE);
    DrawTexture(scarfy, 15, 40, WHITE);

    // Draw the rectangle
    DrawRectangle(playerX - 50, playerY - 50, 50, 50, color);

    EndDrawing();
  }

  // Unload texture and close window
  UnloadTexture(scarfy);
  CloseWindow();

  return 0;
}
