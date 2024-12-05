cmake_minimum_required(VERSION 3.14)

project(ComputerGraphics2 VERSION 0.1 LANGUAGES CXX)

# Настройки проекта
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем автоматическую обработку Qt-файлов
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Найдем необходимые модули Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Quick Gui Qml Widgets)

# Указываем исходники проекта
set(PROJECT_SOURCES
    main.cpp
    Pencil.h Pencil.cpp
    camera.h camera.cpp
    matrix.h matrix.cpp
    DataModel.h DataModel.cpp
)

# Добавляем исполняемый файл
qt_add_executable(ComputerGraphics2
    ${PROJECT_SOURCES}
)

# Подключаем библиотеки Qt6
target_link_libraries(ComputerGraphics2
    PRIVATE Qt6::Core
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Gui
    PRIVATE Qt6::Qml
    PRIVATE Qt6::Widgets
)

# Указываем каталог для QML
set_target_properties(ComputerGraphics2 PROPERTIES
    QML_IMPORT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/qml"
    QML2_IMPORT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/qml"
)

# Устанавливаем файлы приложения
install(TARGETS ComputerGraphics2
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
