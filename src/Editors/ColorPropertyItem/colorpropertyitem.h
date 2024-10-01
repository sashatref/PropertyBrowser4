#pragma once

#include "../abstractpropertyitem.h"

namespace PropertyBrowser3Qt
{

class PROPERTYBROWSER3_EXPORT ColorPropertyItem : public AbstractPropertyItem
{
public:
    ColorPropertyItem();
    QWidget *createEditor(QWidget *_parent) override;
    void setEditorData(QWidget* _widget) override;
    void saveEditorData(QWidget* _widget) override;

    bool checkItem() override;
    bool isDialog() const override
    {
        return true;
    }
};

}
