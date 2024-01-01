#pragma once

#include "ConfigParser.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Vec2/Vec2.hpp"

#include <SFML/Graphics.hpp>

class Game {
private:
  sf::RenderWindow m_window;
  Engine::EntityManager m_entities;
  sf::Font m_font;
  sf::Text m_text;
  GameConfig m_config;
  int m_score;
  int m_currentFrame = 0;
  int m_lastEnemySpawnTime = 0;
  bool m_paused = false;
  bool m_running = true;

  std::shared_ptr<Engine::Entity> m_player;

  void init(const std::string &config) noexcept; // initialize the GameState
                                                 // with a config file path

  void setPaused(bool in_paused) noexcept; // pause the game

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