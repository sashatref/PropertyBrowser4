#pragma once

#include <QMap>
#include <QVariant>
#include <QWidget>
#include <functional>
#include <QUndoView>
#include <QDir>

#include <HelperLibrary/Widgets/isavewidget.h>
#include <HelperLibrary/objectfactory.h>

#include "propertyinfo.h"
#include "export.h"

#include "Editors/abstractpropertyitem.h"


class QTreeWidgetItem;

namespace Ui {
class PropertyBrowser3;
}

class AbstractPropertyItem;
class PropertyBrowser3_P;
class DefaultPropertyItem;

class PROPERTYBROWSER3_EXPORT PropertyBrowser3 :
        public QWidget,
        public ISaveWidget
{
    PropertyBrowser3_P *const d;
    Ui::PropertyBrowser3 *ui;

    friend class PropertyBrowser3_P;
    friend class DefaultPropertyItem;

    Q_OBJECT
    Q_PROPERTY(bool descriptionVisible READ getDescriptionVisible WRITE setDescriptionVisible)
    Q_PROPERTY(bool multiObjectListVisible READ getMultiObjectListVisible WRITE setMultiObjectListVisible)
    Q_PROPERTY(bool dragAndDropEnable READ getDragAndDropEnable WRITE setDragAndDropEnable)
    Q_PROPERTY(bool searchLineVisible READ getSearchLineVisible WRITE setSearchLineVisible)
    Q_PROPERTY(QFont treeFont READ getTreeFont WRITE setTreeFont)
    Q_PROPERTY(QFont listFont READ getListFont WRITE setListFont)
    Q_PROPERTY(QFont descriptionFont READ getDescriptionFont WRITE setDescriptionFont)
    Q_PROPERTY(bool addButtonEnable READ getAddButtonEnable WRITE setAddButtonEnable)
    Q_PROPERTY(bool removeButtonEnable READ getRemoveButtonEnable WRITE setRemoveButtonEnable)
    Q_PROPERTY(bool controlPanelVisible READ getControlPanelVisible WRITE setControlPanelVisible)

    Q_PROPERTY(bool labelVisible READ getLabelVisible WRITE setLabelVisible)
    Q_PROPERTY(QString labelText READ getLabelText WRITE setLabelText)
    Q_PROPERTY(QFont labelFont READ getLabelFont WRITE setLabelFont)
    Q_PROPERTY(int labelMargin READ getLabelMargin WRITE setLabelMargin)

    Q_PROPERTY(bool readOnly READ getReadOnly WRITE setReadOnly)
    Q_PROPERTY(int configLineVisibility READ getConfigLineVisibility WRITE setConfigLineVisibility)
public:
    static ObjectFactory<AbstractPropertyItem, int> m_factory;

    static void registerType();

    void setSingleRowColor(const QString &_propertyName, const QColor &_color);
    void clearUndoList();

    PropertyBrowser3(QWidget *parent = 0);
    ~PropertyBrowser3();

    void closeOpenedEditor();

    bool checkObject(); //вызывает для класса виртуальным метод checkObject();

    int getConfigLineVisibility() const;
    void setConfigLineVisibility(int _value);

    bool getReadOnly() const;
    void setReadOnly(bool _isReadOnly);

    bool getLabelVisible() const;
    void setLabelVisible(bool _isVisible);

    QString getLabelText() const;
    void setLabelText(const QString &_text);

    QFont getLabelFont()const;
    void setLabelFont(const QFont &_font);

    int getLabelMargin() const;
    void setLabelMargin(int _margin);

    void setSearchLineVisible(bool _isVisible);
    bool getSearchLineVisible() const;

    void setAddButtonEnable(bool _isEnable);
    bool getAddButtonEnable() const;

    void setRemoveButtonEnable(bool _isEnable);
    bool getRemoveButtonEnable() const;

    void setControlPanelVisible(bool _isVisible);
    bool getControlPanelVisible() const;

    void setCallBackObject(QObject *const _object);

    bool getDragAndDropEnable() const;
    void setDragAndDropEnable(bool _isEnable);

    QVariant getSelectedObject() const;
    void selectRowWhere(std::function<bool(const QVariant&)> _callback);

    QVariant getVariant() const;
    void setVariantList(const QVariantList &_valueList);
    QVariantList getVariantList() const;
    void setVariant(const QVariant &_value);

    template<class T>
    void setVariant(const T &_value)
    {
        setVariant(QVariant::fromValue(_value));
    }

    /*!
     * \brief задает режим отображения окна подробного описания свойства
     */
    void setDescriptionVisible(bool _isVisible);

    /*!
     * \brief получает режим отображение окна подробного описания свойства
     */
    bool getDescriptionVisible() const;

    /*!
     * \brief задает режим отображения списка объектов для редактирования, создания и удаления
     */
    void setMultiObjectListVisible(bool _isVisible);

    /*!
     * \brief получает режим отображение списка объектов для редактирования, создания и удаления
     */
    bool getMultiObjectListVisible() const;

    /*!
     * \brief устанавливает шрифт для окна редактирования свойств объекта
     */
    void setTreeFont(const QFont &_font);

    /*!
     * \brief получает шрифт окна редактирования свойств объекта
     */
    const QFont &getTreeFont() const;

    /*!
     * \brief устанавливает шрифт для окна подробного описания свойств
     */
    void setDescriptionFont(const QFont &_font);

    /*!
     * \brief получает шрифт для окна подробного описания свойств
     */
    const QFont &getDescriptionFont() const;

    /*!
     * \brief задает шрифт для списка объектов
     */
    void setListFont(const QFont &_font);

    /*!
     * \brief получает шрифт для списка объектов
     */
    const QFont &getListFont() const;

    /*!
     * \brief возвращает указатель на заданное свойство. если свойство указано неверно, будет возвращен 0
     * \param _propertyName имя свойства, которое нужно получить
     * \return
     */
    AbstractPropertyItem *getProperty(const QString &_propertyName);

    /*!
     * \brief перевод на лету
     * будет вызвана функция OnGetObjectPropertyInfo у зарегестрированого слушателя, чтобы получить
     * m_propertyInfoMap с переведенными человекопонятными названиями свойств и описания свойств
     */
    void translate();

    /*!
     * \brief проверяет все свойства на правильность заполнения, если установлен флаг isRequried
     * если хотя бы одно свойство заполнено неверно, будет возвращен false, для свойства будет установлен подсвеченный фон
     * и выдан MessageBox с текстом ошибки.
     */
    bool checkTree();

    /*!
     * \brief очищает PropertyBrowser
     */
    void clear();

    /*!
     * \brief для указанного свойства устанавливает флаг ReadOnly
     */
    void setReadOnly(const QString &_propertyName, bool _isReadOnly);

    /*!
     * \brief выделяет все объекты в списке
     */
    void selectAllObjects();

    /*!
     * \brief получает значение указанного свойства, если такого свойства не существует,
     * то будет возвращет QVariant()
     */
    const QVariant &propertyValue(const QString &_propertyName) const;

    /*!
     * \brief задает значени для указанного свойства
     */
    void setPropertyValue(const QString &_propertyName, const QVariant &_value, bool notify = true);

    /*!
     * \brief устанавливает тип, который указывается при вызове колбэк функции на создание нового объекта
     */
    void setCreateObjectType(const int _type);

    /*!
     * \brief получает тип, который указывается при вызове колбэк функции на создание нового объекта
     */
    int getCreateObjectType() const;

signals:
    /*!
     * \brief срабатывает при изменение любого свойства
     */
    void propertyValueChanged(const QString &_propertyName, const QVariant &_value);
    void propertyValueChanged2(const QString &_propertyName, const QVariant &_newValue, const QVariant &_oldValue);

    /*!
     * \brief срабатывает в процессе закрытия окна
     */
    void propertyBrowserClosed();

protected:
    void closeEvent(QCloseEvent *event) override;
    void changeEvent(QEvent *event) override;
    void showEvent(QShowEvent *) override;

public:
    /*!
     * \brief registerBaseTypes регистрирует редакторы для базовых Qt типов
     */
    static void registerBaseTypes();

    static void registerTypeEditor(int _type, std::function<AbstractPropertyItem*()> _createFunc);
    static void registerEnumEditor(int _type);

    template<class Type>
    static void registerEnumEditor()
    {
        registerEnumEditor(qMetaTypeId<Type>());
    }

    //static void registerVariantListEditor(int _type)

    /*!
     * \brief добавляет новый QTreeWidgetItem в дерево и ассоциирует его с AbstractPropertyItem
     * остальные настройки берутся из PropertyInfo
     */
    static AbstractPropertyItem *addItem(const QString &_propertyName,
                                         int _propertyType,
                                         QTreeWidgetItem *_treeItem,
                                         const PropertyInfo &_propInfo,
                                         const QMetaProperty &_metaProperty);

    // ISaveWidget interface
public:
    virtual QString getWidgetUniqueName() const override;
    virtual QVariant saveWidgetState() const override;
    virtual void loadWidgetState(const QVariant &_text) override;
};



