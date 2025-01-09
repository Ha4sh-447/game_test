#include "player.h"
#include "raylib.h"
#include <cstdio>
#include <raymath.h>

Player::Player(Vector2 startPos) {
  health = 100;
  airtime = 70;
  pos = startPos;
  speed.x = playerSpeed;
  speed.y = 0;
  moving = false;
  jumping = false;
}

void AnimatedSprite::loadSprite(char *sheet) {
  /*
   * Load the sprite into a Sprite object
   */
  Texture2D tex = LoadTexture(sheet);
  numframes = 6;
  Sprite sp = {100, -(int)(3 * groundYPos) / 4, tex.height,
               tex.width / numframes, tex};
  sprite = sp;
}

bool Player::isPlayerOnGround() {
  if (pos.y + sprite.height == groundYPos) {
    return true;
  }
  return false;
}

void Player::handleControl() {
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
  char airTimeText[50];
  bool wasScarfyOnGround = isPlayerOnGround();
  pos = Vector2Add(pos, speed);
  bool scarfyIsOnGround = isPlayerOnGround();
  sprintf(airTimeText, "Air time left: %d", airtime);
  DrawText(airTimeText, 20, 20, 50, BLACK);
}
