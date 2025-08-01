#include "player.h"
#include "config.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

Player::Player(Vector2 startPos) {
  position = startPos;
  velocity = {0, 0};
  airTime = 125;
  jumpUpVelocity = 15.0f;
  airTimeDepletionRate = 2;
  facingRight = true;
  isInAir = false;

  sprite.LoadSprite(CHAR_TEXTURE_PATH, 6, {1, 4, 4, 5});
  jumpSound = LoadSound(JUMP_SOUND_PATH);
}

void Player::HandleControls() {
  if (IsPlayerOnGround()) {
    if (IsKeyDown(KEY_RIGHT)) {
      velocity.x = 3;
      facingRight = true;
    } else if (IsKeyDown(KEY_LEFT)) {
      velocity.x = -3;
      facingRight = false;
    } else {
      velocity.x = 0;
    }

    if (IsKeyPressed(KEY_SPACE)) {
      velocity.y = -10.0f;
      isInAir = true;
      health -= 10;
      StopSound(jumpSound);
      PlaySound(jumpSound);
    }
  } else {
    isInAir = true;
    if (IsKeyDown(KEY_SPACE) && airTime > 0) {
      velocity.y = -(jumpUpVelocity);
      airTime -= airTimeDepletionRate;
    } else {
      velocity.y += gravity;
    }
  }
}

void Player::Update() {
  bool wasOnGround = IsPlayerOnGround();
  position = Vector2Add(position, velocity);
  bool isOnGround = IsPlayerOnGround();

  if (isOnGround) {
    velocity.y = 0;
    position.y = groundYPos - sprite.frameHeight;
    isInAir = false;

    if (airTime < 125)
      airTime++;
  } else {
    isInAir = true;
    velocity.y += gravity;
  }

  sprite.frameRec.width = facingRight ? sprite.frameWidth : -sprite.frameWidth;
  bool isMoving = velocity.x != 0 || !isOnGround;
  sprite.AnimateFrame(velocity, isMoving, isOnGround);

  KeepWithinBounds();
}

void Player::Draw() {
  char airTimeText[50];
  char playerHealth[50];
  snprintf(airTimeText, sizeof(airTimeText), "Air Time: %d", airTime);
  snprintf(playerHealth, sizeof(playerHealth), "Health: %d", health);
  DrawText(airTimeText, 20, 20, 40, BLACK);
  DrawText(playerHealth, 20, 70, 40, BLACK);
  DrawTextureRec(sprite.tex, sprite.frameRec, position, WHITE);
}

void Player::KeepWithinBounds() {
  if (position.x < 0)
    position.x = 0;
  if (position.x + sprite.frameWidth > screenWidth)
    position.x = screenWidth - sprite.frameWidth;
  if (isInAir && position.y < 0)
    position.y = 10;
}

bool Player::IsPlayerOnGround() {
  return position.y + sprite.frameHeight >= groundYPos;
}

void Player::Unload() {
  sprite.Unload();
  UnloadSound(jumpSound);
}
