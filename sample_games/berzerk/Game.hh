#pragma once

// fwd decls
class Robot;

class Game {
 public:
  Game() {
    void initUI() {
      // The UI (lives remaining and score) should take up
      // the bottom 10% of the screen or less
    }
  }
  ~Game() {}

  void getInput() {
    case WASD:
      player.setVelocity();
    case shootButton:
      this->launchBullet(/* player's velocity direction */);
    case escape:
      this->shouldQuit = true;
  }

  void updateLoseConditions() {
    if (this->playerLives <= 0) {
      this->shouldQuit = true;
    }
  }

  void updateAnimations() {}

  void updateAI() {
    Robot* robot;
    for (/* each Robot */) {
      robot->aiBehavior();
    }
  }

  void updateCollisions() {
    // There are not going to be that many walls, robots, or projectiles; probably 10 robots and a player, each of
    // whom can fire a projectile (so 22 objects at most). We could try doing 22 x 22 collision tests, but then we
    // have to test walls on top of that. Another option would be a kind of space partitioning; we maintain a
    // list-of-lists of the contents of every room (walls, projectiles, and characters). A character or projectile
    // would test (based on its corners) what room its in before moving and then after, then update the list-of-lists
    // accordingly. We also don't need to test collisions on anything that didn't move.

    for (/* source: each bullet, robot, and the player */) {
      for (/* target: each wall, bullet, robot, and the player **/) {
        if (/* source collides with target */) {
          source->resolveCollision(*target);
          target->resolveCollision(*source);
        }
      }
    }
  }

  void moveCharacters() {}

  void draw() {
    // draw textures and stuff
  }

  bool getShouldQuit() const { return this->shouldQuit; }

 private:
  bool shouldQuit = false;
  int playerLives = 3;
  // owns: currentLevel
};
