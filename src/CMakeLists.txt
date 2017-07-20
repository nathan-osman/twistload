configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h")

set(SRC
    download/download.cpp
    download/fragment.cpp
    fs/allocationtask.cpp
    fs/file.cpp
    ui/mainwindow.cpp
    main.cpp
)

add_executable(twistload ${SRC})

set_target_properties(twistload PROPERTIES
    CXX_STANDARD          11
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(twistload PUBLIC
    "${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_libraries(twistload Qt5::Network Qt5::Widgets)

install(TARGETS twistload
    DESTINATION bin
)
