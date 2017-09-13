//
// Created by Utkan on 12.09.2017.
//

#include "VList.h"
#include "../Window.h"

VList::VList(Window &window) : Form{window}, m_first{m_window.create<Form>()} {
    set_focusable(true);

    m_first.x = [this]()->int { return this->x(); };
    m_first.y = [this]()->int { return this->y(); };
    add_child(m_first);

    width = [this]()->int { return this->m_max_width; };
    height = [this]()->int {
        int acc = 0;
        for(auto& child : this->m_children) {
            acc += child->height();
        }
        return acc;
    };
}

void VList::add_element(Form &form) {
    m_max_width = std::max(m_max_width, form.width());

    Form* last = m_children.back();
    form.x = [last]()->int {
        return last->x();
    };
    form.y = [last]()->int {
        return last->y() + last->height();
    };

    add_child(form);
}
