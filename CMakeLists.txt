cmake_minimum_required(VERSION 3.8)
project(Citrus)

set(CMAKE_CXX_STANDARD 14)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

set(SOURCE_FILES main.cpp Misc/Relation.h Listeners/Listener.h Misc/Slot.h Forms/Form.cpp Forms/Form.h Window.cpp Window.h Forms/HList.cpp Forms/HList.h Forms/VList.cpp Forms/VList.h Forms/Label.cpp Forms/Label.h Global.h Global.cpp Listeners/MouseButtonListener.cpp Listeners/MouseButtonListener.h Listeners/KeyboardListener.cpp Listeners/KeyboardListener.h Forms/Button.cpp Forms/Button.h Listeners/MouseMotionListener.cpp Listeners/MouseMotionListener.h Forms/Textbox.cpp Forms/Textbox.h)
add_executable(Citrus ${SOURCE_FILES})

target_link_libraries(Citrus sdl2 sdl2_image sdl2_ttf)