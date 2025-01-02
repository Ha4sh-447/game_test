#include <raylib.h>

void jump(Vector2 *pos) {
  // TODO: make proper updation logic using for loop and acceleration
}

int main(void) {
  int posX = 400;
  int posY = 800 - 128;

  InitWindow(800, 800, "PLAYYAYYA");
  SetTargetFPS(60);

  Color color = {(unsigned char)GetRandomValue(0, 255),
                 (unsigned char)GetRandomValue(0, 255),
                 (unsigned char)GetRandomValue(0, 255), 255};

  Texture2D scarfy = LoadTexture("./resources/scarfy.png");

  if (scarfy.id == 0) {
    TraceLog(LOG_ERROR, "Failed to load texture scarfy.png");
    CloseWindow();
    return -1;
  }

  unsigned frameCount = 6;
  int numFrames = 6;
  int frameWidth = scarfy.width / numFrames;
  int frameHeight = scarfy.height;

  int currFrame = 0;         // Current frame index
  int frameDelay = 5;        // After 5 iterations change the frame
  int frameDelayCounter = 0; // A counter to check if 5 iterations have passed
                             // so that frame can be updated

  Rectangle frameRec = {0.0f, 0.0f, (float)frameWidth, (float)frameHeight};
  Vector2 scarfyPos = {(float)posX, (float)posY};

  bool isFacingRight = true;

  while (!WindowShouldClose()) {
    // Frame updation
    ++frameDelayCounter; // update counter
    if (frameDelayCounter > frameDelay) {
      frameDelayCounter = 0;  // reset the counter
      ++currFrame;            // move to next fram
      currFrame %= numFrames; // Wrap to 0
      frameRec.x = (float)frameWidth *
                   currFrame; // update the x coordinate of the sprite sheet
    }

    // Update position
    if (IsKeyDown(KEY_DOWN) && (scarfyPos.y + 128 < 800)) {
      scarfyPos.y += 3;
    }
    if (IsKeyDown(KEY_UP) && (scarfyPos.y > 0)) {
      scarfyPos.y -= 3;
    }
    if (IsKeyDown(KEY_LEFT) && (scarfyPos.x > 0)) {
      scarfyPos.x -= 3;
      isFacingRight = false;
    }
    if (IsKeyDown(KEY_RIGHT) && (scarfyPos.x + 128 < 800)) {
      scarfyPos.x += 3;
      isFacingRight = true;
    }
    if (IsKeyDown(KEY_SPACE)) {
      jump(&scarfyPos);
    }

    frameRec.width = isFacingRight ? (float)frameWidth : -(float)frameWidth;
    // Draw on screen
    BeginDrawing();
    ClearBackground(GREEN);

    DrawTextureRec(
        scarfy, frameRec, scarfyPos,
        WHITE); // to move the char we would need to update scarfyPos vector
    EndDrawing();
  }

  UnloadTexture(scarfy);
  CloseWindow();
  return 0;
}
