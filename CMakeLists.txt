cmake_minimum_required(VERSION 3.16)

project(StrategyMonitor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Alt modüller:
add_subdirectory(Models)
add_subdirectory(ViewModels)
add_subdirectory(Views)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(StrategyMonitor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(StrategyMonitor SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(StrategyMonitor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(StrategyMonitor
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Models
    ViewModels
    Views
)

set_target_properties(StrategyMonitor PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set_target_properties(StrategyMonitor PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER com.example.StrategyMonitor
    )
endif()

include(GNUInstallDirs)
install(TARGETS StrategyMonitor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(StrategyMonitor)
endif()
