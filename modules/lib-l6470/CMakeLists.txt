project(l6470)

add_library(l6470 STATIC
    src/autodriver.cpp
    src/autodriverprint.cpp
    src/l6470.cpp
    src/l6470commands.cpp
    src/l6470config.cpp
    src/l6470dump.cpp
    src/l6470support.cpp
)

target_include_directories(l6470 PUBLIC include)
