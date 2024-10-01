#pragma once

#include <QDialog>

namespace Ui {
class StringListEditor;
}

class StringListEditor : public QDialog
{
    Q_OBJECT

public:
    explicit StringListEditor(QWidget *parent = 0);
    ~StringListEditor();

    void setReadOnly(bool _isReadOnly);

    void setStringList(const QStringList &_list);
    QStringList getStringList() const;

private slots:
    void on_closeButton_clicked();
    void on_applyButton_clicked();

private:
    Ui::StringListEditor *ui;
};
