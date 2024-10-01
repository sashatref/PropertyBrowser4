#pragma once

#include <HelperLibrary/objectfactory.h>
#include <PropertyBrowserCore/abstractpropertyitem.h>

class EditorFactory
{
public:
    static ObjectFactory<AbstractPropertyItem, int> m_factory;

    /*!
     * \brief добавляет новый QTreeWidgetItem в дерево и ассоциирует его с AbstractPropertyItem
     * остальные настройки берутся из PropertyInfo
     */
    static AbstractPropertyItem *addItem(const QString &_propertyName,
                                         int _propertyType,
                                         QTreeWidgetItem *_treeItem,
                                         const PropertyInfo &_propInfo,
                                         const QMetaProperty &_metaProperty);
};
