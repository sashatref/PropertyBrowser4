#pragma once

#include <QWidget>

#include "../../export.h"

namespace Ui {
class OpenFileWidget;
}

class PROPERTYBROWSER3_EXPORT OpenFileWidget : public QWidget
{
    Q_OBJECT
public:
    enum
    {
        SaveFile,
        OpenFile,
        SaveDir,
        OpenDir
    };

    explicit OpenFileWidget(QWidget *parent = 0);
    ~OpenFileWidget();

    void setPath(const QString &_path);
    QString getPath() const;

    void setReadOnly(bool _isReadOnly);

    void setDialogCaption(const QString &_caption);
    void setDefaultDir(const QString &_dir);

    void setDialogType(int _dialogType);
    void setFilter(const QString &_filter);

    void setOptions(int _options);

private slots:
    void on_toolButton_clicked();
    void showSelectedResourceDialog();

private:
    Ui::OpenFileWidget *ui;
    QMenu *m_menu = new QMenu(this);

    QString m_dialogCaption;
    QString m_defaultDir;
    QString m_filter;
    int m_options;
    int m_diglogType;
};
