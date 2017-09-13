//
// Created by Utkan on 13.09.2017.
//

#include "Box.h"

Box::Box(Window &win, int f_width, int f_height) : Form{win} {
    set_focusable(true);
    width = [f_width]()->int {
        return f_width;
    };
    height = [f_height]()->int {
        return f_height;
    };
}
