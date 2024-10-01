#pragma once
#include <QDialog>

namespace Ui {
class LoadFilesWidget;
}

class FileItemDelegate;
class LoadFilesWidget : public QDialog
{
    Q_OBJECT

public:
    explicit LoadFilesWidget(QWidget *parent = 0);
    ~LoadFilesWidget();

    void setReadOnly(bool _isReadOnly);

    void addStringList(const QStringList &_fileList);
    QStringList getStringList() const;

    void setSettings(const QString &_dialogCaption,
                     const QString &_filter,
                     const QString &_defaultDir,
                     int _options);

private slots:
    void on_removeAllButton_clicked();
    void on_addButton_clicked();
    void on_openButton_clicked();

    void on_actionRemoveDuplicates_triggered();
    void on_actionRemoveItem_triggered();
    void on_cancelButton_clicked();
    void on_applyButton_clicked();

private:
    Ui::LoadFilesWidget *ui;
    FileItemDelegate *m_delegate;

    QString m_dialogCaption;
    QString m_filter;
    QString m_defaultDir;
    int m_options;

    QStringList getFiles();


    // QObject interface
protected:
    virtual bool eventFilter(QObject *o, QEvent *e) override;
};
