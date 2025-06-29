add_library(Models
    StrategyData.h
    OrderData.h
    StrategyModel.h
    StrategyModel.cpp
    OrderModel.h
    OrderModel.cpp
    OrderFilterProxyModel.h
    OrderFilterProxyModel.cpp
    StrategyFilterProxyModel.h
    StrategyFilterProxyModel.cpp
)

target_include_directories(Models
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Models
    Qt${QT_VERSION_MAJOR}::Core
    Shared
)
