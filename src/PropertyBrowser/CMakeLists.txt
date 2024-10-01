set(PROJECT_NAME PropertyBrowser4)

project(${PROJECT_NAME} VERSION 1.0.0)

set(SOURCES
    Decorator/decoratorfactory.cpp
    Decorator/decoratorfactory.h
    Decorator/idecoratorbase.cpp
    Decorator/idecoratorbase.h
    Propertybrowser_images.qrc
    export.h
    interfacetool.cpp
    interfacetool.h
    ipropertyinfomap.h
    manageobject.cpp
    manageobject.h
    manageobject.ui
    priv/changepropertycommand.cpp
    priv/changepropertycommand.h
    priv/configuredialog.cpp
    priv/configuredialog.h
    priv/configuredialog.ui
    priv/itemdelegate.cpp
    priv/itemdelegate.h
    priv/mytreewidget.cpp
    priv/mytreewidget.h
    project_pch.h
    propertybrowser.cpp
    propertybrowser.h
    propertybrowser.ui
    propertybrowser_p.cpp
    propertybrowser_p.h
    settingsform.cpp
    settingsform.h
    settingsform.ui
)

if(${PROJECT_NAME}_BUILD_STATIC)
    set(LIB_TYPE STATIC)
else()
    set(LIB_TYPE SHARED)
endif()

add_library(${PROJECT_NAME} ${LIB_TYPE} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        HelperLibrary
        Qt5::Widgets
    PRIVATE
        PropertyBrowserCore
        PropertyBrowserEditors
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
)
target_precompile_headers(${PROJECT_NAME} PRIVATE project_pch.h)
target_compile_definitions(${PROJECT_NAME} PRIVATE "PROPERTYBROWSER3")

if(NOT ${PROJECT_NAME}_BUILD_STATIC)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ".")
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC "${PROJECT_NAME}_BUILD_STATIC")
endif()

deployTr()
makeAI()

