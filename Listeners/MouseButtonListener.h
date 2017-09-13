//
// Created by Utkan on 12.09.2017.
//

#ifndef CİTRUS_MOUSEBUTTONLİSTENER_H
#define CİTRUS_MOUSEBUTTONLİSTENER_H


#include "Listener.h"
#include "../Misc/Slot.h"

class MouseButtonListener : public Listener {
public:
    MouseButtonListener(Slot<int, int, int>& on_mouse_down, Slot<int, int, int>& on_mouse_up);

    void receive(SDL_Event &event) override;

private:
    Slot<int, int, int>& on_mouse_down_reference;
    Slot<int, int, int>& on_mouse_up_reference;
};



#endif //CİTRUS_MOUSEBUTTONLİSTENER_H
