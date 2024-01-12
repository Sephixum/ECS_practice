#include "Game.hpp"

auto main() -> int {
  Game g("resources/config/Config.txt");
  g.run();

  return EXIT_SUCCESS;
}
