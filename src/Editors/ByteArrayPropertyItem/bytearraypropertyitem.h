#pragma once

#include "../abstractpropertyitem.h"

namespace PropertyBrowser3Qt
{

class PROPERTYBROWSER3_EXPORT ByteArrayPropertyItem : public AbstractPropertyItem
{
public:
    ByteArrayPropertyItem();

    virtual QWidget *createEditor(QWidget *_parent) override;
    virtual void setEditorData(QWidget *_widget) override;
    virtual void saveEditorData(QWidget *_widget) override;
    virtual void updateGeometry(QWidget *_widget, const QStyleOptionViewItem _option) override;
    virtual void updateTextValue();

    virtual bool checkItem() override;

    virtual bool isDialog() const override;
};

}
