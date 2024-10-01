#include "project_pch.h"
#include "mytreewidget.h"

#include "Editors/abstractpropertyitem.h"


MyTreeWidget::MyTreeWidget(QWidget *parent):
    QTreeWidget(parent),
    m_isReadOnly(0)
{}

void MyTreeWidget::setReadOnly(bool *_isReadOnly)
{
    m_isReadOnly = _isReadOnly;
}

bool MyTreeWidget::edit(const QModelIndex &index, QAbstractItemView::EditTrigger trigger, QEvent *event)
{
    if(index.column() != 1){return false;}

    QVariant var = index.data(Qt::UserRole);
    QObject *obj =  ObjectHelper::getObject(var, false);

    AbstractPropertyItem *propItem = dynamic_cast<AbstractPropertyItem*>(obj);
    if(!propItem) return 0;
    if(propItem->getReadOnly() && !propItem->isSpecialReadOnlyMode()) return 0;
    if(m_isReadOnly && *m_isReadOnly && !propItem->isSpecialReadOnlyMode()) return 0;

    if(propItem->isDialog())
    {
        QScopedPointer<QDialog> dialog(dynamic_cast<QDialog*>(propItem->createEditor(this)));
        R_ASSERT_X(dialog, "QDialog *dialog == 0");

        propItem->onSetReadOnly(dialog.data(), *m_isReadOnly);
        propItem->setEditorData(dialog.data());
        propItem->updateGeometry(dialog.data(), QStyleOptionViewItem());
        if(dialog->exec() == QDialog::Accepted)
        {
            propItem->saveEditorData(dialog.data());
            propItem->updateTextValue();
        }
        propItem->onSaveEditorGeometry(dialog.data());
        return true;
    } else
    {
        return QTreeWidget::edit(index, trigger, event);
    }
}
