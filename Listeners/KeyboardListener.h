//
// Created by Utkan on 12.09.2017.
//

#ifndef CİTRUS_KEYBOARDLİSTENER_H
#define CİTRUS_KEYBOARDLİSTENER_H


#include "Listener.h"
#include "../Misc/Slot.h"

class KeyboardListener : public Listener {
public:
    KeyboardListener(Slot<int, int>& on_key_down, Slot<int, int>& on_key_up, Slot<std::string>& on_text_enter);

    void receive(SDL_Event &event) override;

private:
    Slot<int, int>& on_key_down_reference;
    Slot<int, int>& on_key_up_reference;
    Slot<std::string>& on_text_enter_reference;
};



#endif //CİTRUS_KEYBOARDLİSTENER_H
