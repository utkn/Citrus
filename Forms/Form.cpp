//
// Created by Utkan on 12.09.2017.
//

#include "Form.h"

void Form::set_focus(bool focus) {
    m_focus = focus;
}

void Form::set_focusable(bool focusable) {
    m_focusable = focusable;
}

void Form::collect(std::vector<Form *> &collection) {
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
        if((child->m_focusable && child->m_focus) || !child->m_focusable)
            child->handle(event);
    }
}