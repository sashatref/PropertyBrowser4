#pragma once

#include <PropertyBrowserCore/abstractpropertyitem.h>

class DoublePropertyItem : public AbstractPropertyItem
{
public:
    DoublePropertyItem();

    virtual QWidget *createEditor(QWidget *_parent) override;
    virtual void setEditorData(QWidget *_widget) override;
    virtual void saveEditorData(QWidget *_widget) override;
    virtual void updateTextValue();
    virtual bool isPermanent() const override;
//    virtual void updateGeometry(QWidget *_widget, const QStyleOptionViewItem _option) override;
};




