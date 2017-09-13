//
// Created by Utkan on 12.09.2017.
//

#include "HList.h"
#include "../Window.h"


HList::HList(Window &window) : Form{window}, m_first{m_window.create<Form>()} {
    set_focusable(true);

    m_first.x = [this]()->int { return this->x(); };
    m_first.y = [this]()->int { return this->y(); };
    add_child(m_first);

    height = [this]()->int { return this->m_max_height; };
    width = [this]()->int {
        int acc = 0;
        for(auto& child : this->m_elements) {
            acc += child->width();
        }
        return acc;
    };
}

void HList::add_element(Form &form) {
    m_max_height = std::max(m_max_height, form.height());

    Form* last = m_elements.back();
    form.x = [last]()->int {
        return last->x() + last->width();
    };
    form.y = [last]()->int {
        return last->y();
    };

    m_elements.emplace_back(&form);
    add_child(form);
}
