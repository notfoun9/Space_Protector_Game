#include <texture_manager/texture_manager.hpp>
#include <mouse/mouse.hpp>
#include <SDL3_image/SDL_image.h>

[[nodiscard]] SDL_Texture* TextureManager::LoadTexture(const char* texture) {
    SDL_Surface* tmpSurface = IMG_Load(texture);
    SDL_Texture* textureFromSurface = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    if (!textureFromSurface) {
#ifdef LOGS
        std::cerr << "Texture: " << texture << " is not created" << '\n';
#endif
    }

    SDL_DestroySurface(tmpSurface);

    return textureFromSurface;
}

void TextureManager::Draw(SDL_Texture* texture, const SDL_FRect* src, const SDL_FRect *dest, SDL_FlipMode flip) {
    SDL_RenderTextureRotated(Game::renderer, texture, src, dest, 0.0, NULL, flip);
}

void TextureManager::Draw(SDL_Texture* texture, const SDL_FRect* src, const SDL_FRect* dest, double angle, SDL_FPoint* center, SDL_FlipMode flip) {
    SDL_RenderTextureRotated(Game::renderer, texture, src, dest, angle, center, flip);
}
