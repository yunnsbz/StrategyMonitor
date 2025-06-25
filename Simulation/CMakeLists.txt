add_library(Simulation
    MockDataGenerator.cpp
    MockDataGenerator.h

)

target_include_directories(Simulation
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Simulation
    Qt${QT_VERSION_MAJOR}::Core
    Views
    ViewModels
    Models
)
