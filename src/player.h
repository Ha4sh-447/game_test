#pragma once

#include "animation.h"
#include <raylib.h>

class Player {
public:
  Vector2 position;
  Vector2 velocity;
  AnimatedSprite sprite;
  int airTime;
  int facingRight = true;
  int isInAir = false;

  Sound footStepSound;
  Sound jumpSound;

  Player(Vector2 startPos);

  void HandleControls();
  void Update();
  void Draw();
  void Unload();
  void KeepWithinBounds();
  bool IsPlayerOnGround();
};
