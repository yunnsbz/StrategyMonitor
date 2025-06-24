add_library(Views
)

target_include_directories(Views
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Views
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    Models
)
