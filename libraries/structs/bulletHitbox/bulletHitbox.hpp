#pragma once

#include <game/game.hpp>
#include <bullet/bullet.hpp>

class Bullet;

class BulletHitbox {
public:
    BulletHitbox(Bullet* owner_, bool back);
    ~BulletHitbox() {
#ifdef LOGS
        std::cout << "Hitbox deleted" << '\n';
#endif
    }
    void Draw();
    void Update();
    SDL_FRect* GetBox() { return &box; }

    void DestroyOwner();
private:
    Bullet* owner;
    SDL_FRect box;
    int difX;
    int difY;

    SDL_Texture* tex;
    SDL_FRect src = {0,0,9,9};
} ;
