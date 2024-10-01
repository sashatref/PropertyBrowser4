#pragma once

#include <QItemDelegate>
#include <QTreeWidgetItem>

class ItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ItemDelegate(bool *_isReadOnly, QObject *parent = 0);

    bool isEditionNow() const;
    bool m_stopSave;
    void closeEditorIfOpened() const;

protected:
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void destroyEditor(QWidget *editor, const QModelIndex &index) const override;
private:
    mutable bool m_editingNow;
    bool *m_isReadOnly;
    QSize m_editorAddSizeHint;
    mutable QTreeWidgetItem *m_editedItem;
};

