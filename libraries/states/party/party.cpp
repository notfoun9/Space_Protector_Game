#include "time/time.hpp"
#include <party/party.hpp>
#include <components/components.hpp>
#include <utilities/utilities.hpp>

Party::Party(Game* game_, SDL_Renderer* renderer_) : game(game_), renderer(renderer_) {

    mouse.AddComponent<PositionComponent>(0,0,45,45);
    mouse.AddComponent<Mouse>(ShortNames::scope);
    mouse.GetComponent<Mouse>().SetBoarders(0,0,15,15);

    background.AddComponent<PositionComponent>(0,0,1920,1080);
    background.AddComponent<SimpleTexture>(ShortNames::back);
    background.GetComponent<SimpleTexture>().SetBoarders(0,0,1920,1080);

    base.AddComponent<PositionComponent>(431,610,132,66);
    base.AddComponent<SimpleTexture>(ShortNames::base);
    base.GetComponent<SimpleTexture>().SetBoarders(0,0,22,11);

    ship.AddComponent<PositionComponent>(-30,645,1120,500);
    ship.AddComponent<SimpleTexture>(ShortNames::ship);
    ship.GetComponent<SimpleTexture>().SetBoarders(0,0,800,500);

    launcher.AddComponent<PositionComponent>(470,550,55,100);
    launcher.AddComponent<Follower>(ShortNames::launcher2);
    launcher.GetComponent<Follower>().SetCenter(27, 75);
    launcher.GetComponent<Follower>().SetBoarders(0,0,22,40);

    launcher.AddComponent<Shooter>(ReusedTextures::bulletTex);
    launcher.GetComponent<Shooter>().SetSrc(0,0,64,128);

    bulsLeft.AddComponent<PositionComponent>(20,600,200,50);
    bulsLeft.AddComponent<Text>(ShortNames::font, 40, SDL_Color{255,255,255,0});

    spawner.AddComponent<Spawner>();
    spawner.GetComponent<Spawner>().SeBoarders(120, 1000);

    gameLost.AddComponent<PositionComponent>(200, 250);
    gameLost.AddComponent<Text>(ShortNames::font, 100, SDL_Color{255,255,255,0});
    gameLost.GetComponent<Text>().SetMessage("GAME OVER!");

    gameWon.AddComponent<PositionComponent>(200, 250);
    gameWon.AddComponent<Text>(ShortNames::font, 130, SDL_Color{255,255,255,0});
    gameWon.GetComponent<Text>().SetMessage("YOU WIN!");
}

void Party::Run() {
    gameState = 0;
    score = 0;
    SDL_HideCursor();
    
    launcher.GetComponent<Shooter>().SetSpeed(game->Setting(BUL_SPEED));
    launcher.GetComponent<Shooter>().SetSize(game->Setting(BUL_SIZE));
    launcher.GetComponent<Shooter>().AddBullets(game->Setting(BUL_NUM));

    spawner.GetComponent<Spawner>().SetRate(game->Setting(METEOR_FREQUENCY));
    spawner.GetComponent<Spawner>().Start();
    spawner.GetComponent<Spawner>().SetSize(game->Setting(METEOR_SIZE_MIN), game->Setting(METEOR_SIZE_MAX));
    spawner.GetComponent<Spawner>().SetVelocity(0, game->Setting(METEOR_SPEED));
    spawner.GetComponent<Spawner>().SetMeteorsNum(game->Setting(METEOR_NUM));
    spawner.GetComponent<Spawner>().SetSpeed(2);

    Life::SetHP(game->Setting(LIVES));

    FPSController fpsController{60};
    while (game->inParty) {

        SDL_Event e;
        SDL_PollEvent(&e);

        if (e.type == SDL_EVENT_MOUSE_BUTTON_UP && e.button.button == SDL_BUTTON_LEFT) {
            launcher.GetComponent<Shooter>().Shoot();
        }

        if (gameState == 0) {
            if (Life::hpLeft() == 0) {
                gameState = -1;
            }
            else if (spawner.GetComponent<Spawner>().MeteorsLeft() == 0 
                     && spawner.GetComponent<Spawner>().GetMeteors()->GetEntities()->empty()) {
                gameState = 1;
            }
        }

        const bool *keystat = SDL_GetKeyboardState(NULL);
        if (keystat[SDL_SCANCODE_ESCAPE]) {
            game->inParty = 0;
            game->inMenu = 1;
            launcher.GetComponent<Shooter>().DeleteBulls();
            spawner.GetComponent<Spawner>().DeleteMets();   

#ifdef LOGS
            std::cout << "ESC pressed" << '\n';
#endif
            continue;
        }
        if (keystat[SDL_SCANCODE_H]) {
            Hitboxes::Switch();
        }
        if (keystat[SDL_SCANCODE_F11]) {
            game->ToggleFullscreen();
        }

        Update();
        Render();

        fpsController.EndFrame();
    }
}


void Party::Update() {

    base.Update();
    launcher.Update();
    spawner.Update();
    mouse.Update();
    if (!game->endlessMode) {
        bulsLeft.GetComponent<Text>().SetMessage("Bullets: ");
        bulsLeft.GetComponent<Text>().AddMessage(std::to_string(launcher.GetComponent<Shooter>().BulletsLeft()));   
    }
    else {
        bulsLeft.GetComponent<Text>().SetMessage("Score: ");
        bulsLeft.GetComponent<Text>().AddMessage(std::to_string(score));   
    }

    bulsLeft.Update();
    if (launcher.HasComponent<BulletsCollider>() == 0) return;

    BulletHitbox* aboba;
    auto* meteors = spawner.GetComponent<Spawner>().GetMeteors()->GetEntities();
    for (auto& met : *meteors) {
        aboba = (launcher.GetComponent<BulletsCollider>().DoesCollide((*met).GetComponent<MeteorHitbox>().GetBox()));
        if (aboba) {
            aboba->DestroyOwner();
            met->Destroy();
            ++score;
            spawner.GetComponent<Spawner>().IncVelocity(0.1f);
            if (score % 10 == 0) {
                if (score % 20 == 0) Life::MakeDamage(-1);
                launcher.GetComponent<Shooter>().Speed() *= 1.1f;
            }

        }
    }
}

void Party::Render() {
    SDL_RenderClear(renderer);

    background.Draw();
    launcher.Draw();
    launcher.GetComponent<Follower>().Draw();
    base.Draw();
    ship.Draw();
    bulsLeft.Draw();
    Life::Draw();

    if (gameState == 0) {
        spawner.Draw();
    }
    else if (gameState == 1) {
        gameWon.Draw();
    }
    else {
        gameLost.Draw();
    }
    mouse.Draw();

    SDL_RenderPresent(renderer);

}
