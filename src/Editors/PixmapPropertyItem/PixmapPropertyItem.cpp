#include "project_pch.h"
#include "PixmapPropertyItem.h"
#include "photouploader.h"

PixmapPropertyItem::PixmapPropertyItem()
{

}

bool PixmapPropertyItem::isDialog() const
{
    return true;
}

QWidget *PixmapPropertyItem::createEditor(QWidget *_parent)
{
    PhotoUploader *widget = new PhotoUploader(_parent);
    return widget;
}

void PixmapPropertyItem::setEditorData(QWidget *_widget)
{
    PhotoUploader *widget = static_cast<PhotoUploader*>(_widget);
    widget->setPixmap(getValue().value<QPixmap>());
}

void PixmapPropertyItem::saveEditorData(QWidget *_widget)
{
    PhotoUploader *widget = static_cast<PhotoUploader*>(_widget);
    setValue(widget->getPixmap());
}

void PixmapPropertyItem::updateGeometry(QWidget *_widget, const QStyleOptionViewItem /*_option*/)
{
    WidgetHelper::setWidgetOnScreenCenter(_widget, _widget->parentWidget(), 600, 600);
}

void PixmapPropertyItem::updateTextValue()
{
    if(!getValue().value<QPixmap>().isNull())
    {
        setValueText(tr("Изображение"));
    } else
    {
        setValueText(tr("Пусто"));
    }
}

