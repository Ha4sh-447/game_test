#pragma once

#include <raylib.h>

extern const int screenWidth;
extern const int screenHeight;
extern const int playerSpeed;
extern const float groundYPos;
extern const int gravity;

typedef struct Sprite {
  Vector2 position;
  Texture2D tex;
} Sprite;

class AnimatedSprite {
public:
  float frameWidth = 0.0f;
  float frameHeight = 0.0f;
  int numFrames = 0;
  int currFrame = 0;
  float timer = 0;
  int frameIndex = 0;
  int frameDelay = 0;
  int frameDelayCounter = 0;
  Rectangle frameRec = {0};
  int footstepFrame1 = 0;
  int footstepFrame2 = 0;
  Sprite sprite;

  void LoadSprite(const char *texturePath, int frame);
  void AnimateFrame(Vector2 velocity, bool moving, bool onGround,
                    Sound footstepSound);
  bool isFootstepFrame();
};

class Player {
  AnimatedSprite sprite;
  Vector2 position;
  Vector2 velocity;
  int airTime = 85;
  int facingRight = true;
  int isInAir = false;

public:
  Sound footStepSound;
  Sound jumpSound;

  Player(Vector2 startPos);

  void HandleControls();
  void KeepWithinBounds();
  bool IsPlayerOnGround();
  void Update();
  void Draw();
};
