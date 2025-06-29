add_library(Views
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    StrategyItemDelegate.cpp
    StrategyItemDelegate.h
    filterdialog.h filterdialog.cpp filterdialog.ui
    OrderTypeDelegate.h
    OrderTypeDelegate.cpp
    HeaderWithIcons.h
    HeaderWithIcons.cpp

)

target_include_directories(Views
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Views
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    ViewModels
    Shared
)
