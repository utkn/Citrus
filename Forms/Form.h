//
// Created by Utkan on 12.09.2017.
//

#ifndef CİTRUS_FORM_H
#define CİTRUS_FORM_H


#include <SDL2/SDL_system.h>
#include <SDL2/SDL_events.h>
#include <vector>
#include "../Listeners/Listener.h"
#include "../Misc/Relation.h"

class Window;
class Form {
public:
    explicit Form(Window& window) : m_window{window} {}
    virtual void draw(SDL_Renderer* renderer) {}
    virtual ~Form() = default;

    void handle(SDL_Event& event);
    void add_listener(Listener* listener);
    void add_child(Form& form);
    void remove_child(Form& form);
    void collect(std::vector<Form*>& collection);

    void set_focusable(bool focusable);
    void set_focus(bool focus);

    bool inside(int check_x, int check_y) {
        return check_x > x() && check_x < x() + width() &&
                check_y > y() && check_y < y() + height();
    }

    Relation x;
    Relation y;
    Relation width;
    Relation height;

    friend class Window;
protected:
    bool m_focusable = false;
    bool m_focus = false;

    std::vector<Listener*> m_listeners;
    std::vector<Form*> m_children;
    Form* m_parent = nullptr;
    Window& m_window;
};



#endif //CİTRUS_FORM_H
