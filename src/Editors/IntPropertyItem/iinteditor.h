#pragma once


class IntPropertyItem;
class IIntEditor : public QObject
{
    Q_OBJECT
public:
    IIntEditor(IntPropertyItem *_parent);

    virtual ~IIntEditor();

    virtual QWidget *createEditor(QWidget *_parent) = 0;
    virtual void setEditorData(QWidget *_widget) = 0;
    virtual void saveEditorData(QWidget *_widget) = 0;
    virtual bool updateTextValue() = 0;

protected:
    IntPropertyItem *m_baseIntEditor;
};

