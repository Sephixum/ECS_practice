#pragma once

#include <string>

struct WindowConfig {
  int W;
  int H;
  int FL;
  int FS;
};

struct FontConfig {
  std::string F;
  int S;
  int R, G, B;
};

struct PlayerConfig {
  int SR;
  int CR;
  int FR;
  int FG;
  int FB;
  int OR;
  int OG;
  int OB;
  int OT;
  int V;
  float S;
};

struct EnemyConfig {
  int SR;
  int CR;
  int OR;
  int OG;
  int OB;
  int OT;
  int VMIN;
  int VMAX;
  int L;
  int SI;
  float SMIN;
  float SMAX;
};

struct BulletConfig {
  int SR;
  int CR;
  int FR;
  int FG;
  int FB;
  int OR;
  int OG;
  int OB;
  int OT;
  int V;
  int L;
  float S;
};

struct GameConfig {
public:
  WindowConfig window_config;
  FontConfig font_config;
  PlayerConfig player_config;
  EnemyConfig enemy_config;
  BulletConfig bullet_config;
  auto parseConfig(const std::string &filePath) noexcept -> bool;
};
