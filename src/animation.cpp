#include "animation.h"
#include "config.h"
#include <raylib.h>

void AnimatedSprite::LoadSprite(const char *texturePath, int frameCount,
                                const FrameInfo frameinfo) {
  Texture2D tex = LoadTexture(texturePath);
  numFrames = frameCount;
  frameHeight = (float)tex.height;
  frameWidth = (float)tex.width / numFrames;
  frameRec = {0.0f, 0.0f, frameWidth, frameHeight};
  footstepFrame1 = frameinfo.footstepFrame1;
  footstepFrame2 = frameinfo.footstepFrame2;
  jumpUpFrame = frameinfo.jumpUpFrame;
  jumpDownFrame = frameinfo.jumpDownFrame;
  frameDelay = 5;
  footstepSound = LoadSound(FOOTSTEP_SOUND_PATH);
}

void AnimatedSprite::AnimateFrame(Vector2 vector, bool moving, bool onGround) {
  ++frameDelayCounter;
  if (frameDelayCounter > frameDelay) {
    frameDelayCounter = 0;
    if (moving) {
      if (onGround) {
        ++currFrame;
        currFrame %= numFrames;
        if (isFootstepFrame()) {
          PlaySound(footstepSound);
        }
      } else {
        if (position.y < 0) {
          currFrame = jumpUpFrame;
        } else {
          currFrame = jumpDownFrame;
        }
      }
      frameRec.x = (float)frameWidth * currFrame;
    }
  }
}

bool AnimatedSprite::isFootstepFrame() {
  return (currFrame == footstepFrame1 || currFrame == footstepFrame2);
}

void AnimatedSprite::Unload() {
  UnloadTexture(tex);
  UnloadSound(footstepSound);
}
