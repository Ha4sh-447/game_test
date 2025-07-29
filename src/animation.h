#pragma once
#include "raylib.h"

class FrameInfo {
public:
  int footstepFrame1;
  int footstepFrame2;
  int jumpUpFrame;
  int jumpDownFrame;
};

class AnimatedSprite {
public:
  Texture2D tex;
  int numFrames = 0;
  int currFrame = 0;
  int frameIndex = 0;
  int frameDelay = 0;
  int frameDelayCounter = 0;
  Rectangle frameRec = {0};
  int footstepFrame1 = 0;
  int footstepFrame2 = 0;
  int jumpUpFrame;
  int jumpDownFrame;
  Vector2 position;
  Sound footstepSound;
  float frameHeight;
  float frameWidth;

  void LoadSprite(const char *texturePath, int frameCount,
                  const FrameInfo frameinfo);
  void AnimateFrame(Vector2 velocity, bool moving, bool onGround);
  bool isFootstepFrame();
  void Unload();
};
