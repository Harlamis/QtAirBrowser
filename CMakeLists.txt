cmake_minimum_required(VERSION 3.16)

project(QtAirBrowser VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Додаємо папку headers у шляхи пошуку
include_directories(headers)

# (Опціонально, якщо хочете, щоб ui_*.h генерувалися коректно при зміні шляхів)
set(CMAKE_AUTOUIC_SEARCH_PATHS forms)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtAirBrowser
        MANUAL_FINALIZATION
        
        # Всі .cpp файли
        sources/main.cpp
        sources/mainwindow.cpp
        sources/register_window.cpp
        sources/BaseUser.cpp
        sources/User.cpp
        sources/Admin.cpp
        sources/AircraftProduct.cpp
        sources/Commercial.cpp
        sources/Fighter.cpp
        sources/AircraftDesigner.cpp
        sources/DatabaseManager.cpp
        sources/dashboard.cpp
        sources/productmanager_window.cpp
        sources/product_editor_dialog.cpp

        # Всі .h файли
        headers/mainwindow.h
        headers/register_window.h
        headers/BaseUser.h
        headers/ISerializable.h
        headers/User.h
        headers/Admin.h
        headers/AircraftProduct.h
        headers/Commercial.h
        headers/Fighter.h
        headers/AircraftDesigner.h
        headers/DatabaseManager.h
        headers/ValidationException.h
        headers/dashboard.h
        headers/productmanager_window.h
        headers/product_editor_dialog.h

        # Всі .ui файли
        forms/mainwindow.ui
        forms/register_window.ui
        forms/dashboard.ui
        forms/productmanager_window.ui
        forms/product_editor_dialog.ui
        
        # Ресурси
        rcs/images.qrc
    )
else()
    # Для старого Qt (Android/Qt5) - теж треба оновити шляхи!
    if(ANDROID)
        add_library(QtAirBrowser SHARED
            sources/main.cpp
            # ... додайте всі файли сюди так само ...
        )
    else()
        add_executable(QtAirBrowser
            sources/main.cpp
            sources/mainwindow.cpp
            # ... додайте всі файли сюди так само, якщо плануєте збірку під Qt5 ...
            # (Але якщо тільки Qt6, можна залишити як є, воно просто не спрацює)
        )
    endif()
endif()

target_link_libraries(QtAirBrowser PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QtAirBrowser)
endif()
set_target_properties(QtAirBrowser PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QtAirBrowser
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtAirBrowser)
endif()
