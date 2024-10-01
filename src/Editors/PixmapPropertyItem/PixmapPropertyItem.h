#pragma once

#include "../abstractpropertyitem.h"

class PixmapPropertyItem : public AbstractPropertyItem
{
    Q_OBJECT
public:
    PixmapPropertyItem();

    virtual bool isDialog() const Q_DECL_OVERRIDE;
    virtual QWidget *createEditor(QWidget *_parent) Q_DECL_OVERRIDE;
    virtual void setEditorData(QWidget *_widget) Q_DECL_OVERRIDE;
    virtual void saveEditorData(QWidget *_widget) Q_DECL_OVERRIDE;
    virtual void updateGeometry(QWidget *_widget, const QStyleOptionViewItem _option) Q_DECL_OVERRIDE;
    virtual void updateTextValue() Q_DECL_OVERRIDE;
};
