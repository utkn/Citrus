//
// Created by Utkan on 12.09.2017.
//

#include <string>
#include "KeyboardListener.h"

KeyboardListener::KeyboardListener(Slot<int, int> &on_key_down, Slot<int, int> &on_key_up, Slot<std::string> &on_text_enter)
        : on_key_down_reference{on_key_down},
          on_key_up_reference{on_key_up},
          on_text_enter_reference{on_text_enter} {
}

void KeyboardListener::receive(SDL_Event &event) {
    switch(event.type) {
        case SDL_KEYDOWN:
            on_key_down_reference.invoke(event.key.keysym.sym, event.key.keysym.mod);
            break;
        case SDL_KEYUP:
            on_key_up_reference.invoke(event.key.keysym.sym, event.key.keysym.mod);
            break;
        case SDL_TEXTINPUT:
            on_text_enter_reference.invoke(std::string{event.text.text});
            break;
    }
}
