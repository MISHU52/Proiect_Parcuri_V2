cmake_minimum_required(VERSION 3.19)
project(Gestionare_parcuriV2 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)

qt_standard_project_setup()

qt_add_executable(Gestionare_parcuriV2
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    resurse.qrc
)

target_link_libraries(Gestionare_parcuriV2
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)

install(TARGETS Gestionare_parcuriV2
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Gestionare_parcuriV2
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})