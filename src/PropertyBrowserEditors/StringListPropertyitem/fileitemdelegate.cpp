#include "project_pch.h"
#include "fileitemdelegate.h"
#include "filelistitem.h"

FileItemDelegate::FileItemDelegate(QObject *parent) :
    QItemDelegate       (parent),
    m_dialogCaption     (),
    m_filter            (),
    m_defaultDir        (),
    m_options           (0)
{

}

QSize FileItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QItemDelegate::sizeHint(option, index) + QSize(5,5);
}

QWidget *FileItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
{
    FileListItem *item = new FileListItem(parent);
    return item;
}

void FileItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    FileListItem *item = static_cast<FileListItem*>(editor);
    item->setPath(index.data(Qt::DisplayRole).toString());
    item->setSettings(m_dialogCaption,
                      m_filter,
                      m_defaultDir,
                      m_options);
}

void FileItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    FileListItem *item = static_cast<FileListItem*>(editor);
    model->setData(index, item->getPath(), Qt::DisplayRole);
}

void FileItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
    editor->setGeometry(option.rect);
}

void FileItemDelegate::setSettings(const QString &_dialogCaption, const QString &_filter, const QString &_defaultDir, int _options)
{
    m_dialogCaption = _dialogCaption;
    m_filter = _filter;
    m_defaultDir = _defaultDir;
    m_options = _options;
}
