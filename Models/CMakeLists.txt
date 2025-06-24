add_library(Models
)

target_include_directories(Models
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Models
    Qt${QT_VERSION_MAJOR}::Core
)
