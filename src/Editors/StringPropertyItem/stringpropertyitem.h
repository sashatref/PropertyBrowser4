#pragma once

#include "../abstractpropertyitem.h"

namespace PropertyBrowser3Qt
{

class PROPERTYBROWSER3_EXPORT StringPropertyItem : public AbstractPropertyItem
{
public:
    StringPropertyItem();
    virtual QWidget *createEditor(QWidget *_parent) override;
    virtual void setEditorData(QWidget* _widget) override;
    virtual void saveEditorData(QWidget* _widget) override;
    virtual void updateGeometry(QWidget *_widget, const QStyleOptionViewItem _option) override;
    virtual void updateTextValue() override;
    virtual bool checkItem() override;
    virtual void onSetReadOnly(QWidget *_widget, bool _isReadOnly) override;
    virtual bool isSpecialReadOnlyMode() const override;

protected:
    bool eventFilter(QObject *o, QEvent *e);

};

}
