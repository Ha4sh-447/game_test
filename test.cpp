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
const int footstepFrame2 = 4; // Frame showing footsteps

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

// Updated updateAirTime: Gradually regenerate airTime when on ground
void updateAirTime(int *airTime, bool isOnGround) {
  const int maxAirTime = 85;
  const float regenRate = 1; // Air time regained per frame (adjust as needed)

  if (isOnGround && *airTime < maxAirTime) {
    *airTime += regenRate;
    if (*airTime > maxAirTime) {
      *airTime = maxAirTime; // Cap at maximum
    }
  }
}

int main(void) {
  Vector2 scarfyVel = {0.0f, 0.0f};
  bool isInAir = false;
  InitWindow(screenWidth, screenHeight, "PLAYYAYYA");
  SetTargetFPS(60);

  InitAudioDevice();

  Texture2D scarfy = LoadTexture("./resources/scarfy.png");

  const char *footstepFilename =
      "./resources/audio/"
      "Single-footstep-in-grass-A-www.fesliyanstudios.com.mp3";
  Sound footstepSound = LoadSound(footstepFilename);
  // Add jump sound
  const char *jumpFilename =
      "./resources/audio/jump.wav"; // Ensure you have a jump sound file
  Sound jumpSound = LoadSound(jumpFilename);
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

  Rectangle frameRec = {0.0f, 0.0f, (float)frameWidth, (float)frameHeight};
  Vector2 scarfyPos = {screenWidth / 2.0f, (float)groundYPos - scarfy.height};

  bool isFacingRight = true;

  // Jump constants
  const float jumpVelocity = -15.0f;    // Upward velocity for jump
  const int maxAirTime = 85;            // Maximum air time for sustained jump
  const float airTimeDepletionRate = 2; // Air time consumed per frame

  while (!WindowShouldClose()) {
    // Horizontal movement
    scarfyVel.x = 0;
    if (IsKeyDown(KEY_RIGHT)) {
      scarfyVel.x = 3;
      isFacingRight = true;
    } else if (IsKeyDown(KEY_LEFT)) {
      scarfyVel.x = -3;
      isFacingRight = false;
    }

    bool scarfyMoving = scarfyVel.x != 0.0f || scarfyVel.y != 0.0f;

    bool wasScarfyOnGround = isScarfyOnGround(&scarfy, &scarfyPos);
    scarfyPos = Vector2Add(scarfyPos, scarfyVel);
    bool scarfyIsOnGround = isScarfyOnGround(&scarfy, &scarfyPos);

    // Update air time display
    sprintf(airTimeText, "Air time left: %d", airTime);

    if (scarfyIsOnGround) {
      scarfyVel.y = 0;
      scarfyPos.y = groundYPos - scarfy.height; // Snap to ground
      isInAir = false;

      // Regenerate air time gradually
      updateAirTime(&airTime, true);

      if (!wasScarfyOnGround) {
        // Play landing sound
        PlaySound(footstepSound);
      }

      // Initiate jump on SPACE press
      if (IsKeyPressed(KEY_SPACE)) {
        scarfyVel.y = jumpVelocity;
        isInAir = true;
        PlaySound(jumpSound);
      }
    } else {
      isInAir = true;

      // Sustain jump if SPACE is held and airTime remains
      if (IsKeyDown(KEY_SPACE) && airTime > 0) {
        scarfyVel.y = jumpVelocity; // Maintain upward velocity
        airTime -= airTimeDepletionRate;
      } else {
        scarfyVel.y += gravity; // Apply gravity
      }

      // No air time regeneration in air
      updateAirTime(&airTime, false);
    }

    // Update sprite facing direction
    frameRec.width = isFacingRight ? (float)frameWidth : -(float)frameWidth;

    animateChar(&frameRec, &scarfyVel, frameDelay, numFrames, &currFrame,
                &frameDelayCounter, scarfyMoving, scarfyIsOnGround,
                footstepSound);
    keepWithinBounds(&scarfyPos, &scarfy, isInAir);

    // Draw on screen
    BeginDrawing();
    ClearBackground(GREEN);
    DrawTextureRec(scarfy, frameRec, scarfyPos, WHITE);
    DrawText(airTimeText, 20, 20, 50, BLACK);
    EndDrawing();
  }

  UnloadTexture(scarfy);
  UnloadSound(footstepSound);
  UnloadSound(jumpSound);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
