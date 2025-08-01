#include "weapons.h"
#include <cstdio>
#include <raylib.h>

Weapon::Weapon() {
  position = {0, 0};
  origin = {0.0};
  rotation = 0.0f;
  length = 50.0f;
  facingRight = true;
  texture = {0};
  sourceRec = {0, 0};
}

void Weapon::LoadWeapon(const char *tex) {
  texture = LoadTexture(tex);
  if (texture.id == 0) {
    printf("Failed to load weapon texture: %s\n", tex);
    length = 50.0f;
  } else {
    int row = 5;
    int spriteWidth = 32;
    int spriteHeight = 16;
    int col = 1;
    float scale = 4.0f;

    Rectangle source = {static_cast<float>(col * spriteWidth),
                        static_cast<float>(row * spriteHeight),
                        static_cast<float>(spriteWidth),
                        static_cast<float>(spriteHeight)};

    sourceRec = source;
    length = (float)texture.width;
    origin = {5.0f, (float)texture.height / 2.0f};
  }
}

void Weapon::Update(Vector2 playerPos, Vector2 mousePos,
                    bool playerFacingRight) {
  facingRight = playerFacingRight;

  position.x = playerPos.x + (facingRight ? 20.0f : -20.0f);
  position.y = playerPos.y + 30.0f;

  rotation = AngleToMouse(position, mousePos, facingRight);
}

void Weapon::Draw() {}
