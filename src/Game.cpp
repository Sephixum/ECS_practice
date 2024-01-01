#include "Game.hpp"

#include <fstream>
#include <iostream>

Game::Game(const std::string &config) { init(config); }

void Game::init(const std::string &config) noexcept {
  m_config.parseConfig(config);

  m_window.create(
      sf::VideoMode(m_config.window_config.W, m_config.window_config.H),
      "ECS_Practice", m_config.window_config.FS | sf::Style::Default);
  m_window.setFramerateLimit(m_config.window_config.FL);

  m_font.loadFromFile(m_config.font_config.F);
}

void Game::setPaused(bool in_paused) noexcept { m_paused = in_paused; }

void Game::sMovement() {
  // TODO: implement all entity movement in this function
  // NOTE: reading the m_player component to determine if it should be moving

  m_player->cTransform->velocity = {0, 0};

  if (m_player->cInput->up) {
    m_player->cTransform->velocity.y = -5;
  }

  if (m_player->cInput->right) {
    m_player->cTransform->velocity.x = 5;
  }

  if (m_player->cInput->down) {
    m_player->cTransform->velocity.y = 5;
  }

  if (m_player->cInput->left) {
    m_player->cTransform->velocity.x = -5;
  }

  m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
  m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
}

void Game::sUserInput() {
  sf::Event event;
  while (m_window.pollEvent(event)) {

    if (event.type == sf::Event::Closed) {
      m_running = false;
      break;
    }

    if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
      case sf::Keyboard::W:
        std::puts("W key Pressed.");
        m_player->cInput->up = true;
        break;

      case sf::Keyboard::S:
        std::puts("S key Pressed.");
        m_player->cInput->down = true;
        break;

      case sf::Keyboard::D:
        std::puts("D key Pressed.");
        m_player->cInput->right = true;
        break;

      case sf::Keyboard::A:
        std::puts("A key Pressed.");
        m_player->cInput->left = true;
        break;
      }
    }

    if (event.type == sf::Event::KeyReleased) {
      switch (event.key.code) {
      case sf::Keyboard::W:
        std::puts("W key Released.");
        m_player->cInput->up = false;
        break;

      case sf::Keyboard::S:
        std::puts("S key Released.");
        m_player->cInput->down = false;
        break;

      case sf::Keyboard::D:
        std::puts("D key Released.");
        m_player->cInput->right = false;
        break;

      case sf::Keyboard::A:
        std::puts("A key Released.");
        m_player->cInput->left = false;
        break;
      }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
      switch (event.key.code) {
      case sf::Mouse::Left:
        std::puts("Left Mouse pressed.");
        break;
      }
    }

    if (event.type == sf::Event::MouseButtonReleased) {

      switch (event.key.code) {
      case sf::Mouse::Left:
        std::puts("Left Mouse Released.");
        break;
      }
    }
  }
}

void Game::sLifespan() {}

void Game::sRender() {
  m_window.clear(sf::Color::Black);

  m_player->cTransform->angle += 1.0f;
  m_player->cShape->shape.setRotation(m_player->cTransform->angle);
  m_player->cShape->shape.setPosition(m_player->cTransform->pos.x,
                                      m_player->cTransform->pos.y);

  for (auto entity : m_entities.getEntities()) {
    m_window.draw(entity->cShape->shape);
  }

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

void Game::spawnEnemy() {
  auto entity = m_entities.addEntity("enemy");

  auto mx = m_window.getSize().x / 3.0f;
  auto my = m_window.getSize().y / 3.0f;

  entity->cTransform = std::make_shared<CTransform>(
      Util::Vec2f(mx, my), Util::Vec2f(5.0f, 5.0f), 10.0f);

  entity->cShape = std::make_shared<CShape>(40.0f, 8);

  m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawSmallEnemies(std::shared_ptr<Engine::Entity> entity) {
  // TODO spawn small enemies at the location of the input enemy e

  // when we create the smaller enemy, we have to read the valued of the
  // original enemy
  // - spawn a number of small enemies equal to the vertices of the original
  // enemy
  // - set each small enemy to the same color as the original, half the
  // size(alpha)
  // - small enemies are worth double points of the original enemy
}

void Game::spawnBullet(std::shared_ptr<Engine::Entity> entity,
                       const Util::Vec2f &mousePos) {
  std::cout << mousePos.x;
}

void Game::spawnSpecialWeapon(std::shared_ptr<Engine::Entity> entity) {}

void Game::run() {
  spawnPlayer();

  while (m_running) {
    m_entities.update();

    if (!m_paused) {
      if (m_currentFrame - m_lastEnemySpawnTime == 60) {
        std::puts("sEnemySpawner()");
        m_lastEnemySpawnTime = m_currentFrame;
        // sEnemySpawner();
      }

      sMovement();
      // sCollision();
      sUserInput();
    }

    sRender();

    m_currentFrame++;
  }
}
