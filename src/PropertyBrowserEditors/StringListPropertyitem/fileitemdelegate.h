#pragma once

#include <QItemDelegate>

class FileItemDelegate : public QItemDelegate
{
    Q_OBJECT
    // QAbstractItemDelegate interface
public:
    FileItemDelegate(QObject *parent = 0);

    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setSettings(const QString &_dialogCaption,
                     const QString &_filter,
                     const QString &_defaultDir,
                     int _options);

signals:
    void deleteItem(int row);

private:
    QString m_dialogCaption;
    QString m_filter;
    QString m_defaultDir;
    int m_options;
};

