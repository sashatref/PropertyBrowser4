#pragma once

#include <QWidget>

namespace Ui {
class FileListItem;
}

class FileListItem : public QWidget
{
    Q_OBJECT

public:
    explicit FileListItem(QWidget *parent = 0);
    ~FileListItem();

    void setPath(const QString &_path);
    QString getPath() const;

    void setSettings(const QString &_dialogCaption,
                     const QString &_filter,
                     const QString &_defaultDir,
                     int _options);

private slots:
    void on_openButton_clicked();

signals:
    void deleteButtonClicked();

private:
    Ui::FileListItem *ui;

    QString m_dialogCaption;
    QString m_filter;
    QString m_defaultDir;
    int m_options;
};
