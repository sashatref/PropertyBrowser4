#include "propertybrowser3plugin.h"
#include "propertybrowser3.h"

PropertyBrowser3Plugin::PropertyBrowser3Plugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}


void PropertyBrowser3Plugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool PropertyBrowser3Plugin::isInitialized() const
{
    return initialized;
}

QWidget *PropertyBrowser3Plugin::createWidget(QWidget *parent)
{
    return new PropertyBrowser3(parent);
}

QString PropertyBrowser3Plugin::name() const
{
    return "PropertyBrowser3";
}

QString PropertyBrowser3Plugin::group() const
{
    return "Custom widgets";
}

QIcon PropertyBrowser3Plugin::icon() const
{
    return QIcon();
}

QString PropertyBrowser3Plugin::toolTip() const
{
    return "";
}

QString PropertyBrowser3Plugin::whatsThis() const
{
    return "";
}

bool PropertyBrowser3Plugin::isContainer() const
{
    return false;
}

QString PropertyBrowser3Plugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"PropertyBrowser3\" name=\"propertyBrowser\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>270</width>\n"
           "    <height>400</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString PropertyBrowser3Plugin::includeFile() const
{
    return "propertybrowser3/propertybrowser3.h";
}
