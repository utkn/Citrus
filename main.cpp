#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Forms/Form.h"
#include "Window.h"
#include "Forms/HList.h"
#include "Forms/VList.h"
#include "Forms/Label.h"
#include "Forms/Button.h"
#include "Forms/Textbox.h"


class Filler : public Form {
public:
    Filler(Window& win, int f_width, int f_height) : Form{win} {
        set_focusable(true);
        width = [f_width]()->int {
            return f_width;
        };
        height = [f_height]()->int {
            return f_height;
        };
    }
};



int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* win;
    SDL_Renderer* ren;

    SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_SHOWN, &win, &ren);

    Window window{640, 480};
    auto& hl = window.create<HList>();

    auto& f1 = window.create<Button>("SUBMIT!", 16);
    auto& f2 = window.create<VList>();
    auto& f3 = window.create<Filler>(255, 255);

    auto& f2l1 = window.create<Textbox>(16, 100);
    auto& f2l2 = window.create<Label>("sup?!!", 12, SDL_Color{255, 255, 255});
    f2.add_element(f2l1);
    f2.add_element(f2l2);

    hl.add_element(f3);
    hl.add_element(f2);
    hl.add_element(f1);

    bool close = false;
    while(!close) {
        SDL_Event e{};
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) close = true;
            window.handle(e);
        }
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        window.render(ren);
        SDL_RenderPresent(ren);
    }

    return 0;
}