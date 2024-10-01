#pragma once

#include <PropertyBrowserCore/abstractpropertyitem.h>

namespace PropertyBrowser3Qt
{

class ColorPropertyItem : public AbstractPropertyItem
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
