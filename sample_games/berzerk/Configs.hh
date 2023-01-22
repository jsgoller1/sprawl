#pragma once

#include "Vect2D.hh"

constexpr int DEFAULT_SCREEN_WIDTH = 1400;
constexpr int DEFAULT_SCREEN_HEIGHT = 900;
constexpr int INTERNAL_PLAY_AREA_WIDTH = DEFAULT_SCREEN_WIDTH - 200;
constexpr int INTERNAL_PLAY_AREA_HEIGHT = DEFAULT_SCREEN_HEIGHT - 200;

constexpr int PLAYER_DYING_ANIMATION_LOOP_COUNT = 2;
constexpr int PLAYER_SHOOT_DELAY_MS = 750;
constexpr int PLAYER_MOVE_SPEED = 5;

// TODO: Robot should move, shoot, and animate
// faster as fewer remain
constexpr int ROBOT_MOVE_SPEED = 1;
constexpr int ROBOT_DEFAULT_WIDTH = 40;
constexpr int ROBOT_DEFAULT_HEIGHT = 55;
constexpr int ROBOT_SHOOT_DELAY_MS = 750;

constexpr int BULLET_DEFAULT_SPEED = 10;
constexpr int BULLET_DEFAULT_HEIGHT = 35;
constexpr int BULLET_DEFAULT_WIDTH = 35;

constexpr int WALL_THICCNESS = 10;
constexpr int VERTICAL_WALL_WIDTH = WALL_THICCNESS;
constexpr int VERTICAL_WALL_HEIGHT = INTERNAL_PLAY_AREA_HEIGHT / 3;
constexpr int HORIZONTAL_WALL_WIDTH = INTERNAL_PLAY_AREA_WIDTH / 5;
constexpr int HORIZONTAL_WALL_HEIGHT = WALL_THICCNESS;

constexpr int WALLS_COUNT = 38;
constexpr int HORIZONTAL_BORDER_WALLS_COUNT = 4;
constexpr int BORDER_WALLS_N[] = {0, 1, 3, 4};
constexpr int BORDER_WALLS_S[] = {15, 16, 18, 19};
constexpr int VERTICAL_BORDER_WALLS_COUNT = 2;
constexpr int BORDER_WALLS_W[] = {20, 32};
constexpr int BORDER_WALLS_E[] = {25, 37};
constexpr int EXIT_N = 2;
constexpr int EXIT_S = 17;
constexpr int EXIT_W = 26;
constexpr int EXIT_E = 31;
constexpr int EXIT_COUNT = 4;
constexpr int HORIZONTAL_INTERNAL_WALLS_COUNT = 10;
constexpr int HORIZONTAL_INTERNAL_WALLS[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
constexpr int VERTICAL_INTERNAL_WALLS_COUNT = 12;
constexpr int VERTICAL_INTERNAL_WALLS[] = {21, 22, 23, 24, 27, 28, 29, 30, 33, 34, 35, 36};
constexpr int FIXED_LEVEL_LAYOUT_WALLS_COUNT = 6;
constexpr int FIXED_LEVEL_LAYOUT_WALLS[] = {21, 27, 8, 9, 35, 34};
constexpr int ROBOTS_COUNT = 1;
const Vect2D TOP_LEFT = Vect2D::zero();

constexpr int BULLET_SPRITE_WIDTH_PX = 7;
constexpr int BULLET_SPRITE_HEIGHT_PX = 7;
constexpr int BULLET_SPRITE_BOUNDARY_WIDTH_PX = 2;

constexpr int OTTO_SPRITE_WIDTH_PX = 8;
constexpr int OTTO_SPRITE_HEIGHT_PX = 16;
constexpr int OTTO_SPRITE_BOUNDARY_WIDTH_PX = 1;

constexpr int PLAYER_SPRITE_WIDTH_PX = 8;
constexpr int PLAYER_SPRITE_HEIGHT_PX = 16;
constexpr int PLAYER_SPRITE_BOUNDARY_WIDTH_PX = 1;

constexpr int ROBOT_SPRITE_WIDTH_PX = 8;
constexpr int ROBOT_SPRITE_HEIGHT_PX = 11;
constexpr int ROBOT_SPRITE_BOUNDARY_WIDTH_PX = 1;
