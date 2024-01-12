#include "Game.hpp"
#include "Entity.hpp"
#include "Vec2/Vec2.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>

Game::Game(const std::string &config_path)
    : m_random_engine(std::random_device{}()) {
  init(config_path);
}

void Game::init(const std::string &config_path) {
  if (!loadConfig(config_path)) {
    throw std::runtime_error(
        std::format("could not load config file, \"{}\".", config_path));
  }

  m_window.create(sf::VideoMode(m_window_config.W, m_window_config.H),
                  "Develop window", sf::Style::Default | m_window_config.FS);
  m_window.setFramerateLimit(m_window_config.FL);

  m_font.loadFromFile(m_font_config.F);
}

auto Game::loadConfig(const std::string &config_path) -> bool {
  std::fstream ifs(config_path);

  if (!ifs.is_open()) {
    return false;
  }

  std::string line;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    std::string type;

    iss >> type;

    if (type == "Window") {
      iss >> m_window_config.W >> m_window_config.H >> m_window_config.FL >>
          m_window_config.FS;
    } else if (type == "Font") {
      iss >> m_font_config.F >> m_font_config.S >> m_font_config.R >>
          m_font_config.G >> m_font_config.B;
    } else if (type == "Player") {
      iss >> m_player_config.SR >> m_player_config.CR >> m_player_config.S >>
          m_player_config.FR >> m_player_config.FG >> m_player_config.FB >>
          m_player_config.OR >> m_player_config.OG >> m_player_config.OB >>
          m_player_config.OT >> m_player_config.V;
    } else if (type == "Enemy") {
      iss >> m_enemy_config.SR >> m_enemy_config.CR >> m_enemy_config.SMIN >>
          m_enemy_config.SMAX >> m_enemy_config.OR >> m_enemy_config.OG >>
          m_enemy_config.OB >> m_enemy_config.OT >> m_enemy_config.VMIN >>
          m_enemy_config.VMAX >> m_enemy_config.L >> m_enemy_config.SI;
    } else if (type == "Bullet") {
      iss >> m_bullet_config.SR >> m_bullet_config.CR >> m_bullet_config.FR >>
          m_bullet_config.FG >> m_bullet_config.FB >> m_bullet_config.OR >>
          m_bullet_config.OG >> m_bullet_config.OB >> m_bullet_config.OT >>
          m_bullet_config.V >> m_bullet_config.L >> m_bullet_config.S;
    }
  }

  return true;
}

void Game::setPaused(bool in_paused) noexcept { m_paused = in_paused; }

void Game::spawnPlayer() {
  auto new_entity = m_entity_manager.addEntity("player");

  auto mx = m_window.getSize().x / 2.0f;
  auto my = m_window.getSize().y / 2.0f;

  new_entity->cTransform = std::make_shared<cmp::Transform>(
      utl::Vec2f(mx, my),
      utl::Vec2f(static_cast<float>(m_player_config.S),
                 static_cast<float>(m_player_config.S)),
      0.0f);
  new_entity->cShape = std::make_shared<cmp::Shape>(
      static_cast<float>(m_player_config.SR), m_player_config.V,
      sf::Color(m_player_config.FR, m_player_config.FG, m_player_config.FB),
      sf::Color(m_player_config.OR, m_player_config.OG, m_player_config.OB),
      static_cast<float>(m_player_config.OT));
  new_entity->cInput = std::make_shared<cmp::Input>();
  new_entity->cCollision = std::make_shared<cmp::Collision>(m_player_config.SR);

  new_entity->cShape->shape.setPosition(new_entity->cTransform->pos.x,
                                        new_entity->cTransform->pos.y);

  m_player = new_entity;
}

void Game::spawnEnemy() {
  std::uniform_int_distribution ud_x(m_enemy_config.SR,
                                     m_window_config.W - m_enemy_config.SR);
  std::uniform_int_distribution ud_y(m_enemy_config.SR,
                                     m_window_config.H - m_enemy_config.SR);
  std::uniform_int_distribution ud_index(0, 1);

  int tmp_arr[]{-1, 1};

  int random_x = ud_x(m_random_engine);
  int random_y = ud_y(m_random_engine);

  int random_index_x = ud_index(m_random_engine);
  int random_index_y = ud_index(m_random_engine);

  auto new_entity = m_entity_manager.addEntity("enemy");

  new_entity->cTransform = std::make_shared<cmp::Transform>(
      utl::Vec2f(random_x, random_y),
      utl::Vec2f(m_enemy_config.SMAX * tmp_arr[random_index_x],
                 m_enemy_config.SMAX * tmp_arr[random_index_y]),
      0.0f);
  new_entity->cShape = std::make_shared<cmp::Shape>(
      static_cast<float>(m_enemy_config.SR), m_enemy_config.VMAX,
      sf::Color(m_player_config.FR, m_player_config.FG, m_player_config.FB),
      sf::Color(m_player_config.OR, m_player_config.OG, m_player_config.OB),
      static_cast<float>(m_player_config.OT));
  new_entity->cCollision = std::make_shared<cmp::Collision>(m_enemy_config.SR);
}

