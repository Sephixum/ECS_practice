#include "Game.hpp"

#include <fstream>
#include <iostream>

Game::Game(const std::string &config) { init(config); }

void Game::init(const std::string &config) noexcept {
  m_config.parseConfig(config);

  m_window.create(
      sf::VideoMode(m_config.window_config.W, m_config.window_config.H),
      "ECS_Practice", m_config.window_config.FS);
  m_window.setFramerateLimit(m_config.window_config.FL);
}

void Game::setPaused(bool in_paused) noexcept { m_paused = in_paused; }

void Game::sMovement() {}

void Game::sUserInput() {
  sf::Event event;
  while (m_window.pollEvent(event)) {
    switch (event.type) {

    case sf::Event::Closed:
      m_running = false;
      m_window.close();
      break;

    case sf::Event::KeyPressed:
      switch (event.key.code) {

      case sf::Keyboard::W:
        std::puts("W key Pressed.");
        break;

      case sf::Keyboard::S:
        std::puts("S key Pressed.");
        break;
      }
      break;

    case sf::Event::KeyReleased:

      switch (event.key.code) {
      case sf::Keyboard::W:
        std::puts("W key Relased.");
        break;

      case sf::Keyboard::S:
        std::puts("S key Released.");
        break;
      }
    }
  }
}

void Game::sLifespan() {}

void Game::sRender() {
  m_window.clear(sf::Color::Blue);

  m_player->cTransform->angle += 1.0f;
  m_player->cShape->shape.setRotation(m_player->cTransform->angle);

  // m_window.draw(m_player->cShape->shape);

  // for (auto entity : m_entities.getEntities()) {
  //   m_window.draw(entity->cShape->shape);
  // }

  m_window.display();
}

void Game::sEnemySpawner() {}

void Game::sCollision() {}

void Game::spawnPlayer() {
  auto entity = m_entities.addEntity("player");

  auto mx = m_window.getSize().x / 2.0f;
  auto my = m_window.getSize().y / 2.0f;

  entity->cTransform = std::make_shared<CTransform>(
      Util::Vec2f(mx, my), Util::Vec2f(1.0f, 1.0f), 0.0f);

  entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10),
                                            sf::Color(255, 0, 0), 4.0f);

  entity->cInput = std::make_shared<CInput>();

  m_player = entity;
}

void Game::spawnEnemy() {}

void Game::spawSmallEnemies(std::shared_ptr<Engine::Entity> entity) {}

// void Game::spawnBullet(std::shared_ptr<Engine::Entity> entity,
//                        const Util::Vec2f &mousePos) {}

void Game::spawnSpecialWeapon(std::shared_ptr<Engine::Entity> entity) {}

void Game::run() {
  while (m_running) {
    m_entities.update();

    if (!m_paused) {
      // sEnemySpawner();
      // sMovement();
      // sCollision();
      sUserInput();
    }

    sRender();

    m_currentFrame++;
  }
}
