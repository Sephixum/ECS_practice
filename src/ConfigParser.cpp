#include "ConfigParser.hpp"

#include <exception>
#include <format>
#include <fstream>
#include <sstream>

auto GameConfig::parseConfig(const std::string &file_path) noexcept -> bool {
  std::ifstream config_file(file_path);

  if (!config_file.is_open()) {
    return false;
  }

  std::string line;
  while (std::getline(config_file, line)) {
    std::istringstream iss(line);
    std::string type;
    iss >> type;

    if (type == "Window") {
      iss >> window_config.W >> window_config.H >> window_config.FL >>
          window_config.FS;
    } else if (type == "Font") {
      iss >> font_config.F >> font_config.S >> font_config.R >> font_config.G >>
          font_config.B;
    } else if (type == "Player") {
      iss >> player_config.SR >> player_config.CR >> player_config.S >>
          player_config.FR >> player_config.FG >> player_config.FB >>
          player_config.OR >> player_config.OG >> player_config.OB >>
          player_config.OT >> player_config.V;
    } else if (type == "Enemy") {
      iss >> enemy_config.SR >> enemy_config.CR >> enemy_config.SMIN >>
          enemy_config.SMAX >> enemy_config.OR >> enemy_config.OG >>
          enemy_config.OB >> enemy_config.OT >> enemy_config.VMIN >>
          enemy_config.VMAX >> enemy_config.L >> enemy_config.SI;
    } else if (type == "Bullet") {
      iss >> bullet_config.SR >> bullet_config.CR >> bullet_config.FR >>
          bullet_config.FG >> bullet_config.FB >> bullet_config.OR >>
          bullet_config.OG >> bullet_config.OB >> bullet_config.OT >>
          bullet_config.V >> bullet_config.L >> bullet_config.S;
    }
  }

  return true;
}