void Game::spawnBullet(const utl::Vec2f &mouse_pos) {
  auto x_diff = mouse_pos.x - m_player->cTransform->pos.x;
  auto y_diff = mouse_pos.y - m_player->cTransform->pos.y;

  auto new_entity = m_entity_manager.addEntity("bullet");

  auto direction_vec = utl::Vec2f(x_diff, y_diff) * 1.5f;
  auto direction_unit_vec = utl::getUnitVec(direction_vec) * 400;

  new_entity->cTransform = std::make_shared<cmp::Transform>(
      utl::Vec2f(m_player->cTransform->pos.x, m_player->cTransform->pos.y),
      utl::Vec2f(direction_unit_vec), 0.0f);

  new_entity->cShape = std::make_shared<cmp::Shape>(m_bullet_config.SR, 16);
  new_entity->cCollision = std::make_shared<cmp::Collision>(m_bullet_config.SR);
}

void Game::sMovement() {

  m_player->cTransform->velocity = {0, 0};

  if (m_player->cInput->up) {
    m_player->cTransform->velocity.y = -m_player_config.S;
  }
  if (m_player->cInput->right) {
    m_player->cTransform->velocity.x = m_player_config.S;
  }
  if (m_player->cInput->down) {
    m_player->cTransform->velocity.y = m_player_config.S;
  }
  if (m_player->cInput->left) {
    m_player->cTransform->velocity.x = -m_player_config.S;
  }

  for (auto &entity : m_entity_manager.getEntities()) {
    entity->cTransform->angle += 1.0f;
    entity->cShape->shape.setRotation(entity->cTransform->angle);

    entity->cTransform->pos.x += entity->cTransform->velocity.x * m_delta_time;
    entity->cTransform->pos.y += entity->cTransform->velocity.y * m_delta_time;
    entity->cShape->shape.setPosition(entity->cTransform->pos.x,
                                      entity->cTransform->pos.y);
  }
}

void Game::sUserInput() {
  sf::Event event;
  while (m_window.pollEvent(event)) {

    if (event.type == sf::Event::Closed) {
      m_running = false;
      m_window.close();
      break;
    }

    if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {

      case sf::Keyboard::Escape:
        std::puts("Esc key Pressed.");
        m_running = false;
        break;

      case sf::Keyboard::P:
        setPaused(!m_paused);
        std::puts(m_paused ? "Game Paused" : "Game resumed");
        break;

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

      default:
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

      default:
        break;
      }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
      if (event.mouseButton.button == sf::Mouse::Left) {
        std::puts("Left Mouse pressed.");
        auto mouse_position =
            utl::Vec2f(event.mouseButton.x, event.mouseButton.y);

        spawnBullet(mouse_position);
      }

      if (event.mouseButton.button == sf::Mouse::Right) {
        std::puts("Right Mouse pressed.");
      }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
      if (event.mouseButton.button == sf::Mouse::Left) {
        std::puts("Left Mouse released.");
      }

      if (event.mouseButton.button == sf::Mouse::Right) {
        std::puts("Right Mouse released.");
      }
    }
  }
}

void Game::sRender() {
  m_window.clear();

  for (const auto &entity : m_entity_manager.getEntities()) {
    m_window.draw(entity->cShape->shape);
  }

  m_window.display();
}

void Game::sEnemySpawner() {
  // if (m_entity_manager.getEntities("enemy").size() < 10) {
  spawnEnemy();
  // }
  m_last_enemy_spawn_time = m_current_frame;
}

void Game::sCollision() {
  for (auto &entity : m_entity_manager.getEntities()) {
    if (entity->cTransform->pos.x <= entity->cCollision->radius ||
        entity->cTransform->pos.x >=
            m_window_config.W - entity->cCollision->radius) {
      entity->cTransform->velocity.x *= -1;
    }

    if (entity->cTransform->pos.y <= entity->cCollision->radius ||
        entity->cTransform->pos.y >=
            m_window_config.H - entity->cCollision->radius) {
      entity->cTransform->velocity.y *= -1;
    }
  }
}

void Game::run() {
  spawnPlayer();

  while (m_running) {
    m_entity_manager.update();

    m_delta_time = m_delta_clock.restart().asSeconds();

    sUserInput();
    if (!m_paused) {

      // if ((m_current_frame - m_last_enemy_spawn_time) == m_enemy_config.SI) {
      if ((m_current_frame - m_last_enemy_spawn_time) == 60) {
        // std::puts("sEnemySpawner()");
        sEnemySpawner();
      }

      sCollision();
      sMovement();

      ++m_current_frame;
    }

    sRender();
  }
}
