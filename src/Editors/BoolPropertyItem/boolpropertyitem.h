#pragma once

#include "../abstractpropertyitem.h"

namespace PropertyBrowser3Qt
{

class PROPERTYBROWSER3_EXPORT BoolPropertyItem : public AbstractPropertyItem
{
public:
    BoolPropertyItem();

    virtual QWidget *createEditor(QWidget *_parent) override;
    virtual void setEditorData(QWidget* _widget) override;
    virtual void saveEditorData(QWidget* _widget) override;
    virtual void updateTextValue() override;
    virtual void nonEditorPaint(QPainter *_painter, const QStyleOptionViewItem &_option) override;
    virtual bool isPermanent() const override;
    virtual void onSetReadOnly(QWidget *_widget, bool _isReadOnly) override;
    virtual bool isSpecialReadOnlyMode() const override;
};

}
