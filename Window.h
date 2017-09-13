//
// Created by Utkan on 12.09.2017.
//

#ifndef CİTRUS_WİNDOW_H
#define CİTRUS_WİNDOW_H


#include "Forms/Form.h"

class Window {
public:
    Window(int width, int height);

    void collect_draw_list();
    void render(SDL_Renderer* renderer);
    void handle(SDL_Event& event);
    void set_focus(int x, int y);

    template <typename T, typename... Args>
    T& create(Args&&... args) {
        T* form = new T(*this, std::forward<Args>(args)...);
        m_root->add_child(*form);

        m_form_list.emplace_back(form);
        return *form;
    };
private:
    std::vector<std::unique_ptr<Form>> m_form_list;
    std::vector<Form*> m_draw_list;
    Form* m_root;
    bool m_debug = true;
};



#endif //CİTRUS_WİNDOW_H
