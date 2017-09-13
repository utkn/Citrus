//
// Created by Utkan on 12.09.2017.
//

#ifndef CİTRUS_LİSTENER_H
#define CİTRUS_LİSTENER_H

#include <SDL2/SDL_events.h>

class Listener {
public:
    virtual void receive(SDL_Event& event) = 0;
    virtual ~Listener() = default;
};


#endif //CİTRUS_LİSTENER_H
