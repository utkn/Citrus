//
// Created by Utkan on 12.09.2017.
//

#include "Button.h"
#include "../Window.h"

Button::Button(Window &win, std::string &&text, int font_size) : Form{win},
                                                                 m_label{m_window.create<Label>(std::move(text), font_size)},
                                                                 m_button_listener{on_mouse_down, on_mouse_up} {
    set_focusable(true);
    add_child(m_label);
    add_listener(&m_button_listener);

    width = [this]()->int { return this->m_label.width(); };
    height = [this]()->int { return this->m_label.height(); };

    m_label.x = [this]()->int { return this->x(); };
    m_label.y = [this]()->int { return this->y(); };

    on_mouse_down.add([this](int button, int x, int y) {
        if(this->inside(x, y)) {
            m_bg_color = SDL_Color{200, 200, 200, 255};
        }
    });

    on_mouse_up.add([this](int button, int x, int y) {
        m_bg_color = SDL_Color{255, 255, 255, 255};
    });
}

void Button::draw(SDL_Renderer *renderer) {
    SDL_Rect rect = {x(), y(), width(), height()};
    SDL_SetRenderDrawColor(renderer, m_bg_color.r, m_bg_color.g, m_bg_color.b, 255);
    SDL_RenderFillRect(renderer, &rect);
}
