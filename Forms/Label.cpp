//
// Created by Utkan on 12.09.2017.
//

#include "Label.h"
#include "../Global.h"

Label::Label(Window &win, std::string &&text, int font_size, SDL_Color color) : Form{win},
                                                                                m_text{std::move(text)},
                                                                                m_color{color} {
    m_font = TTF_OpenFont(Global::FONT_PATH, font_size);
    m_surface = TTF_RenderText_Blended(m_font, m_text.c_str(), m_color);

    width = [this]()->int {
        return this->m_surface->w;
    };
    height = [this]()->int {
        return this->m_surface->h;
    };
}

void Label::draw(SDL_Renderer *renderer) {
    SDL_Texture* tx = SDL_CreateTextureFromSurface(renderer, m_surface);
    SDL_Rect rect{x(), y(), width(), height()};
    SDL_RenderCopy(renderer, tx, nullptr, &rect);
    SDL_DestroyTexture(tx);
}

Label::~Label() {
    SDL_FreeSurface(m_surface);
    TTF_CloseFont(m_font);
}
