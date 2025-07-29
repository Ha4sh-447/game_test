#ifndef CONFIG_H
#define CONFIG_H

// Screen dimensions
const int screenWidth = 1600;
const int screenHeight = 900;

const int playerSpeed = 10;
const float groundYPos = (3 * screenHeight) / 4;
const int gravity = 1;

// Asset Paths
extern const char *CHAR_TEXTURE_PATH;
extern const char *JUMP_SOUND_PATH;
extern const char *FOOTSTEP_SOUND_PATH;
#endif
