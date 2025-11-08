cmake_minimum_required(VERSION 3.16)

project(PVZ VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia LinguistTools)


set(TS_FILES PVZ_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PVZ
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources.qrc # 资源文件
        plant.h plant.cpp
        zombie.h zombie.cpp
        other.h other.cpp
        sunflower.h sunflower.cpp
        sun.h sun.cpp
        shop.h shop.cpp
        card.h card.cpp
        peashooter.h peashooter.cpp
        cherrybomb.h cherrybomb.cpp
        pea.h pea.cpp
        wallnut.h wallnut.cpp
        snowpea.h snowpea.cpp
        potatomine.h potatomine.cpp
        repeater.h repeater.cpp
        basiczombie.h basiczombie.cpp
        conezombie.h conezombie.cpp
        bucketzombie.h bucketzombie.cpp
        screenzombie.h screenzombie.cpp
        footballzombie.h footballzombie.cpp
        mower.h mower.cpp
        map.h map.cpp
        shovel.h shovel.cpp
        button.h button.cpp
        resources.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PVZ APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(PVZ SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PVZ
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# target_link_libraries(PVZ PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(PVZ PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia
)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.PVZ)
endif()
set_target_properties(PVZ PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 添加应用图标（仅 Windows）
if(WIN32)
    set(WINDOWS_ICON ${CMAKE_CURRENT_SOURCE_DIR}/PVZ.ico)
    set_source_files_properties(${WINDOWS_ICON} PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")
    target_sources(PVZ PRIVATE ${WINDOWS_ICON})
endif()

include(GNUInstallDirs)
install(TARGETS PVZ
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PVZ)
endif()
