#include "VariantMapPropertyItem.h"

#include "settingsform.h"
#include "propertybrowser3.h"
#include "../editorproperties.h"

VariantMapPropertyItem::VariantMapPropertyItem():
    AbstractPropertyItem(QVariant::Map)
{
    using namespace PropertyBrowser3Qt;

    m_propertiesMap[VariantMapProperty::EditorSize] = QSize(500, 500);
}

QWidget *VariantMapPropertyItem::createEditor(QWidget *_parent)
{
    using namespace HelperLibraryNS;

    VariantMapEditor *editor = new VariantMapEditor(_parent);
    editor->setWindowTitle(getPropertyCaption());
    editor->setWindowModality(Qt::ApplicationModal);

    DialogWrapper *dialog = new DialogWrapper(_parent);
    dialog->setWindowTitle(getPropertyCaption());
    dialog->setWidget(editor);
    return dialog;
}

HelperLibraryNS::VariantMapEditor *castEditor(QWidget *_w)
{
    using namespace HelperLibraryNS;

    DialogWrapper *wrapper = qobject_cast<DialogWrapper*>(_w);
    R_ASSERT(wrapper);

    VariantMapEditor *out = qobject_cast<VariantMapEditor*>(wrapper->getWidget());
    R_ASSERT(out);
    return out;
}

void VariantMapPropertyItem::setEditorData(QWidget *_widget)
{
    castEditor(_widget)->setVariantMap(getValue().toMap());
}

void VariantMapPropertyItem::saveEditorData(QWidget *_widget)
{
    setValue(castEditor(_widget)->getVariantMap());
}

void VariantMapPropertyItem::updateGeometry(QWidget *_widget, const QStyleOptionViewItem /*option*/)
{
    using namespace PropertyBrowser3Qt;

    QSize size = m_propertiesMap[VariantMapProperty::EditorSize].toSize();
    _widget->setGeometry(0,0, size.width(), size.height());
    WidgetHelper::setWidgetOnScreenCenter(_widget, _widget->parentWidget());
}

void VariantMapPropertyItem::updateTextValue()
{
    QString text = tr("Элементов: %1").arg(getValue().toMap().size());
    m_treeItem->setText(1, text);
}

bool VariantMapPropertyItem::isDialog() const {return true;}
