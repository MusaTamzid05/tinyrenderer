cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(tinyrenderer)






set(SOURCE_FILES
    src/main.cpp
    src/tgaimage.cpp
    src/render.cpp
    src/model.cpp
    )

add_executable(tinyrenderer  ${SOURCE_FILES})

set_target_properties( tinyrenderer
    PROPERTIES
    CXX_STANDARD 11
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE 1

    )



include_directories( 
    include
    )


target_link_libraries(tinyrenderer)
