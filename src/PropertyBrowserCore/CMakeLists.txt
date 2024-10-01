set(PROJECT_NAME PropertyBrowserCore)

project(${PROJECT_NAME})

set(SOURCES
    project_pch.h
    abstractpropertyitem.h
    abstractpropertyitem.cpp
    propertyinfo.h
    editorproperties.h
    EditorFactory.h
    EditorFactory.cpp
    interfacetool.h
    interfacetool.cpp
    ipropertyinfomap.h
    Decorator/decoratorfactory.cpp
    Decorator/decoratorfactory.h
    Decorator/idecoratorbase.cpp
    Decorator/idecoratorbase.h
)


add_library(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt5::Widgets
    HelperLibrary
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
)
target_precompile_headers(${PROJECT_NAME} PRIVATE project_pch.h)

deployTr()

