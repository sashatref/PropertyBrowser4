#include "project_pch.h"
#include "stringpropertyitem.h"

#include "OpenFileWidget.h"

#include "../editorproperties.h"

namespace PropertyBrowser3Qt
{

StringPropertyItem::StringPropertyItem():
    AbstractPropertyItem(QVariant::String)
{
    m_propertiesMap[StringProperty::EditorType] = StringProperty::SimpleText;
    m_propertiesMap[StringProperty::Filter] = "*.*";
    m_propertiesMap[StringProperty::Options] = 0;
    m_propertiesMap[StringProperty::DialogCaption] = tr("Выберите файл...");
    m_propertiesMap[StringProperty::DefaultDirectory] = "";
    m_propertiesMap[StringProperty::ExtEditorMinHeight] = 50;
    m_propertiesMap[StringProperty::ExtEditorMaxHeight] = 130;
    m_propertiesMap[StringProperty::isPassword] = false;
}


//создаем разные типы редакторов, в зависимости от установленных пользователем свойств
QWidget *StringPropertyItem::createEditor(QWidget *_parent)
{
    QWidget* editor = 0;

    int editorType = m_propertiesMap[StringProperty::EditorType].toInt();
    int options = m_propertiesMap[StringProperty::Options].toInt();
    QString filter = m_propertiesMap[StringProperty::Filter].toString();
    QString dialogCaption = m_propertiesMap[StringProperty::DialogCaption].toString();
    QString defaultDir = m_propertiesMap[StringProperty::DefaultDirectory].toString();
    bool isPasswordField = m_propertiesMap[StringProperty::isPassword].toBool();

    if(editorType == StringProperty::SimpleText)
    {
        QLineEdit *lineEdit = new QLineEdit(_parent);
        lineEdit->installEventFilter(this);
        lineEdit->setFrame(false);
        lineEdit->setContextMenuPolicy(Qt::NoContextMenu);
        if(isPasswordField)
        {
            lineEdit->setEchoMode(QLineEdit::Password);
        }
        editor = lineEdit;
    } else if(editorType == StringProperty::ExtendedText)
    {
        QTextEdit *textEditor = new QTextEdit(_parent);
        textEditor->setReadOnly(false);
        textEditor->setWordWrapMode(QTextOption::NoWrap);
        textEditor->setFrameShape(QFrame::Box);
        textEditor->setFrameShadow(QFrame::Plain);
        QFont tempFont = textEditor->font();
        tempFont.setBold(true);
        textEditor->setFont(tempFont);
        editor = textEditor;
    } else if(editorType == StringProperty::OpenFile)
    {
        OpenFileWidget *openFile = new OpenFileWidget(_parent);
        openFile->setOptions(options);
        openFile->setFilter(filter);
        openFile->setDialogCaption(dialogCaption);
        openFile->setDefaultDir(defaultDir);
        openFile->setDialogType(OpenFileWidget::OpenFile);
        editor = openFile;
    } else if(editorType == StringProperty::SaveFile)
    {
        OpenFileWidget *openFile = new OpenFileWidget(_parent);
        openFile->setOptions(options);
        openFile->setFilter(filter);
        openFile->setDialogCaption(dialogCaption);
        openFile->setDefaultDir(defaultDir);
        openFile->setDialogType(OpenFileWidget::SaveFile);
        editor = openFile;
    } else if(editorType == StringProperty::OpenDir)
    {
        OpenFileWidget *openFile = new OpenFileWidget(_parent);
        openFile->setOptions(options);
        openFile->setFilter(filter);
        openFile->setDialogCaption(dialogCaption);
        openFile->setDefaultDir(defaultDir);
        openFile->setDialogType(OpenFileWidget::OpenDir);
        editor = openFile;
    } else if(editorType == StringProperty::SaveDir)
    {
        OpenFileWidget *openFile = new OpenFileWidget(_parent);
        openFile->setOptions(options);
        openFile->setFilter(filter);
        openFile->setDialogCaption(dialogCaption);
        openFile->setDefaultDir(defaultDir);
        openFile->setDialogType(OpenFileWidget::SaveDir);
        editor = openFile;
    }

    return editor;
}

void StringPropertyItem::setEditorData(QWidget *_widget)
{
    int editorType = m_propertiesMap[StringProperty::EditorType].toInt();

    if(editorType == StringProperty::SimpleText)
    {
        QLineEdit *lineEdit = static_cast<QLineEdit*>(_widget);
        lineEdit->setText(getValue().toString());
        lineEdit->deselect();
    } else if(editorType == StringProperty::ExtendedText)
    {
        QTextEdit *textEdit = static_cast<QTextEdit*>(_widget);
        textEdit->setText(getValue().toString());
        textEdit->moveCursor(QTextCursor::End);
    } else if(editorType == StringProperty::OpenFile)
    {
        OpenFileWidget *openFile = static_cast<OpenFileWidget*>(_widget);
        openFile->setPath(getValue().toString());
    } else if(editorType == StringProperty::SaveFile)
    {
        OpenFileWidget *openFile = static_cast<OpenFileWidget*>(_widget);
        openFile->setPath(getValue().toString());
    } else if(editorType == StringProperty::OpenDir)
    {
        OpenFileWidget *openFile = static_cast<OpenFileWidget*>(_widget);
        openFile->setPath(getValue().toString());
    } else if(editorType == StringProperty::SaveDir)
    {
        OpenFileWidget *openFile = static_cast<OpenFileWidget*>(_widget);
        openFile->setPath(getValue().toString());
    }

}

void StringPropertyItem::saveEditorData(QWidget *_widget)
{
    int editorType = m_propertiesMap[StringProperty::EditorType].toInt();

    if(editorType == StringProperty::SimpleText)
    {
        QLineEdit *lineEdit = static_cast<QLineEdit*>(_widget);
        setValue(lineEdit->text());
    } else if(editorType == StringProperty::ExtendedText)
    {
        QTextEdit *textEdit = static_cast<QTextEdit*>(_widget);
        setValue(textEdit->toPlainText());
    } else if(editorType == StringProperty::OpenFile)
    {
        OpenFileWidget *openFile = static_cast<OpenFileWidget*>(_widget);
        setValue(openFile->getPath());
    } else if(editorType == StringProperty::SaveFile)
    {
        OpenFileWidget *openFile = static_cast<OpenFileWidget*>(_widget);
        setValue(openFile->getPath());
    } else if(editorType == StringProperty::OpenDir)
    {
        OpenFileWidget *openFile = static_cast<OpenFileWidget*>(_widget);
        setValue(openFile->getPath());
    } else if(editorType == StringProperty::SaveDir)
    {
        OpenFileWidget *openFile = static_cast<OpenFileWidget*>(_widget);
        setValue(openFile->getPath());
    }


}

bool StringPropertyItem::checkItem()
{
    if(getRequried() && getValue().toString().trimmed().isEmpty())
    {
        return false;
    }
    return true;
}

bool StringPropertyItem::eventFilter(QObject *o, QEvent *e)
{
    if(e->type() == QEvent::FocusIn)
    {
        QLineEdit *editor = static_cast<QLineEdit*>(o);
        editor->deselect();
        QFont tempFont = editor->font();
        tempFont.setBold(true);
        editor->setFont(tempFont);
    }

    return QObject::eventFilter(o, e);
}

void StringPropertyItem::onSetReadOnly(QWidget *_widget, bool _isReadOnly)
{
    int editorType = m_propertiesMap[StringProperty::EditorType].toInt();

    if(editorType == StringProperty::SimpleText)
    {
        QLineEdit *lineEdit = static_cast<QLineEdit*>(_widget);
        lineEdit->setEnabled(!_isReadOnly);
    } else if(editorType == StringProperty::ExtendedText)
    {
        QTextEdit *textEdit = static_cast<QTextEdit*>(_widget);
        textEdit->setReadOnly(_isReadOnly);
    } else if(editorType == StringProperty::OpenFile)
    {
        OpenFileWidget *openFile = static_cast<OpenFileWidget*>(_widget);
        openFile->setReadOnly(_isReadOnly);
    } else if(editorType == StringProperty::SaveFile)
    {
        OpenFileWidget *openFile = static_cast<OpenFileWidget*>(_widget);
        openFile->setReadOnly(_isReadOnly);
    } else if(editorType == StringProperty::OpenDir)
    {
        OpenFileWidget *openFile = static_cast<OpenFileWidget*>(_widget);
        openFile->setReadOnly(_isReadOnly);
    } else if(editorType == StringProperty::SaveDir)
    {
        OpenFileWidget *openFile = static_cast<OpenFileWidget*>(_widget);
        openFile->setReadOnly(_isReadOnly);
    }
}

bool StringPropertyItem::isSpecialReadOnlyMode() const
{
    return true;
}


void StringPropertyItem::updateGeometry(QWidget *_widget, const QStyleOptionViewItem _option)
{
    AbstractPropertyItem::updateGeometry(_widget, _option);
    int editorType = m_propertiesMap[StringProperty::EditorType].toInt();

    if(editorType == StringProperty::ExtendedText)
    {
        int maxHeight = m_propertiesMap[StringProperty::ExtEditorMaxHeight].toInt();
        int minHeight = m_propertiesMap[StringProperty::ExtEditorMinHeight].toInt();

        int width1 = _widget->width();
        int height1 = maxHeight;
        int y1 = _widget->y();

        if(_widget->parentWidget())
        {
            if(_widget->parentWidget()->height() - _widget->y() < maxHeight)
            {
                height1 = _widget->parentWidget()->height() - _widget->y();
            }

            if(height1 < minHeight)
            {
                y1 = y1 - maxHeight + _widget->height();
                height1 = maxHeight;

                if(y1 < 0)
                {
                    y1 = 0;
                    height1 = _widget->y() + _widget->height();
                }
            }
        }
        _widget->setGeometry(_widget->x(), y1, width1, height1);
    }
}


//чтоб из-за текста в несколько строк не увеличивалась высота QTreeWidget
//то для отображения переносы на новую строку убираем
void StringPropertyItem::updateTextValue()
{
    int editorType = m_propertiesMap[StringProperty::EditorType].toInt();
    bool isPasswordField = m_propertiesMap[StringProperty::isPassword].toBool();

    if(editorType == StringProperty::ExtendedText)
    {
        m_treeItem->setText(1, getValue().toString().split("\n").join(""));
    } else
    {
        if(isPasswordField)
        {
            int count = getValue().toString().size();
            QString stars;
            Text::addChars(stars, "●", count);

            m_treeItem->setText(1, stars);
        } else
        {
            AbstractPropertyItem::updateTextValue();
        }
    }
}

}
