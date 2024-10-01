set(PROJECT_NAME PropertyBrowser3)

project(${PROJECT_NAME} VERSION 1.0.0)

set(SOURCES
    Decorator/decoratorfactory.cpp 
    Decorator/decoratorfactory.h 
    Decorator/idecoratorbase.cpp 
    Decorator/idecoratorbase.h 
    Editors/BoolPropertyItem/boolpropertyitem.cpp 
    Editors/BoolPropertyItem/boolpropertyitem.h
    Editors/ByteArrayPropertyItem/bytearrayeditor.cpp 
    Editors/ByteArrayPropertyItem/bytearrayeditor.h 
    Editors/ByteArrayPropertyItem/bytearrayeditor.ui
    Editors/ByteArrayPropertyItem/bytearraypropertyitem.cpp 
    Editors/ByteArrayPropertyItem/bytearraypropertyitem.h 
    Editors/ByteArrayPropertyItem/chunks.cpp 
    Editors/ByteArrayPropertyItem/chunks.h 
    Editors/ByteArrayPropertyItem/commands.cpp 
    Editors/ByteArrayPropertyItem/commands.h 
    Editors/ByteArrayPropertyItem/qhexedit.cpp 
    Editors/ByteArrayPropertyItem/qhexedit.h 
    Editors/ColorPropertyItem/colorpropertyitem.cpp 
    Editors/ColorPropertyItem/colorpropertyitem.h 
    Editors/DatePropertyItem/datepropertyitem.cpp 
    Editors/DatePropertyItem/datepropertyitem.h 
    Editors/DateTimePropertyItem/datetimepropertyitem.cpp 
    Editors/DateTimePropertyItem/datetimepropertyitem.h 
    Editors/DefaultPropertyItem/defaultpropertyitem.cpp 
    Editors/DefaultPropertyItem/defaultpropertyitem.h 
    Editors/DoublePropertyItem/doublepropertyitem.cpp 
    Editors/DoublePropertyItem/doublepropertyitem.h 
    Editors/FontPropertyItem/fontpropertyitem.cpp 
    Editors/FontPropertyItem/fontpropertyitem.h 
    Editors/IntPropertyItem/defaultinteditor.cpp 
    Editors/IntPropertyItem/defaultinteditor.h 
    Editors/IntPropertyItem/enuminteditor.cpp 
    Editors/IntPropertyItem/enuminteditor.h 
    Editors/IntPropertyItem/flagsinteditor.cpp
    Editors/IntPropertyItem/flagsinteditor.h
    Editors/IntPropertyItem/iinteditor.cpp 
    Editors/IntPropertyItem/iinteditor.h 
    Editors/IntPropertyItem/intpropertyitem.cpp 
    Editors/IntPropertyItem/intpropertyitem.h 
    Editors/PixmapPropertyItem/PixmapPropertyItem.cpp 
    Editors/PixmapPropertyItem/PixmapPropertyItem.h 
    Editors/PixmapPropertyItem/ResizableView/resizableview.cpp 
    Editors/PixmapPropertyItem/ResizableView/resizableview.h 
    Editors/PixmapPropertyItem/photouploader.cpp 
    Editors/PixmapPropertyItem/photouploader.h
    Editors/PixmapPropertyItem/photouploader.ui         
    Editors/RectPropertyItem/rectpropertyitem.cpp 
    Editors/RectPropertyItem/rectpropertyitem.h 
    Editors/SizePropertyItem/sizepropertyitem.cpp 
    Editors/SizePropertyItem/sizepropertyitem.h 
    Editors/StringListPropertyitem/fileitemdelegate.cpp 
    Editors/StringListPropertyitem/fileitemdelegate.h 
    Editors/StringListPropertyitem/filelistitem.cpp 
    Editors/StringListPropertyitem/filelistitem.h 
    Editors/StringListPropertyitem/filelistitem.ui     
    Editors/StringListPropertyitem/loadfileswidget.cpp 
    Editors/StringListPropertyitem/loadfileswidget.h 
    Editors/StringListPropertyitem/loadfileswidget.ui   
    Editors/StringListPropertyitem/stringlisteditor.cpp 
    Editors/StringListPropertyitem/stringlisteditor.h 
    Editors/StringListPropertyitem/stringlisteditor.ui  
    Editors/StringListPropertyitem/stringlistpropertyitem.cpp 
    Editors/StringListPropertyitem/stringlistpropertyitem.h 
    Editors/StringPropertyItem/OpenFileWidget.h 
    Editors/StringPropertyItem/openfilewidget.cpp 
    Editors/StringPropertyItem/openfilewidget.ui        
    Editors/StringPropertyItem/stringpropertyitem.cpp 
    Editors/StringPropertyItem/stringpropertyitem.h 
    Editors/TimePropertyItem/timepropertyitem.cpp 
    Editors/TimePropertyItem/timepropertyitem.h 
    Editors/UrlPropertyItem/urlpropertyitem.cpp 
    Editors/VariantListPropertyItem/VariantListPropertyItem.cpp 
    Editors/VariantListPropertyItem/VariantListPropertyItem.h 
    Editors/VariantMapPropertyItem/VariantMapPropertyItem.cpp 
    Editors/VariantMapPropertyItem/VariantMapPropertyItem.h 
    Editors/abstractpropertyitem.cpp 
    Editors/abstractpropertyitem.h 
    Editors/editorproperties.h 
    Propertybrowser3_images.qrc
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
    propertybrowser3.cpp 
    propertybrowser3.h 
    propertybrowser3.ui 
    propertybrowser3_p.cpp 
    propertybrowser3_p.h 
    propertyinfo.h 
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
    PRIVATE
    Qt5::Widgets
    HelperLibrary
)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/priv
)
target_precompile_headers(${PROJECT_NAME} PRIVATE project_pch.h)
target_compile_definitions(${PROJECT_NAME} PRIVATE "PROPERTYBROWSER3")

if(NOT ${PROJECT_NAME}_BUILD_STATIC)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ".")
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC "${PROJECT_NAME}_BUILD_STATIC")
endif()

deployTr()
moveHeaders()
aviaNames()
makeAI()

