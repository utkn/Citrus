//
// Created by Utkan on 12.09.2017.
//

#ifndef CİTRUS_BUTTON_H
#define CİTRUS_BUTTON_H


#include "Form.h"
#include "Label.h"
#include "../Misc/Slot.h"
#include "../Listeners/MouseButtonListener.h"

class Button : public Form {
public:
    Button(Window& win, std::string&& text, int font_size);

    void draw(SDL_Renderer *renderer) override;

    Slot<int, int, int> on_mouse_down;
    Slot<int, int, int> on_mouse_up;

private:
    SDL_Color m_bg_color{255, 255, 255, 255};
    MouseButtonListener m_button_listener;
    Label& m_label;
};



#endif //CİTRUS_BUTTON_H
