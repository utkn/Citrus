//
// Created by Utkan on 12.09.2017.
//

#include "MouseButtonListener.h"

MouseButtonListener::MouseButtonListener(Slot<int, int, int> &on_mouse_down, Slot<int, int, int> &on_mouse_up)
        : on_mouse_down_reference{on_mouse_down},
          on_mouse_up_reference{on_mouse_up} {
}

void MouseButtonListener::receive(SDL_Event &event) {
    switch(event.type) {
        case SDL_MOUSEBUTTONDOWN:
            on_mouse_down_reference.invoke(event.button.button, event.button.x, event.button.y);
            break;
        case SDL_MOUSEBUTTONUP:
            on_mouse_up_reference.invoke(event.button.button, event.button.x, event.button.y);
            break;
    }
}
