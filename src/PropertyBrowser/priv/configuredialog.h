#pragma once

#include <QDialog>

namespace Ui {
class ConfigureDialog;
}

namespace PropertyBrowser3Qt
{

struct TreeConfInfo
{
    TreeConfInfo(const QFont &_treeFont = QFont(),
                  const QFont &_listFont = QFont(),
                  int _historyCount = 30):
        treeFont        (_treeFont),
        listFont        (_listFont),
        historyCount    (_historyCount)
    {}

    QFont treeFont;
    QFont listFont;
    int historyCount;
};

class ConfigureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigureDialog(QWidget *parent = 0);
    ~ConfigureDialog();

    void setConf(const TreeConfInfo &_info);
    TreeConfInfo getConf() const;

private slots:
    void on_closeButton_clicked();
    void on_applyButton_clicked();
    void on_selectMaintTableFontButton_clicked();
    void on_selectColumnListFontButton_clicked();
    void on_setMainTableFontDefaultBtn_clicked();
    void on_setColumnListFontDefaultBtn_clicked();
    void on_setHistoryCountDefBtn_clicked();

private:
    void updateEditors();
    TreeConfInfo m_conf;

    Ui::ConfigureDialog *ui;
};

}

