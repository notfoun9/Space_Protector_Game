#include <shooter/shooter.hpp>
#include <follower/follower.hpp>

Shooter::Shooter(SDL_Texture* bulTex) {
    tex = bulTex;
}

void Shooter::Init() {

}

void Shooter::SetSize(float size) {
    angle = owner->GetComponent<Follower>().GetAngle();
    SDL_FRect temp =  owner->GetComponent<Follower>().GetDest();

    destFRect.w = size * baseW;
    destFRect.h = size * baseH;
    destFRect.y = temp.y;
    destFRect.x = temp.x + temp.w / 2 - destFRect.w / 2;

    center.y = owner->GetComponent<Follower>().GetCenter()->y;
    center.x = destFRect.w / 2;
}

Shooter::~Shooter() {
    for (auto bul : bullets) {
        delete bul;
        SDL_DestroyTexture(tex);
    }
}

void Shooter::Update() {
    angle = owner->GetComponent<Follower>().GetAngle();


    if (Game::event.button.button == SDL_BUTTON_LEFT) {
        Shoot();
    }

    for (auto bullet : bullets) {
        bullet->Update();
    }

    while (!bulletsToDestroy.empty()) {
        bullets.erase(bulletsToDestroy.top());
        delete bulletsToDestroy.top();

        bulletsToDestroy.pop();
    }

}

void Shooter::Draw() {
    for (auto &bullet : bullets) {
        bullet->Draw();
    }
}

void Shooter::Shoot() {
    if (bulletsLeft > 0) {
        Bullet* bul = new Bullet(this);
        bul->SetAcceleration(0,-0.06);
        bullets.insert(bul);
        --bulletsLeft;
    }
#ifdef LOGS
    std::cout << "Bullets left: " << bulletsLeft << '\n';
#endif
}
