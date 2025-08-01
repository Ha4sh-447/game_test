#ifndef WEAPON_H
#define WEAPON_H

#include <raylib.h>
#include <vector>
enum WeaponType { Pistol, AR, Sword };

class Weapon {
public:
  Vector2 position;
  Vector2 origin;
  float rotation;
  float length;
  Texture2D texture;
  Rectangle sourceRec;
  bool facingRight;
  WeaponType currentWeapon;

  Weapon();

  void LoadWeapon(const char *texturePath);
  void Update(Vector2 playerPos, Vector2 mousePos, bool playerFacingRight);
  void Draw();
  void Unload();

  Vector2 GetTipPosition();
  Vector2 GetDirection();

private:
  float AngleToMouse(Vector2 playerPos, Vector2 mousePos,
                     bool playerFacingRight);
  std::vector<Rectangle> weaponRects;
  void InitWeaponRects();
};
#endif
