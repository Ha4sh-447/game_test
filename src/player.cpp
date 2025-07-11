#include "player.h"
#include "raylib.h"
#include <cstdio>
#include <raymath.h>

int gravity = 1;

Player::Player(Vector2 startPos) {
  health = 100;
  airtime = 70;
  pos = startPos;
  speed.x = playerSpeed;
  speed.y = 0;
  moving = false;
  jumping = false;
}

void AnimatedSprite::LoadSprite(const char *texturePath, int frame) {
  /*
   * Load the sprite into a Sprite object
   */
  Texture2D tex = LoadTexture(texturePath);
  numframes = frame;
  Sprite sp = {100, -(int)(3 * groundYPos) / 4, tex.height,
               tex.width / numframes, tex};
  sprite = sp;
}

bool Player::isPlayerOnGround() {
  // Check if Player is on ground
  if (pos.y + sprite.height == groundYPos) {
    return true;
  }
  return false;
}

void Player::handleControl() {
  // Handle key inputs
  if (isPlayerOnGround()) {
    if (IsKeyDown(KEY_SPACE)) {
      speed.y = -2 * playerSpeed;
    }

    if (IsKeyDown(KEY_RIGHT)) {
      speed.x = 3;
      direction = 1;
    } else if (IsKeyDown(KEY_LEFT)) {
      speed.x = -3;
      direction = 0;
    } else {
      speed.x = 0;
    }
  }

  moving = speed.x != 0.0f || speed.y != 0.0f;
}

void Player::update() {
  // update speed of the player
  bool wasScarfyOnGround = isPlayerOnGround();
  pos = Vector2Add(pos, speed);
  bool scarfyIsOnGround = isPlayerOnGround();
  // Jumping stuff
  if (scarfyIsOnGround) {
    speed.y = 0;
    pos.y = groundYPos - sprite.height;
    if (!wasScarfyOnGround) {
      // play sound
    }
  } else {
    if (IsKeyDown(KEY_SPACE) && airtime > 0) {
      airtime -= 2;
    } else {
      speed.y += gravity;
      // airtime = 85;
    }
  }

  frameRec.width = direction ? frameWidth : -frameWidth;
  Vector2Add(pos, speed);
  draw();
}

void Player::draw() {

  char airTimeText[50];
  sprintf(airTimeText, "Air time left: %d", airtime);
  DrawText(airTimeText, 20, 20, 50, BLACK);

  DrawTextureRec(sprite.tex, frameRec, pos, WHITE);
}
