#pragma once

#ifndef Game_hpp
#define Game_hpp

#include <string>
#include <iostream>
#include <thread>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <chrono>
#include <vector>
#include <array>
#include <stack>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <tuple>
#include <bitset>
#include <memory>

enum settings {METEOR_SIZE_MIN,  METEOR_SIZE_MAX,  METEOR_FREQUENCY,  METEOR_SPEED,         METEOR_NUM,  
               BUL_SIZE,         BUL_NUM,          BUL_SPEED,         METEOR_ACCELERATION,  LIVES};

class Game {
public:
    Game() = default;
    ~Game();

    void Init(const char* title, int xPos, int yPos, int widht, int height, bool fullscreen);
    void Run(); 
    bool& IsRunning();
    void Quit();

    void ToggleFullscreen();
    
    static SDL_Renderer *renderer;
    static SDL_Event event;
    bool text = 0;

    float fm = INT_MAX;
                                  // LVL em      1     2     3     4     5    6     7     8
    std::vector<float> meteorSizeMin   = {8,     6,    5,    4,    2,    6,   3,    5,    6};
    std::vector<float> meteorSizeMax   = {9,     9,    6,    6,    9,    7,   4,    8,    8};
    std::vector<float> meteorFrequency = {1200,  500, 1000, 500,  1000, 700, 700,  800, 500};
    std::vector<float> meteorSpeed     = {3,     3,    3.5,  4.5,  4,    3.5, 2,    3,    4}; 
    std::vector<float> meteorNum       = {fm,    15,   20,   20,   20,   40,  20,   50,   20};
    std::vector<float> bulletSize      = {4,     3.5,  3,    3,    4,    3,   4,    3,    3.5};
    std::vector<float> bulletNum       = {fm,    25,   30,   25,   25,   50,  25,   60,   25};
    std::vector<float> bulletSpeed     = {40,    40,   25,   35,   30,   22,  20,   25,   50};
    std::vector<float> meteorAccel     = {0,     0,    0,    3,    3,    3,   3,    0,    3};
    std::vector<float> lives           = {5,     5,    3,    5,    3,    5,   5,    4,    1};

    auto SetSettings(int lvl) {
        settings = std::vector<float>{meteorSizeMin[lvl], meteorSizeMax[lvl], meteorFrequency[lvl], meteorSpeed[lvl], meteorNum[lvl],       
                                      bulletSize[lvl],    bulletNum[lvl],     bulletSpeed[lvl],     meteorAccel[lvl], lives[lvl]};
    }
    float Setting(size_t param) {
        return settings[param];
    }

    bool inMenu = 1;
    bool inParty = 0;

    bool endlessMode = 0;

private:

    std::vector<float> settings;
    bool isRunning = 1;
    bool fullscreen_ = 0;
    SDL_Window *window;
} ;


struct Hitboxes {
    static bool Active() { return active; }
    static void Switch() {
        if (SDL_GetTicks() - tick > 500) {
            tick = SDL_GetTicks();
            active = !active;
#ifdef LOGS
            std::cout << (active ? "Hitboxes Shown" : "Hitboxes Hidden") << std::endl;
#endif
        }
    }

    inline static long long tick = 0;
    inline static bool active = 0;
};


class Life {
public:
    static void Init();

    static void SetHP(int num) { hp = num; }
    static int hpLeft() { return hp; }

    static void MakeDamage(int damage) { hp -= damage; }
    static void Draw() { 
        for (int i = 0; i < hp; ++i) {
            SDL_FRect dest = {30, float(30 + 90 * i), 80, 80};
            SDL_RenderTextureRotated(Game::renderer, heart, NULL, &dest, 0.0, NULL, SDL_FLIP_NONE);
        }
    }
private:
    inline static SDL_Texture* heart;
    inline static int hp = 0;
} ;

#endif 
