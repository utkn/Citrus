//
// Created by Utkan on 13.09.2017.
//

#ifndef CİTRUS_TEXTBOX_H
#define CİTRUS_TEXTBOX_H


#include <string>
#include <SDL2/SDL_ttf.h>
#include "Form.h"
#include "../Misc/Slot.h"
#include "../Listeners/KeyboardListener.h"
#include "../Listeners/MouseButtonListener.h"
#include "../Listeners/MouseMotionListener.h"

class Textbox : public Form {
public:
    Textbox(Window& win, int font_size, int box_width);

    ~Textbox() override;

    void draw(SDL_Renderer *renderer) override;

    void put_cursor(int x);
    void move_cursor_right();
    void move_cursor_left();

    void paste();
    void copy();
    void cut();
    void insert_text(std::string text);

    void start_selection();
    void erase_selection();
    std::string extract_selection();
    void end_selection();

    std::string text() const;

    Slot<int, int, int> on_mouse_down;
    Slot<int, int, int> on_mouse_up;
    Slot<int, int, int> on_mouse_move;

    Slot<int, int> on_key_down;
    Slot<int, int> on_key_up;
    Slot<std::string> on_text_enter;
private:
    TTF_Font* m_font;
    std::string m_text;
    KeyboardListener m_keyboard_listener;
    MouseButtonListener m_button_listener;
    MouseMotionListener m_motion_listener;

    int m_left_shift = 0;
    int m_cursor_index = 0;
    int m_selection_start_index = -1;
};



#endif //CİTRUS_TEXTBOX_H
