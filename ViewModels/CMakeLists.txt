add_library(ViewModels
    MainViewModel.h
    MainViewModel.cpp
    StrategiesViewModel.h
    StrategiesViewModel.cpp
    OrdersViewModel.h
    OrdersViewModel.cpp
    DataReceiver.h
    DataReceiver.cpp


)

target_include_directories(ViewModels
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ViewModels
    Qt${QT_VERSION_MAJOR}::Core
    Models
    Simulation
)
