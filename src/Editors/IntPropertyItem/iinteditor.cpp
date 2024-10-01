#include "iinteditor.h"

#include "intpropertyitem.h"

IIntEditor::IIntEditor(IntPropertyItem *_parent):
    QObject         (_parent),
    m_baseIntEditor (_parent)
{

}

IIntEditor::~IIntEditor()
{

}
