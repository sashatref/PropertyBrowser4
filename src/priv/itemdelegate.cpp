#include "project_pch.h"
#include "itemdelegate.h"

#include "Editors/abstractpropertyitem.h"

//FIXME: почему то в некоторых случаях, для ComboType, FlagsType - из QVariant не хочет кастить
//указатели в AbstractPropertyItem*, зато нормально срабатывает с промежуточным QObject*
//нужно разобраться в чем проблема

ItemDelegate::ItemDelegate(bool *_isReadOnly, QObject *parent) :
    QItemDelegate       (parent),
    m_stopSave          (false),
    m_editingNow        (false),
    m_isReadOnly        (_isReadOnly),
    m_editorAddSizeHint (5,5),
    m_editedItem        (0)
{

}

bool ItemDelegate::isEditionNow() const
{
    return m_editingNow;
}

void ItemDelegate::closeEditorIfOpened() const
{
    if(m_editingNow && m_editedItem)
    {
        QTreeWidget *tree = m_editedItem->treeWidget();
        tree->closePersistentEditor(m_editedItem, 1);
    }
}

QWidget *ItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem&, const QModelIndex &index) const
{  
    if(index.column() != 1){return 0;}

    QObject *obj = index.data(Qt::UserRole).value<QObject*>();
    AbstractPropertyItem *propItem = dynamic_cast<AbstractPropertyItem*>(obj);
    if(!propItem) return 0;
    if(propItem->getReadOnly() && !propItem->isSpecialReadOnlyMode()) return 0;
    if(*m_isReadOnly && !propItem->isSpecialReadOnlyMode()) return 0;

    m_editingNow = true;
    m_editedItem = propItem->getTreeItem();

    QWidget *wdg = propItem->createEditor(parent);
    propItem->onSetReadOnly(wdg, *m_isReadOnly || propItem->getReadOnly());
    return wdg;
}

void ItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.column() != 1){return;}

    QObject *obj = index.data(Qt::UserRole).value<QObject*>();
    AbstractPropertyItem *propItem = dynamic_cast<AbstractPropertyItem*>(obj);
    if(!propItem) return;

    propItem->setEditorData(editor);
}

void ItemDelegate::setModelData(QWidget *editor, QAbstractItemModel*, const QModelIndex &index) const
{
    if(index.column() != 1){return;}

    if(!m_stopSave)
    {
        QObject *obj = index.data(Qt::UserRole).value<QObject*>();
        AbstractPropertyItem *propItem = dynamic_cast<AbstractPropertyItem*>(obj);
        if(!propItem) return;
        propItem->saveEditorData(editor);
        propItem->updateTextValue();
        propItem->onSaveEditorGeometry(editor);
    }
}

void ItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() != 1) {return;}

    editor->setGeometry(option.rect);

    QObject *obj = index.data(Qt::UserRole).value<QObject*>();
    AbstractPropertyItem *propItem = dynamic_cast<AbstractPropertyItem*>(obj);
    if(!propItem) return;

    propItem->updateGeometry(editor, option);
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QItemDelegate::sizeHint(option, index) + m_editorAddSizeHint;
}


void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QItemDelegate::paint(painter, option, index);

    if(index.column() != 1){return;}

    QObject *obj = index.data(Qt::UserRole).value<QObject*>();
    AbstractPropertyItem *propItem = dynamic_cast<AbstractPropertyItem*>(obj);
    if(!propItem) return;

    propItem->nonEditorPaint(painter, option);
}


void ItemDelegate::destroyEditor(QWidget *editor, const QModelIndex &index) const
{
    setModelData(editor, 0, index);
    m_editingNow = false;
    m_editedItem = 0;
    QItemDelegate::destroyEditor(editor, index);
}
