#include <levels/levels.hpp>
#include <position/position.hpp>
#include <text/text.hpp>
#include <utilities/utilities.hpp>
#include <components/components.hpp>

Levels::Levels(Game* game_, SDL_Renderer* renderer_) : game(game_), renderer(renderer_) {
    int pos = -40;
    for (int i = 0; i < 8; ++i) {
        auto* levelButtonI = &buttons.AddEntity();

        levelButtonI->AddComponent<PositionComponent>(100, pos += 70, 865, 60);
        levelButtonI->AddComponent<Button>(ShortNames::activeButton, ShortNames::button);
        levelButtonI->GetComponent<Button>().SetDiff(-15,0);
        levelButtonI->AddComponent<Text>(ShortNames::font, 50, SDL_Color{0,0,0,255});

        levelButtonI->GetComponent<Text>().SetMessage("Level " + levelNames[i]);
        buts.push_back(levelButtonI);
    }

    endlessMode = new Entity();

    endlessMode->AddComponent<PositionComponent>(100, 590, 865, 60);
    endlessMode->AddComponent<Button>(ShortNames::activeButton, ShortNames::button);
    endlessMode->GetComponent<Button>().SetDiff(-15, 0);
    endlessMode->AddComponent<Text>(ShortNames::font, 50, SDL_Color{0,0,0,255});
    endlessMode->GetComponent<Text>().SetMessage("Endless Mode");
}

void Levels::Run() {
    ticksSinceJoined = SDL_GetTicks();
    SDL_ShowCursor();

    FPSController fpsController{60};
    while (game->inMenu) {
        Update();
        Render();

        fpsController.EndFrame();
    }
}

void Levels::Update() {
    for (auto b : buts) {
        b->Update();
    }
    SDL_Event e;
    SDL_PollEvent(&e);
    if (e.type == SDL_EVENT_MOUSE_BUTTON_UP && e.button.button == SDL_BUTTON_LEFT) {
        for (int i = 0; i < buts.size(); ++i) {
            if (buts[i]->GetComponent<Button>().IsSelected()) {
#ifdef LOGS
                std::cout << "Level " << i << "is started" << '\n';
#endif
                game->SetSettings(i + 1);
                game->endlessMode = 0;
                game->inMenu = 0;
                game->inParty = 1;
                return;
            }
        }
        if (endlessMode->GetComponent<Button>().IsSelected()) {
#ifdef LOGS
            std::cout << "EndlessMode is selected" << '\n';
#endif
            game->SetSettings(0);
            game->endlessMode = 1;
            game->inMenu = 0;
            game->inParty = 1;
            return;
        }
    }
    endlessMode->Update();

    const bool *keystat = SDL_GetKeyboardState(NULL);
    if (keystat[SDL_SCANCODE_ESCAPE] && (SDL_GetTicks() - ticksSinceJoined > 500)) {
        game->inMenu = 0;
        game->Quit();
    }
    if (keystat[SDL_SCANCODE_F11]) {
        game->ToggleFullscreen();
    }

}

void Levels::Render() {
    SDL_RenderClear(renderer);
    buttons.Draw();
    endlessMode->Draw();

    SDL_RenderPresent(renderer);
}
