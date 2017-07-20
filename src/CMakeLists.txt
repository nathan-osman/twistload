configure_file(configure.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h")

set(SRC
    main.cpp
)

add_executable(twistload ${SRC})

set_target_properties(twistload PROPERTIES
    CXX_STANDARD          11
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(twistload Qt5::Network Qt5::Widgets)

install(TARGETS twistload
    DESTINATION bin
)
