#pragma once

#ifdef _DEBUG
    #ifdef USE_VLD
        #include <vld.h>
    #endif
#endif

#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QColorDialog>
#include <QDateEdit>
#include <QScrollBar>
#include <QKeyEvent>
#include <QApplication>
#include <QClipboard>
#include <QFontDialog>
#include <QFileDialog>
#include <QPainter>
#include <QLineEdit>
#include <QTextEdit>
#include <QMimeData>
#include <QMessageBox>
#include <QMenu>
#include <QDebug>
#include <QUndoStack>
#include <QMetaProperty>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QTreeWidgetItem>

#include <HelperLibrary/iobject.h>
#include <HelperLibrary/igadget.h>
#include <HelperLibrary/ivariant.h>
#include <HelperLibrary/Widgets/widgethelper.h>
#include <HelperLibrary/Widgets/extendedwidget.h>
#include <HelperLibrary/Widgets/extendedmainwindow.h>
#include <HelperLibrary/Widgets/layoutsaver.h>
#include <HelperLibrary/Widgets/dialogwrapper.h>

#include <HelperLibrary/converterfunctions.h>
#include <HelperLibrary/functions.h>
#include <HelperLibrary/releaseassert.h>
#include <HelperLibrary/Styles/iconsenum.h>
#include <HelperLibrary/Serialization/serializer.h>
#include <HelperLibrary/Logger/loggermacro.h>
#include <HelperLibrary/anymacro.h>
#include <HelperLibrary/Resources/resourceexplorerdialog.h>
#include <HelperLibrary/Decorator/basedecorator.h>
#include <HelperLibrary/Widgets/VariantMapEditor/VariantMapEditor.h>

