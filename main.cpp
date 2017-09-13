#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include "Forms/Form.h"
#include "Window.h"
#include "Forms/HList.h"
#include "Forms/VList.h"
#include "Forms/Label.h"
#include "Forms/Button.h"
#include "Forms/Textbox.h"
#include "Forms/Box.h"


class VMenu : public VList {
public:
    explicit VMenu(Window& win) : VList{win} {
        set_focusable(true);
    }

    Button& new_option(std::string const& label) {
        Button& btn = m_window.create<Button>(std::string{label}, 16);
        add_element(btn);
        btn.width = [this]()->int {
            return this->m_max_width;
        };
        m_option_map.insert(std::make_pair(label, &btn));
        return btn;
    }

    void attach_menu(std::string const& label, VMenu& menu) {
        Button& btn = *m_option_map.at(label);

        menu.set_shown(false);
        menu.x = [&btn]()->int {
            return btn.x() + btn.width();
        };
        menu.y = [&btn]()->int {
            return btn.y();
        };
        add_child(menu);

        btn.on_mouse_down.add([this, label](int, int, int) {
            this->toggle(label);
        });
    }

    void toggle(std::string const& label) {
//        for(auto& pair : m_option_map) {
//            pair.second->set_shown(false);
//        }
        Button& btn = *m_option_map.at(label);
        btn.set_shown(true);
    }

private:
    std::map<std::string, Button*> m_option_map;
};

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* win;
    SDL_Renderer* ren;

    SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_SHOWN, &win, &ren);

    Window window{640, 480};

    auto& menu = window.create<VMenu>();
    menu.new_option("New");
    menu.new_option("Open");
    menu.new_option("Save");

    auto& menu2 = window.create<VMenu>();
    menu2.new_option("Hello!");
    menu2.new_option("Success!");

    menu.attach_menu("New", menu2);

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