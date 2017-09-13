//
// Created by Utkan on 12.09.2017.
//

#ifndef CİTRUS_LABEL_H
#define CİTRUS_LABEL_H


#include <SDL2/SDL_ttf.h>
#include <string>
#include "Form.h"

class Label : public Form {
public:
    Label(Window& win, std::string&& text, int font_size, SDL_Color color = {0, 0, 0});
    ~Label() override;

    void draw(SDL_Renderer *renderer) override;
private:
    SDL_Surface* m_surface = nullptr;
    TTF_Font* m_font = nullptr;
    SDL_Color m_color;
    std::string m_text;
};



#endif //CİTRUS_LABEL_H
