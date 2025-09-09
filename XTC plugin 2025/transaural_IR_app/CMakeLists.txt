cmake_minimum_required(VERSION 3.16)

project(transaural_IR_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(transaural_IR_app main.cpp
    appwindow.h appwindow.cpp
    irgenerator.h irgenerator.cpp
    irvisualizer.h irvisualizer.cpp
    irfilemanager.h irfilemanager.cpp
    parameters.h parameters.cpp)

target_link_libraries(transaural_IR_app PRIVATE Qt6::Widgets)
target_link_libraries(transaural_IR_app PRIVATE Qt6::Core)
target_link_libraries(transaural_IR_app PRIVATE Qt6::Widgets)
target_link_libraries(transaural_IR_app PRIVATE Qt6::Core)

include(GNUInstallDirs)
install(TARGETS transaural_IR_app
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
