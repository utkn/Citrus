//
// Created by Utkan on 12.09.2017.
//

#include "Window.h"

Window::Window(int width, int height) {
    m_root = new Form(*this);
    m_root->set_focusable(true);
    m_root->width = [width]()->int {
        return width;
    };
    m_root->height = [height]()->int {
        return height;
    };
    m_form_list.emplace_back(m_root);
}

void Window::collect_draw_list() {
    m_draw_list.clear();
    m_root->collect(m_draw_list);
}

void Window::render(SDL_Renderer *renderer) {
    for(auto& form : m_draw_list) {
        form->draw(renderer);
        if(m_debug) {
            SDL_Rect rect {form->x(), form->y(), form->width(), form->height()};
            SDL_SetRenderDrawColor(renderer, 255, (form->m_focused) ? 255 : 0, 0, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

void Window::handle(SDL_Event &event) {
    collect_draw_list();

    if(event.type == SDL_MOUSEBUTTONDOWN) {
        set_focus(event.button.x, event.button.y);
    } else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_0) {
        m_debug = !m_debug;
    }
    m_root->handle(event);
}

void Window::set_focus(int x, int y) {
    Form* branch = nullptr;
    for(auto it = m_draw_list.rbegin(); it != m_draw_list.rend(); ++it) {
        if(branch == nullptr
           && (*it)->m_focusable
           && (*it)->inside(x, y)) {
            branch = *it;
        }
        (*it)->set_focus(false);
    }
    if(branch == nullptr) return;

    branch->set_focus(true);
    while(branch->m_parent != nullptr) {
        // If a form is non-focusable its state is determined by its parents.
        for(auto& branch_child : branch->m_children) {
            if(!branch_child->m_focusable) branch_child->set_focus(true);
        }
        branch = branch->m_parent;
        branch->set_focus(true);
    }
}
