#pragma once

#include "EntityManager.hpp"

#include <SFML/Graphics.hpp>
#include <random>
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

class Game {
private:
  std::mt19937_64 m_random_engine;
  eng::EntityManager m_entity_manager;

  sf::RenderWindow m_window;
  sf::Clock m_delta_clock;
  sf::Font m_font;
  sf::Text m_text;

  WindowConfig m_window_config;
  FontConfig m_font_config;
  PlayerConfig m_player_config;
  EnemyConfig m_enemy_config;
  BulletConfig m_bullet_config;

  int m_score;
  int m_current_frame = 0;
  int m_last_enemy_spawn_time = 0;

  bool m_paused = false;
  bool m_running = true;

  float m_delta_time;

  std::shared_ptr<eng::Entity> m_player;

  void
  init(const std::string &config); // init the game state with config file DONE*
  auto loadConfig(const std::string &in_path) -> bool; // DONE*
  void setPaused(bool in_paused) noexcept;             // pause the game DONE*
  void spawnPlayer();                                  // DONE*
  void spawnEnemy();                                   // DONE*
  void spawSmallEnemies(std::shared_ptr<eng::Entity> entity);
  void spawnBullet(const utl::Vec2f &mouse_pos); //
  void spawnSpecialWeapon(std::shared_ptr<eng::Entity> entity);

  void sMovement();     // System: Entity position / movement update
  void sUserInput();    // System: User input
  void sLifespan();     // System: Lifespan
  void sRender();       // System: Render / Drawing DONE*
  void sEnemySpawner(); // System: Spawns Enemies
  void sCollision();    // System: Collision

public:
  Game(const std::string &config);

  void run(); // IS BEING DONE
};
