#pragma once

#include "Entity.hpp"
#include "EntityManager.hpp"

#include <SFML/Graphics.hpp>

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
  sf::RenderWindow m_window;
  Engine::EntityManager m_entities;
  sf::Font m_font;
  sf::Text m_text;
  PlayerConfig m_playerConfig;
  EnemyConfig m_enemyConfig;
  BulletConfig m_bulletConfig;
  int m_score;
  int m_currentFrame = 0;
  bool m_paused = false;
  bool m_running = true;

  std::shared_ptr<Engine::Entity> m_player;

  void init(const std::string
                &config); // initialize the GameState with a config file path
  void setPaused(bool in_paused); // pause the game

  void sMovement();     // System: Entity position / movement update
  void sUserInput();    // System: User input
  void sLifespan();     // System: Lifespan
  void sRender();       // System: Render / Drawing
  void sEnemySpawner(); // System: Spawns Enemies
  void sCollision();    // System: Collision

  void spawnPlayer();
  void spawnEnemy();
  void spawSmallEnemies(std::shared_ptr<Engine::Entity> entity);
  void spawnBullet(std::shared_ptr<Engine::Entity> entity,
                   const Util::Vec2f &mousePos);
  void spawnSpecialWeapon(std::shared_ptr<Engine::Entity> entity);

public:
  Game(const std::string &config);

  void run();
};