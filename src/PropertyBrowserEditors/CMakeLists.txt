set(PROJECT_NAME PropertyBrowserEditors)

project(${PROJECT_NAME})

set(SOURCES
    project_pch.h
    BoolPropertyItem/boolpropertyitem.h
    BoolPropertyItem/boolpropertyitem.cpp
    ByteArrayPropertyItem/bytearrayeditor.cpp
    ByteArrayPropertyItem/bytearrayeditor.h
    ByteArrayPropertyItem/bytearrayeditor.ui
    ByteArrayPropertyItem/bytearraypropertyitem.cpp
    ByteArrayPropertyItem/bytearraypropertyitem.h
    ByteArrayPropertyItem/chunks.cpp
    ByteArrayPropertyItem/chunks.h
    ByteArrayPropertyItem/commands.cpp
    ByteArrayPropertyItem/commands.h
    ByteArrayPropertyItem/qhexedit.cpp
    ByteArrayPropertyItem/qhexedit.h
    ColorPropertyItem/colorpropertyitem.cpp
    ColorPropertyItem/colorpropertyitem.h
    DatePropertyItem/datepropertyitem.cpp
    DatePropertyItem/datepropertyitem.h
    DateTimePropertyItem/datetimepropertyitem.cpp
    DateTimePropertyItem/datetimepropertyitem.h
    DefaultPropertyItem/defaultpropertyitem.cpp
    DefaultPropertyItem/defaultpropertyitem.h
    DoublePropertyItem/doublepropertyitem.cpp
    DoublePropertyItem/doublepropertyitem.h
    FontPropertyItem/fontpropertyitem.cpp
    FontPropertyItem/fontpropertyitem.h
    # IntPropertyItem/defaultinteditor.cpp
    # IntPropertyItem/defaultinteditor.h
    # IntPropertyItem/enuminteditor.cpp
    # IntPropertyItem/enuminteditor.h
    # IntPropertyItem/flagsinteditor.cpp
    # IntPropertyItem/flagsinteditor.h
    # IntPropertyItem/iinteditor.cpp
    # IntPropertyItem/iinteditor.h
    # IntPropertyItem/intpropertyitem.cpp
    # IntPropertyItem/intpropertyitem.h
    # PixmapPropertyItem/PixmapPropertyItem.cpp
    # PixmapPropertyItem/PixmapPropertyItem.h
    # PixmapPropertyItem/ResizableView/resizableview.cpp
    # PixmapPropertyItem/ResizableView/resizableview.h
    # PixmapPropertyItem/photouploader.cpp
    # PixmapPropertyItem/photouploader.h
    # PixmapPropertyItem/photouploader.ui
    # RectPropertyItem/rectpropertyitem.cpp
    # RectPropertyItem/rectpropertyitem.h
    # SizePropertyItem/sizepropertyitem.cpp
    # SizePropertyItem/sizepropertyitem.h
    # StringListPropertyitem/fileitemdelegate.cpp
    # StringListPropertyitem/fileitemdelegate.h
    # StringListPropertyitem/filelistitem.cpp
    # StringListPropertyitem/filelistitem.h
    # StringListPropertyitem/filelistitem.ui
    # StringListPropertyitem/loadfileswidget.cpp
    # StringListPropertyitem/loadfileswidget.h
    # StringListPropertyitem/loadfileswidget.ui
    # StringListPropertyitem/stringlisteditor.cpp
    # StringListPropertyitem/stringlisteditor.h
    # StringListPropertyitem/stringlisteditor.ui
    # StringListPropertyitem/stringlistpropertyitem.cpp
    # StringListPropertyitem/stringlistpropertyitem.h
    StringPropertyItem/OpenFileWidget.h
    StringPropertyItem/openfilewidget.cpp
    StringPropertyItem/openfilewidget.ui
    StringPropertyItem/stringpropertyitem.cpp
    StringPropertyItem/stringpropertyitem.h
    TimePropertyItem/timepropertyitem.cpp
    TimePropertyItem/timepropertyitem.h
    UrlPropertyItem/urlpropertyitem.cpp
    # VariantListPropertyItem/VariantListPropertyItem.cpp
    # VariantListPropertyItem/VariantListPropertyItem.h
    # VariantMapPropertyItem/VariantMapPropertyItem.cpp
    # VariantMapPropertyItem/VariantMapPropertyItem.h
    PropertyBrowserEditors.h
    PropertyBrowserEditors.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt::Widgets
    PropertyBrowserCore
    CustomStylePlugin
    HelperLibrary
)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}
)
target_precompile_headers(${PROJECT_NAME} PRIVATE project_pch.h)

deployTr()
moveHeaders()

