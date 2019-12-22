cmake_minimum_required(VERSION 3.15)
project(cwk2)


set(CMAKE_CXX_STANDARD 14)

#打开Qt的MOC功能和UI文件处理功能
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR  ON)

#set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.12.0/lib/cmake")
find_package(Qt5 COMPONENTS Widgets Multimedia MultimediaWidgets Network Xml Gui REQUIRED)


#add_executable(project1 main.cpp)
set(SOURCE_FILES tomeo.cpp the_player.cpp the_player.h the_button.cpp the_button.h PlayerSlider.cpp PlayerSlider.h buttom_label.cpp buttom_label.h)
add_executable(cw2 ${SOURCE_FILES})

target_link_libraries(cw2 Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets Qt5::Network Qt5::Xml Qt5::Gui)


#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

