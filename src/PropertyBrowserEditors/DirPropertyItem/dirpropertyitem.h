#pragma once

#include "../abstractpropertyitem.h"

class DirPropertyItem : public AbstractPropertyItem
{
public:
    enum
    {
        DefaultCaption,
        DefaultDir
    };

    DirPropertyItem();

    // AbstractPropertyItem interface

    virtual QWidget *createEditor(QWidget *_parent) override;
    virtual void setEditorData(QWidget *_widget) override;
    virtual void saveEditorData(QWidget *_widget) override;
    virtual void updateTextValue() override;
};

