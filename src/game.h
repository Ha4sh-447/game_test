// game.h
#pragma once
#include "player.h"

class Game {
  int airDepletionRate = 1;

public:
  void DrawUI(Player &player);
  void Run(Player &player);
};
