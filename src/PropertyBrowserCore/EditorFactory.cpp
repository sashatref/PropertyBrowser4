#include "EditorFactory.h"
#include "interfacetool.h"

ObjectFactory<AbstractPropertyItem, int> EditorFactory::m_factory;

AbstractPropertyItem *EditorFactory::addItem(const QString &_propertyName,
                                             int _propertyType,
                                             QTreeWidgetItem *_treeItem,
                                             const PropertyInfo &_propInfo,
                                             const QMetaProperty &_metaProperty)
{
    using namespace PropertyBrowser3Qt;

    if (!_treeItem)
        return 0;
    QTreeWidgetItem *groupTreeItem = TreeWidgetUtils::findByName(_treeItem, _propInfo.m_group, 0);

    if (!groupTreeItem) {
        if (_propInfo.m_group == "") {
            groupTreeItem = _treeItem;
        } else {
            groupTreeItem = new QTreeWidgetItem(_treeItem);
            groupTreeItem->setText(0, _propInfo.m_group);

            InterfaceTool::applyItemAsGroup(groupTreeItem);
        }
    }

    QTreeWidgetItem *item = new QTreeWidgetItem(groupTreeItem);
    item->setHidden(_propInfo.m_isHidden);
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable
                   | Qt::ItemIsEnabled);
    groupTreeItem->setExpanded(true);

    InterfaceTool::applyItemAsValue(item);

    AbstractPropertyItem *propertyItem = 0;

    if (EditorFactory::m_factory.isRegistered(_propertyType)) {
        propertyItem = EditorFactory::m_factory.create(_propertyType);
    } else {
        // propertyItem = new DefaultPropertyItem();
    }

    if (propertyItem) {
        propertyItem->initProperty(_propertyName, _propInfo, item, _metaProperty);

        if (propertyItem->isPermanent()) {
            QWidget *wdg = propertyItem->createEditor(_treeItem->treeWidget());
            //propertyItem->onSetReadOnly(wdg, d->m_isReadOnly);
            _treeItem->treeWidget()->setItemWidget(item, 1, wdg);
        }
    }

    item->setData(1, Qt::UserRole, QVariant::fromValue(propertyItem));

    return propertyItem;
}
