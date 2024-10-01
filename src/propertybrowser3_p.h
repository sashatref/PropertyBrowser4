#pragma once

#include "project_pch.h"

#include "ipropertyinfomap.h"

class IGadget;
class QUndoStack;
class QTreeWidgetItem;
class ItemDelegate;
class AbstractPropertyItem;
class PropertyBrowser3;
class AbstractPropertyItem;


class PropertyBrowser3_P : public QObject
{
    Q_OBJECT
public:
    friend class PropertyBrowser3;
    PropertyBrowser3 *const q;

    PropertyBrowser3_P(PropertyBrowser3 *const _q);
    ~PropertyBrowser3_P();

    void updateStyle();
    void updateLanguage();

    QUndoStack *m_undoStack;

    bool m_isReadOnly;
    int m_createObjectType;             ///<id типа, который будет создаваться по нажатию кнопки "Добавить"
    QTreeWidgetItem *m_topLevelItem;    ///<корневой элемент дерева
    ItemDelegate *m_delegate;           ///<делегат для дерева
    QObject *m_callBackObject2;

    QMap<QString, PropertyInfo> m_propertyInfoMap;          ///<карта подробных настроек для каждого из свойств
    QMap<QString, AbstractPropertyItem*> m_propertyItemMap; ///<карта указателей на созданные редакторы свойств
    QMap<QString, bool> m_expandedState;                    ///<карта состояния свернутости узлов дерева

    //QList<QTreeWidgetItem*> getAllItems();              ///<получить рекурсивно все ветки дерева
    QVariant m_emptyVariant;                            ///<пустое значение qvariant

    QFont m_treeFont;
    QFont m_listFont;
    int m_searchHistoryCount = 100;


    /*!
     * \brief сохраняет состояние развернутых групп в переменную m_expandedState
     */
    void saveExpandedState();

    /*!
     * \brief загружает состояние развернутых групп из перемнной m_expandedState
     */
    void loadExpandedState();

    /*!
     * \brief убирает подсвечивание фона со всех свойств, установленных с помощью setWarning
     */
    void clearWarnings();

    /*!
     * \brief на основе объектов из _valueList и списка общих свойств из _properties
     * устанавливает значения для редакторов, созданных ранее
     * \param _valueList
     * \param _properties
     */
    void updateProperties(const QVariantList &_valueList, const QStringList &_properties, bool sendNotify = true);

    /*!
     * \brief на основе списка свойств все объектов из _valueList создает редакторы для общих свойств
     * \param _valueList
     */
    void createProperties(const QVariantList &_valueList);

    void initListWidget(const QVariantList &_valueList);
    void initVariantList(const QVariantList &_valueList);


    static AbstractPropertyItem *getPropertyItem(QVariant &_var);

private slots:
    void on_actionDefault_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionRedo_clicked();
    void on_actionUndo_clicked();
    void on_actionShowUndoRedoList_clicked(bool isChecked);

    void addButtonClicked();
    void removeButtonClicked();
    void customContextMenu(const QPoint &_point);

    void treeWidgetItemClicked(QTreeWidgetItem *_currentItem, QTreeWidgetItem *_prevItem);
    void listWidgetItemSelectionChanged();
    void valueChanged(const QString &_propertyName, const QVariant &_value);
    void valueChanged2(const QString &_propertyName, const QVariant &_newValue, const QVariant &_oldValue);

    void onSearchTextChanged(const QString &_text);

    void onCofigButtonClicked();

    void applyConf();

    // QObject interface
public:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
};
