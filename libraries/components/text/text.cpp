#include<text/text.hpp>
#include<texture_manager/texture_manager.hpp>
#include <position/position.hpp>

Text::Text(std::string fontPath, int fontSize, const SDL_Color color_) :
    color(color_) {
    TTF_Init();
    const char* f = fontPath.data();
    font = TTF_OpenFont(f, fontSize);
#ifdef LOGS
    std::cerr << SDL_GetError() << '\n';
#endif
    if (!font) {
#ifdef LOGS
        std::cerr << "Failed to load font\n";
#endif
    }
}

Text::~Text() {
    TTF_CloseFont(font);
    SDL_DestroyTexture(textTex);
}

void Text::Init() {
    auto& tmp = owner->GetComponent<PositionComponent>();
    destRect.x = tmp.X();
    destRect.y = tmp.Y();
}

void Text::SetSize(int w, int h) {
    destRect.w = w;
    destRect.h = h;
}

void Text::SetMessage(std::string message_) {
    message = message_;
    SDL_DestroyTexture(textTex);
    SDL_DestroySurface(textSurface);
    textSurface = TTF_RenderText_Solid(font, message.c_str(), 0, color);

    SDL_DestroyTexture(textTex);
    textTex = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
    destRect.w = textTex->w;
    destRect.h = textTex->h;
}

void Text::AddMessage(std::string extraMes) {
    message += extraMes;
    SetMessage(message);
    destRect.w = textTex->w;
    destRect.h = textTex->h;
}

void Text::Update() {
    // SDL_QueryTexture(textTex, nullptr, nullptr, &destRect.w, &destRect.h);
}

void Text::Draw() {
#ifdef LOGS
    if (!textTex) std::cerr << "error" << '\n';
#endif
    SDL_RenderTexture(Game::renderer, textTex, NULL, &destRect);
}
