#include "Game.hpp"

auto main() -> int {
  Game g("resources/config/Config.txt");
  g.run();
  return 0;
}