#include <game/game.hpp>
#include <components/components.hpp>
#include <utilities/utilities.hpp>
#include <party/party.hpp>
#include <levels/levels.hpp>
#include <reusedTextures/reusedTextures.hpp>
#include <texture_manager/texture_manager.hpp>

SDL_Renderer* Game::renderer = nullptr;

SDL_Event Game::event;
Game::~Game() {
    TTF_Quit();
    SDL_Quit();
    SDL_DestroyRenderer(Game::renderer);
    SDL_DestroyWindow(window);
}

void Game::Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);

        renderer = SDL_CreateRenderer(window, NULL);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        isRunning = true;
    }
    else {
#ifdef LOGS
        std::cerr << "Failed to init SDL" << '\n';
#endif
        isRunning = false;
    }

    if (!TTF_Init()) {
#ifdef LOGS
        std::cerr << "Failed to init TTF" << '\n';
#endif
        return;
    }

    Life::Init();
    ReusedTextures::Init();
}

bool& Game::IsRunning() {
    return isRunning;
}
void Game::ToggleFullscreen() {
    static int64_t lastUsed = 0;
    if (SDL_GetTicks() - lastUsed > 500) {
        lastUsed = SDL_GetTicks();
        fullscreen_ = !fullscreen_;
        (fullscreen_) ? SDL_SetWindowFullscreen(window, 1) : SDL_SetWindowFullscreen(window, 0);
    }
}
void Game::Quit() {
    isRunning = 0;
}

void Game::Run() {
    Party party(this, renderer);
    Levels levels(this, renderer);
    while (IsRunning()) {
        if (inMenu) {
            levels.Run();
        }
        if (inParty) {
            party.Run();
        }
    }
}

void Life::Init() {
    heart = TextureManager::LoadTexture("../assets/heart.png");
}
