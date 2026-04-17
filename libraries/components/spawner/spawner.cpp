#include <spawner/spawner.hpp>
#include <animatedTexture/animatedTexture.hpp>
#include <short_names/short_names.hpp>
#include <meteorHitbox/meteorHitbox.hpp>
#include <position/position.hpp>
#include <reusedTextures/reusedTextures.hpp>

Spawner::Spawner() {
    active = 0;
}

Spawner::~Spawner() {
    meteors.Clear();
}

void Spawner::Update() {
    if (active == false) return;

    if (meteorsLeft != 0 && SDL_GetTicks() - lastTick >= rate) {
        lastTick = SDL_GetTicks();
        Spawn();
        --meteorsLeft;
    }

    meteors.Update();
    meteors.Refresh();
}

void Spawner::Draw() {
    meteors.Draw();
}

void Spawner::Spawn() {
    auto& meteor = meteors.AddEntity();

    int destX = rand() % (rightBoarder - leftBoarder) + leftBoarder;
    float range = maxSize - minSize;
    float size = minSize + float(rand() % int(range * 100)) / 100;

    meteor.AddComponent<PositionComponent>(destX, 0 - 19 * size, 11 * size, 19 * size);
    meteor.GetComponent<PositionComponent>().SetVelocity(velocity.x, velocity.y);
    meteor.GetComponent<PositionComponent>().SetSpeed(speed);

    meteor.AddComponent<AnimatedTexture>(ReusedTextures::meteorTex);
    auto& tex = meteor.GetComponent<AnimatedTexture>();
    tex.AddAnimation("fall", 0, 4, 150);
    tex.Play("fall");
    tex.SetBoarders(0,0,11,19);
    
    meteor.AddComponent<MeteorHitbox>();

#ifdef LOGS
    std::cout << size << '\n';
#endif
}

void Spawner::SeBoarders(int left, int right) {
    leftBoarder = left;
    rightBoarder = right;
}

void Spawner::SetSize(float min, float max) {
    minSize = min;
    maxSize = max;
}
