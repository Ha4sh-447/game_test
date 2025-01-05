#include <chrono>
#include <raylib.h>

#define MAX_JUMP_HEIGHT 400.0f

struct Velocity {
  float Vx;
  float Vy;
};

void jump(Vector2 *pos, Velocity *velo) {
  // TODO: make proper updation logic using for loop and acceleration
  int h = 0;
  float currPos = pos->y;
  for (h = 0; h <= (int)MAX_JUMP_HEIGHT; h += 10) {
    if (h < (int)MAX_JUMP_HEIGHT) {
      pos->y -= MAX_JUMP_HEIGHT / 20;
    } else {
      pos->y += MAX_JUMP_HEIGHT / 25;
    }
  }
}

void animateChar(Rectangle *frameRec, int frameDelay, int numFrame,
                 int *currFrame, int *frameDelayCounter) {
  float frameWdith = frameRec->width;
  ++(*frameDelayCounter);
  if (*frameDelayCounter > frameDelay) {
    (*currFrame)++;
    *frameDelayCounter = 0;
    *currFrame %= numFrame;
    frameRec->x = frameWdith * (*currFrame);
  }
}

float getCurrentTime() {
  auto now = std::chrono::high_resolution_clock::now();
  auto timeSinceEpochs = now.time_since_epoch();

  return std::chrono::duration<float>(timeSinceEpochs).count();
}

int main(void) {
  int posX = 400;
  int posY = 800 - 128;

  // Character initially at halt
  Velocity scarfyVel = {0, 0};
  Vector2 gravity = {0, 2};

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

  float prevTime = 0;
  float currTime = getCurrentTime();

  while (!WindowShouldClose()) {
    // Update position
    if (IsKeyDown(KEY_RIGHT)) {
      scarfyVel.Vx = 3; // Move right
      animateChar(&frameRec, frameDelay, numFrames, &currFrame,
                  &frameDelayCounter);
      isFacingRight = true;
    } else if (IsKeyDown(KEY_LEFT)) {
      scarfyVel.Vx = -3; // Move left
      animateChar(&frameRec, frameDelay, numFrames, &currFrame,
                  &frameDelayCounter);
      isFacingRight = false;
    } else {
      scarfyVel.Vx = 0; // Stop horizontal movement when no key is pressed
    }

    if (IsKeyDown(KEY_UP)) {
      Vector2 currPos = scarfyPos;

      while (scarfyPos.y != 0) {
        prevTime = currTime;
        currTime = getCurrentTime();

        float dt = currTime - prevTime;
        if (dt > 0.15f)
          dt = 0.15f;

        scarfyPos.y += scarfyVel.Vy * dt;
        scarfyPos.x += scarfyVel.Vx * dt;

        scarfyVel.Vy += gravity.y * dt;
      }

      animateChar(&frameRec, frameDelay, numFrames, &currFrame,
                  &frameDelayCounter);

    } else if (IsKeyDown(KEY_DOWN)) {
      scarfyVel.Vy = 3; // Move down
      animateChar(&frameRec, frameDelay, numFrames, &currFrame,
                  &frameDelayCounter);

    } else {
      scarfyVel.Vy = 0; // Stop vertical movement when no key is pressed
    }

    frameRec.width = isFacingRight ? frameRec.width : -frameRec.width;

    scarfyPos.x += scarfyVel.Vx;
    scarfyPos.y += scarfyVel.Vy;

    if (scarfyPos.x + 128 > 800)
      scarfyPos.x = 800 - 128;
    if (scarfyPos.x < 0)
      scarfyPos.x = 0;
    if (scarfyPos.y < 0)
      scarfyPos.y = 0;
    if (scarfyPos.y > 800 - 128)
      scarfyPos.y = 800 - 128;

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
