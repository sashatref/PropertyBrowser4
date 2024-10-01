#pragma once

#include <QTreeWidget>

class MyTreeWidget : public QTreeWidget
{
public:
    MyTreeWidget(QWidget *parent = 0);
    void setReadOnly(bool *_isReadOnly);

protected:
    bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event);

    bool *m_isReadOnly;
};

