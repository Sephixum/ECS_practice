we have
1. Window
2. Font
3. Player
4. Enemy
5. Bullet

=========================================

# Window
W : width(int)
H : height(int)
FL: frame limit(int)
FS: full screen(int)

=========================================

# Font
F : font file(std::string)
S : font size(int)
R, G, B : red(int) green(int) blue(int)

=========================================

# Player
SR: shape radius(int)
CR: collision radius(int)
S : speed(float)
FR, FG, FB: fill color RGB(int, int, int)
OR, OG, OB: outline color RGB(int, int, int)
OT: outline thickness(int)
V : shape vertices(int)

=========================================

# Enemy
SR: shape radius(int)
CR: collision radius(int)
SMIN, SMAX: min / max speed(float, float)
OR, OG, OB: outline color RGB(int, int, int)
OT: outline thickness(int)
VMIN, VMAX: min / max vertices(int, int)
L : small lifespan(int)
SP: spawn interval

=========================================

# Bullet
SR: shape radius(int)
CR: collision radius(int)
S : speed(float)
FR, FG, FB: fill color RGB(int, int, int)
OR, OG, OB: out line color RGB(int, int, int)
OT: outline thickness(int)
V : shape vertices(int)
L : life span(int)

=========================================

# Recommended Approach :

1. Implement Vec2 class DONE
2. Implement Basic functioanlity in EntityManager
   addEntity(), update(), DONE
3. Implement basics of Game class:
    a. Construct a Player Entity Using spawnPlayer() DONE
    b. Implement basic drawing of entities using Game::sRender() DONE
    c. Construct some enemies using the spawnEnemy() DONE
    d. Construct a bullet using the spawnBullet() DONE
4. Implement Player Movement in Gmae::sUserInput and Game::sMovement DONE
5. Implement the EntityManager::update() function so it deletes dead entities DONE
6. Implement the EntityManager::getEntities(tag) functioanlity DONE
7. Implement collisions in sCollision and entity.destroy() if it's dead
8. Implement the rest of the game's functioanlity, including config file reading
