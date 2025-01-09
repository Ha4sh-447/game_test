#include <cstdio>
#include <cstdlib>
#include <raylib.h>
#include <raymath.h>

const int gravity = 1;

const int screenWidth = 1600;
const int screenHeight = 900;

const int numFrames = 6;

const int scarfySpeed = 10;
const int groundYPos = (3 * screenHeight) / 4; // Define ground position

const int jumpUpFrame = 3;
const int jumpDownFrame = 4;
const int footstepFrame1 = 1; // Frame showing footsteps
const int footstepFrame2 = 4; // Frame showing footstepsj

int airTime = 85;

bool isFootstepFrame(int frameIndex) {
  if (frameIndex == footstepFrame1 || frameIndex == footstepFrame2) {
    return true;
  }
  return false;
}

bool isScarfyOnGround(Texture2D *scarfy, Vector2 *pos) {
  if (pos->y + scarfy->height >= groundYPos) {
    return true;
  }
  return false;
}

void animateChar(Rectangle *frameRec, Vector2 *scarfyVel, int frameDelay,
                 int numFrame, int *currFrame, int *frameDelayCounter,
                 bool scarfyMoving, bool scarfyIsOnGround, Sound sound) {

  float frameWidth = frameRec->width;
  ++(*frameDelayCounter);
  if ((*frameDelayCounter) > frameDelay) {
    *frameDelayCounter = 0;
    if (scarfyMoving) {
      if (scarfyIsOnGround) {
        ++(*currFrame);
        *currFrame %= numFrame;
        if (isFootstepFrame(*currFrame)) {
          // play footstep sound
          PlaySound(sound);
        }
      } else {
        if (scarfyVel->y < 0) {
          *currFrame = jumpUpFrame;
        } else {
          *currFrame = jumpDownFrame;
        }
      }
      frameRec->x = (float)frameWidth * (*currFrame);
    }
  }
}

void keepWithinBounds(Vector2 *pos, Texture2D *tex, bool isInAir) {
  if (pos->x < 0) {
    pos->x = 0;
  }
  if (pos->x + (int)(tex->width / numFrames) > screenWidth) {
    pos->x = screenWidth - (int)(tex->width / numFrames);
  }

  if (isInAir && pos->y < 0) {
    pos->y = 10;
  }
}

void displayText(char *text) {
  BeginDrawing();
  DrawText(text, 20, 20, 20, BLACK);
  EndDrawing();
};

int main(void) {

  Vector2 scarfyVel = {0.0f, 0.0f};
  bool isInAir = false;
  InitWindow(screenWidth, screenHeight, "PLAYYAYYA");
  SetTargetFPS(60);

  InitAudioDevice();

  Texture2D scarfy = LoadTexture("./resources/scarfy.png");

  const char *filename =
      "./resources/audio/"
      "Single-footstep-in-grass-A-www.fesliyanstudios.com.mp3";
  Sound footstepSound = LoadSound(filename);
  char airTimeText[50];

  if (scarfy.id == 0) {
    TraceLog(LOG_ERROR, "Failed to load texture scarfy.png");
    CloseWindow();
    return -1;
  }

  unsigned frameCount = 6;
  int frameWidth = scarfy.width / numFrames;
  int frameHeight = scarfy.height;

  int currFrame = 0;         // Current frame index
  int frameDelay = 5;        // After 5 iterations change the frame
  int frameDelayCounter = 0; // A counter to check if 5 iterations have passed
                             // so that frame can be updated

  Rectangle frameRec = {0.0f, 0.0f, (float)frameWidth, (float)frameHeight};
  Vector2 scarfyPos = {screenWidth / 2.0f, (float)groundYPos - scarfy.height};

  bool isFacingRight = true;
  while (!WindowShouldClose()) {
    // Horizontal movement of scarfy
    if (isScarfyOnGround(&scarfy, &scarfyPos)) {
      if (IsKeyDown(KEY_SPACE)) {
        scarfyVel.y = -2 * scarfySpeed;
      }

      if (IsKeyDown(KEY_RIGHT)) {
        scarfyVel.x = 3;
        isFacingRight = true;
      } else if (IsKeyDown(KEY_LEFT)) {
        scarfyVel.x = -3;
        isFacingRight = false;
      } else {
        scarfyVel.x = 0;
      }
    }

    bool scarfyMoving = scarfyVel.x != 0.0f || scarfyVel.y != 0.0f;

    bool wasScarfyOnGround = isScarfyOnGround(&scarfy, &scarfyPos);
    scarfyPos = Vector2Add(scarfyPos, scarfyVel);
    bool scarfyIsOnGround = isScarfyOnGround(&scarfy, &scarfyPos);
    sprintf(airTimeText, "Air time left: %d", airTime);
    DrawText(airTimeText, 20, 20, 50, BLACK);

    if (scarfyIsOnGround) {
      scarfyVel.y = 0;
      scarfyPos.y = groundYPos - scarfy.height;
      if (!wasScarfyOnGround) {
        // play landing sound
        PlaySound(footstepSound);
      }
    } else {
      // TODO: Play sound when in air
      if (IsKeyDown(KEY_SPACE) && airTime > 0) {
        airTime -= 2;
        isInAir = true;
      } else {
        scarfyVel.y += gravity;
        airTime = 85;
      }
    }

    frameRec.width = isFacingRight ? (float)frameWidth : -(float)frameWidth;

    animateChar(&frameRec, &scarfyVel, frameDelay, numFrames, &currFrame,
                &frameDelayCounter, scarfyMoving, scarfyIsOnGround,
                footstepSound);
    keepWithinBounds(&scarfyPos, &scarfy, isInAir);
    // Draw on screen
    BeginDrawing();
    ClearBackground(GREEN);

    DrawTextureRec(scarfy, frameRec, scarfyPos, WHITE);
    EndDrawing();
  }

  UnloadTexture(scarfy);
  CloseWindow();
  return 0;
}
