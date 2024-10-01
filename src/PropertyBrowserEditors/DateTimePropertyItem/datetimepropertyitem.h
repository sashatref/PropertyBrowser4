#pragma once

#include <PropertyBrowserCore/abstractpropertyitem.h>

class DateTimePropertyItem : public AbstractPropertyItem
{
public:
    DateTimePropertyItem();

    virtual QWidget *createEditor(QWidget *_parent) override;
    virtual void setEditorData(QWidget* _widget) override;
    virtual void saveEditorData(QWidget* _widget) override;
    virtual void updateTextValue() override;
};
