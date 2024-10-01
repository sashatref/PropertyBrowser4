#pragma once

#include "../abstractpropertyitem.h"

class TimePropertyItem : public AbstractPropertyItem
{
public:
    TimePropertyItem();

    // AbstractPropertyItem interface
public:
    virtual QWidget *createEditor(QWidget *_parent) override;
    virtual void setEditorData(QWidget *_widget) override;
    virtual void saveEditorData(QWidget *_widget) override;
    virtual void updateTextValue() override;
};
