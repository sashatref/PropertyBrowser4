#pragma once

#include "../abstractpropertyitem.h"

class UrlPropertyItem : public AbstractPropertyItem
{
public:
    virtual QWidget *createEditor(QWidget *_parent) override;
    virtual void setEditorData(QWidget *_widget) override;
    virtual void saveEditorData(QWidget *_widget) override;
    virtual bool checkItem() override;
};

