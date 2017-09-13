//
// Created by Utkan on 13.09.2017.
//

#ifndef CİTRUS_MOUSEMOTİONLİSTENER_H
#define CİTRUS_MOUSEMOTİONLİSTENER_H


#include "Listener.h"
#include "../Misc/Slot.h"

class MouseMotionListener : public Listener {
public:
    explicit MouseMotionListener(Slot<int, int, int>& on_mouse_move);

    void receive(SDL_Event &event) override;
private:
    Slot<int, int, int>& m_mouse_move_reference;
};


#endif //CİTRUS_MOUSEMOTİONLİSTENER_H
