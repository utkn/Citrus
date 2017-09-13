//
// Created by Utkan on 13.09.2017.
//

#include "MouseMotionListener.h"

MouseMotionListener::MouseMotionListener(Slot<int, int, int>& on_mouse_move) : m_mouse_move_reference{on_mouse_move} {}

void MouseMotionListener::receive(SDL_Event &event) {
    if(event.type == SDL_MOUSEMOTION) {
        m_mouse_move_reference.invoke(event.motion.state, event.motion.x, event.motion.y);
    }
}
