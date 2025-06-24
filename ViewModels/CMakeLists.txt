add_library(ViewModels
    MockDataGenerator.h
)

target_include_directories(ViewModels
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ViewModels
    Qt${QT_VERSION_MAJOR}::Core
    Models
)
