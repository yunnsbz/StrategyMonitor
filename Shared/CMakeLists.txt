add_library(Shared
    strategy_model_roles.h

)

target_include_directories(Shared
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Shared
    Qt${QT_VERSION_MAJOR}::Core
)
