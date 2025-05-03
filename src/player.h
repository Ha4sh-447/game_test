#include <raylib.h>

typedef struct Sprite {
  int x;
  int y;
  int height;
  int width;
  Texture2D tex;
} Sprite;

extern int screenWidth;
extern int screenHeight;
extern int playerSpeed;
extern float groundYPos;
extern int gravity;

class AnimatedSprite {
public:
  float frameWidth = 0.0f;
  float frameHeight = 0.0f;
  int numframes = 0;
  float timer = 0;
  int frameIndex = 0;
  int frameDelay = 0;
  int frameDelayCounter = 0;
  Rectangle frameRec = {0};
  int footstepFrame1 = 0;
  int footstepFrame2 = 0;
  Sprite sprite;

  void loadSprite(char *sheet);
  void animateFrame();
  bool isFootstepFrame();
};

class Player : AnimatedSprite {
  int health;
  int airtime;
  int direction;
  Vector2 speed = {0};
  Vector2 pos = {0};
  bool moving;
  bool jumping;

public:
  Player(Vector2 startPos);
  void handleControl();
  void keepWithinBounds();
  bool isPlayerOnGround();
  void update();
  void draw();
};

class Game {
public:
  void draw();
  void update(Player *player);
};
