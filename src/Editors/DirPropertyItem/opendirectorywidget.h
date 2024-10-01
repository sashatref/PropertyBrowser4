#pragma once

#include <QWidget>

namespace Ui {
class OpenDirectoryWidget;
}

class OpenDirectoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OpenDirectoryWidget(QWidget *parent = 0);
    ~OpenDirectoryWidget();

    void setPath(const QString &_path);
    QString getPath() const;

    void setDialogCaption(const QString &_caption);
    void setDefaultDir(const QString &_dir);

private slots:
    void on_toolButton_clicked();

private:
    Ui::OpenDirectoryWidget *ui;

    QString m_dialogCaption;
    QString m_defaultDir;
};
