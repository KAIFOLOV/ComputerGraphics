cmake_minimum_required(VERSION 3.14)

project(ComputerGraphics VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Gui Qml Widgets)

# общий набор исходников
set(COMMON_SOURCES
    camera.h camera.cpp
    matrix.h matrix.cpp
    DataModel.h DataModel.cpp
    resources.qrc
)

foreach(_target lab2 lab3 lab4)
    add_executable(${_target} "${_target}.cpp")

    target_sources(${_target} PRIVATE
        ${COMMON_SOURCES}
    )

if(_target STREQUAL "lab2")
    target_sources(${_target} PRIVATE
        Pencil.h Pencil.cpp
    )

elseif(_target STREQUAL "lab3")
    target_sources(${_target} PRIVATE
        Pencil.h Pencil.cpp
        Facets.h Facets.cpp
)

elseif(_target STREQUAL "lab4")
    target_sources(${_target} PRIVATE
        Surface.h Surface.cpp
)
endif()

target_link_libraries(${_target}
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(${_target} PROPERTIES
    QML_IMPORT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/qml"
    QML2_IMPORT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/qml"
)

endforeach()
