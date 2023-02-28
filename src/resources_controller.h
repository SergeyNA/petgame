#ifndef EXTERN_VAR //#pragma once
#define EXTERN_VAR

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 540;
#define TECHNOLOGIES_COUNT 40 //Research_tree.cpp

bool FULLSCREEN = false;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

TTF_Font* gFont[4] = {nullptr, nullptr, nullptr, nullptr};
SDL_Color textColor = { 255, 0, 0, 255 };

std::stringstream string_buffer;

int mouseX, mouseY;

enum font_colors {RED, GREEN, BLUE, YELLOW, GRAY, BLACK, WHITE};

int resourses;
int people;
int science_points;
int action_limits;
int action_points;

enum game_event {GAME_NEW_TURN, GAME_ATTACK, BUILD_SHIP, EXPLORATION, HULL_CREATION, DO_RESEARCH, MOVING_FLEET};
void action_handler(game_event e);
void openTechnology(int index);

bool scroll_move = false;

int global_shift;
int y_offset;
int research_tree_offset;
bool node_is_shifted;
std::string logMessage = "";

enum Construction_mode {OVERVIEW_MODE, CREATE_HULL_MODE = 0, LOG_OPEN, LOADING_SHIP} construction_mode;

#endif
