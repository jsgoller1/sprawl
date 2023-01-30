#pragma once
#include <set>

#include "Vect2D.hh"

// Screen
constexpr int DEFAULT_SCREEN_WIDTH = 1400;
constexpr int DEFAULT_SCREEN_HEIGHT = 900;
constexpr int INTERNAL_PLAY_AREA_WIDTH = DEFAULT_SCREEN_WIDTH - 200;
constexpr int INTERNAL_PLAY_AREA_HEIGHT = DEFAULT_SCREEN_HEIGHT - 200;

// Player behavior
constexpr int PLAYER_DYING_ANIMATION_LOOP_COUNT = 2;
constexpr int PLAYER_SHOOT_DELAY_MS = 750;
constexpr int PLAYER_MOVE_SPEED = 5;

// Player sprite
constexpr int PLAYER_SPRITE_WIDTH_PX = 8;
constexpr int PLAYER_SPRITE_HEIGHT_PX = 16;
constexpr int PLAYER_SPRITE_BOUNDARY_WIDTH_PX = 1;

// Robot behavior
// TODO: Robot should move, shoot, and animate faster as fewer remain
constexpr int ROBOT_MOVE_SPEED = 1;
constexpr int ROBOT_DEFAULT_WIDTH = 40;
constexpr int ROBOT_DEFAULT_HEIGHT = 55;
constexpr int ROBOT_DYING_WIDTH = 80;
constexpr int ROBOT_DYING_HEIGHT = 80;
constexpr int ROBOT_SHOOT_DELAY_MS = 750;
constexpr int ROBOT_PURSUIT_DISTANCE_PX = 900;
constexpr int ROBOT_SHOOTING_ERROR_MARGIN_PX = 15;

// Robot sprite
constexpr int ROBOT_SPRITE_WIDTH_PX = 8;
constexpr int ROBOT_SPRITE_HEIGHT_PX = 12;
constexpr int ROBOT_SPRITE_BOUNDARY_WIDTH_PX = 1;
constexpr int ROBOT_DYING_SPRITE_HEIGHT_PX = 16;
constexpr int ROBOT_DYING_SPRITE_WIDTH_PX = 16;

// Bullet behavior
constexpr int BULLET_DEFAULT_SPEED = 10;
constexpr int BULLET_DEFAULT_HEIGHT = 35;
constexpr int BULLET_DEFAULT_WIDTH = 35;

// Bullet sprite
constexpr int BULLET_SPRITE_WIDTH_PX = 7;
constexpr int BULLET_SPRITE_HEIGHT_PX = 7;
constexpr int BULLET_SPRITE_BOUNDARY_WIDTH_PX = 2;

// Otto sprite
constexpr int OTTO_SPRITE_WIDTH_PX = 8;
constexpr int OTTO_SPRITE_HEIGHT_PX = 16;
constexpr int OTTO_SPRITE_BOUNDARY_WIDTH_PX = 1;

// Wall behavior
constexpr int WALL_THICCNESS = 10;
constexpr int VERTICAL_WALL_WIDTH = WALL_THICCNESS;
constexpr int VERTICAL_WALL_HEIGHT = INTERNAL_PLAY_AREA_HEIGHT / 3;
constexpr int HORIZONTAL_WALL_WIDTH = INTERNAL_PLAY_AREA_WIDTH / 5;
constexpr int HORIZONTAL_WALL_HEIGHT = WALL_THICCNESS;

// Level behavior, see Level.hh for explanation of what indexes represent
constexpr int ROBOTS_COUNT = 1;
constexpr int EXIT_N = 2;
constexpr int EXIT_S = 17;
constexpr int EXIT_W = 26;
constexpr int EXIT_E = 31;
const std::set<int> HORIZONTAL_EXIT_WALLS{EXIT_N, EXIT_S};
const std::set<int> VERTICAL_EXIT_WALLS{EXIT_W, EXIT_E};
const std::set<int> HORIZONTAL_BORDER_WALLS{0, 1, 3, 4, 15, 16, 18, 19};
const std::set<int> VERTICAL_BORDER_WALLS{20, 32, 25, 37};
const std::set<int> HORIZONTAL_INTERNAL_WALLS{5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
const std::set<int> VERTICAL_INTERNAL_WALLS{21, 22, 23, 24, 27, 28, 29, 30, 33, 34, 35, 36};
constexpr int GENERATED_WALL_COUNT = 6;

const Vect2D CELL_0_CENTER = Vect2D(-HORIZONTAL_WALL_WIDTH * 2, VERTICAL_WALL_HEIGHT);
const Vect2D NORTH_SPAWN = Vect2D(0, VERTICAL_WALL_HEIGHT);
const Vect2D EAST_SPAWN = Vect2D(HORIZONTAL_WALL_WIDTH * 2, 0);
const Vect2D SOUTH_SPAWN = Vect2D(0, -VERTICAL_WALL_HEIGHT);
const Vect2D WEST_SPAWN = Vect2D(HORIZONTAL_WALL_WIDTH * -2, 0);
// const Vect2D PLAYER_SPAWN_POINT = CELL_0_CENTER;

// Misc
constexpr int DEFAULT_ANIMATION_FRAME_SHOW_LENGTH_MS = 150;
const Vect2D TOP_LEFT = Vect2D::zero();
constexpr int BULLET_SPAWN_OFFSET_DISTANCE_PX = 50;
constexpr int NO_COLLISION = -1;
