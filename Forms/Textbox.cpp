//
// Created by Utkan on 13.09.2017.
//

#include "Textbox.h"
#include "../Misc/Global.h"

Textbox::Textbox(Window &win, int font_size, int box_width) : Form{win},
                                                              m_keyboard_listener{on_key_down, on_key_up, on_text_enter},
                                                              m_button_listener{on_mouse_down, on_mouse_up},
                                                              m_motion_listener{on_mouse_move} {
    set_focusable(true);
    add_listener(&m_keyboard_listener);
    add_listener(&m_button_listener);
    add_listener(&m_motion_listener);

    m_font = TTF_OpenFont(Global::FONT_PATH, font_size);

    width = [box_width]()->int { return box_width; };
    height = [this]()->int { return TTF_FontHeight(this->m_font); };

    on_text_enter.add([this](std::string text) {
        if(m_selection_start_index > -1) erase_selection();
        this->insert_text(text);
    });

    on_key_down.add([this](int key, int mod) {
        switch(key) {
            case SDLK_BACKSPACE:
                if(this->m_selection_start_index > -1) {
                    this->erase_selection();
                } else if (this->m_cursor_index > 0) {
                    this->m_text.erase(std::begin(this->m_text) + this->m_cursor_index - 1);
                    this->move_cursor_left();
                }
                break;
            case SDLK_RIGHT:
                if(mod & KMOD_SHIFT) {
                    this->start_selection();
                } else {
                    this->end_selection();
                }
                this->move_cursor_right();
                break;
            case SDLK_LEFT:
                if(mod & KMOD_SHIFT) {
                    this->start_selection();
                } else {
                    this->end_selection();
                }
                this->move_cursor_left();
                break;
            case SDLK_v:
                if(mod & KMOD_CTRL) {
                    if(this->m_selection_start_index > -1) {
                        this->erase_selection();
                    }
                    this->paste();
                }
                break;
            case SDLK_c:
                if(mod & KMOD_CTRL && this->m_selection_start_index > -1) {
                    this->copy();
                }
                break;
            case SDLK_x:
                if(mod & KMOD_CTRL && this->m_selection_start_index > -1) {
                    this->cut();
                }
                break;
        }
    });

    on_mouse_down.add([this](int b, int x, int y) {
        this->end_selection();
        this->put_cursor(x - this->x());
    });

    on_mouse_move.add([this](int state, int x, int y) {
        if(state & SDL_BUTTON_LMASK) {
            start_selection();
            put_cursor(x - this->x());
        }
    });
}

Textbox::~Textbox() {
    TTF_CloseFont(m_font);
}

void Textbox::draw(SDL_Renderer *renderer) {
    // Draw the background
    SDL_Rect form_rect{x(), y(), width(), height()};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &form_rect);

    // Create the text surface and the main surface from its properties.
    SDL_Surface* text_surface = TTF_RenderText_Blended(m_font, (m_text.empty()) ? " " : m_text.c_str(), SDL_Color{0, 0, 0});
    SDL_Surface* main_surface = SDL_CreateRGBSurfaceWithFormat(text_surface->flags, text_surface->w + 2, text_surface->h, 32, text_surface->format->format);

    // Get the cursor position.
    int cursor_x = 0;
    if (m_cursor_index > 0) {
        std::string left_text = (m_cursor_index == m_text.length()) ? m_text : m_text.substr(0, m_cursor_index);
        TTF_SizeText(m_font, left_text.c_str(), &cursor_x, nullptr);
    }
    // If focused, copy the cursor and selection into main surface.
    if(m_focused) {
        // Copy the cursor.
        SDL_Rect cursor_rect{cursor_x, 1, 1, height() - 5};
        SDL_FillRect(main_surface, &cursor_rect, SDL_MapRGB(main_surface->format, 50, 50, 50));
        // Copy the selection.
        if (m_selection_start_index > -1) {
            // Get the selection start position.
            int selection_x = 0;
            if (m_selection_start_index > 0) {
                std::string left_text = (m_selection_start_index == m_text.length()) ? m_text : m_text.substr(0,
                                                                                                              m_selection_start_index);
                TTF_SizeText(m_font, left_text.c_str(), &selection_x, nullptr);
            }
            int selection_left = std::min(selection_x, cursor_x);
            int selection_right = std::max(selection_x, cursor_x);

            SDL_Rect selection_rect{selection_left, 0, selection_right - selection_left, height()};
            SDL_FillRect(main_surface, &selection_rect, SDL_MapRGB(main_surface->format, 90, 180, 225));
        }
    }
    // Copy the text into main surface.
    SDL_Rect dst = {1, 0, text_surface->w, text_surface->h};
    SDL_BlitSurface(text_surface, nullptr, main_surface, &dst);

    // Calculate the left shift.
    m_left_shift = (int)round(cursor_x / width()) * width();
    // Calculate the source and destination rectangles.
    SDL_Rect crop_main_surface{m_left_shift, 0, width(), height()};
    SDL_Rect dst2{x(), y(), (m_left_shift + width() > main_surface->w) ? main_surface->w - m_left_shift : width(), height()};
    // Draw the main surface.
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, main_surface);
    SDL_RenderCopy(renderer, texture, &crop_main_surface, &dst2);

    // Free the memory.
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(main_surface);
    SDL_FreeSurface(text_surface);
}

void Textbox::put_cursor(int x) {
    if(m_text.empty()) return;

    x += m_left_shift;
    int acc = 0;
    std::size_t index = 0;

    while(x > acc && index < m_text.length()) {
        int advance = 0;
        TTF_GlyphMetrics(m_font, m_text.at(index), nullptr, nullptr, nullptr, nullptr, &advance);
        acc += advance;
        index++;
    }

    if(x > acc) index++;

    m_cursor_index = (index == 0) ? index : index - 1;
}

void Textbox::move_cursor_right() {
    if(m_cursor_index == m_text.length()) return;
    m_cursor_index++;
}

void Textbox::move_cursor_left() {
    if(m_cursor_index == 0) return;
    m_cursor_index--;

}

void Textbox::paste() {
    if(SDL_HasClipboardText()) {
        std::string clipboard_text{SDL_GetClipboardText()};
        insert_text(clipboard_text);
    }
}

void Textbox::copy() {
    SDL_SetClipboardText(extract_selection().c_str());
}

void Textbox::cut() {
    copy();
    erase_selection();
}

void Textbox::insert_text(std::string text) {
    for(auto ch : text) {
        this->m_text.insert(std::begin(this->m_text) + this->m_cursor_index, ch);
        this->move_cursor_right();
    }
}

void Textbox::start_selection() {
    if(m_selection_start_index > -1) return;
    m_selection_start_index = m_cursor_index;
}

void Textbox::erase_selection() {
    int min = std::min(m_cursor_index, m_selection_start_index);
    int max = std::max(m_cursor_index, m_selection_start_index);
    m_text.erase(std::begin(m_text) + min, std::begin(m_text) + max);
    m_cursor_index = min;

    end_selection();
}

std::string Textbox::extract_selection() {
    int min = std::min(m_cursor_index, m_selection_start_index);
    int max = std::max(m_cursor_index, m_selection_start_index);
    return m_text.substr(min, max - min);
}

void Textbox::end_selection() {
    if(m_selection_start_index < 0) return;
    m_selection_start_index = -1;
}

std::string Textbox::text() const {
    return m_text;
}
