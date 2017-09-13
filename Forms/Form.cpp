//
// Created by Utkan on 12.09.2017.
//

#include "Form.h"

void Form::set_focus(bool focus) {
    m_focused = focus;
}

void Form::set_focusable(bool focusable) {
    m_focusable = focusable;
}

void Form::collect(std::vector<Form *> &collection) {
    if(!shown()) return;
    collection.emplace_back(this);
    for(auto& child : m_children) {
        child->collect(collection);
    }
}

void Form::remove_child(Form &form) {
    m_children.erase(std::remove(std::begin(m_children), std::end(m_children), &form), std::end(m_children));
    form.m_parent = nullptr;
}

void Form::add_child(Form &form) {
    if(form.m_parent != nullptr) {
        form.m_parent->remove_child(form);
    }
    form.m_parent = this;
    m_children.emplace_back(&form);
}

void Form::add_listener(Listener *listener) {
    m_listeners.emplace_back(listener);
}

void Form::handle(SDL_Event &event) {
    for(auto& listener : m_listeners) {
        listener->receive(event);
    }
    for(auto& child : m_children) {
        if((child->m_focusable && child->m_focused) || !child->m_focusable)
            child->handle(event);
    }
}

bool Form::inside(int check_x, int check_y) const {
    return check_x > x() && check_x < x() + width() &&
           check_y > y() && check_y < y() + height();
}

void Form::set_shown(bool shown) {
    m_shown = shown;
}

bool Form::shown() const {
    return m_shown;
}
