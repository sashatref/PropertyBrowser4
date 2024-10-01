#include "plugincollection.h"
#include "propertybrowser3plugin.h"

PluginsCollection::PluginsCollection(QObject*)
{
    widgets.append(new PropertyBrowser3Plugin(this));
}

QList<QDesignerCustomWidgetInterface *> PluginsCollection::customWidgets() const
{
    return widgets;
}
