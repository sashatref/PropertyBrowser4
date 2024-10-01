#pragma once

namespace PropertyBrowser3Qt
{
    namespace StringProperty
    {

    enum
    {
        EditorType,         //(int)тип редактора
        Filter,             //(QString)фильтр для QFileDialog                   (OpenFile | SaveFile)
        Options,            //(QFileDialog::Options)опции для QFileDialog       (OpenFile | SaveFile)
        DialogCaption,      //(QString)заголовок для QFileDialog                (OpenFile | SaveFile)
        DefaultDirectory,   //(QString)каталог по-умолчанию для QFileDialog     (OpenFile | SaveFile)
        ExtEditorMinHeight, //(int)максимальная высота редактора текста         (ExtendedText)
        ExtEditorMaxHeight, //(int)минимальная высота редактора текста          (ExtendedText)
        isPassword          //(bool)отображать вместо текста - звездочки        (SimpleText)
    };

    enum //EditorType
    {
        SimpleText,     //обычная строка QLineEdit
        ExtendedText,   //расширенный редактор, для текста
        OpenFile,       //выбрать файл для загрузки
        SaveFile,       //выбрать файл для сохранения
        OpenDir,
        SaveDir
    };

    }

    namespace IntProperty
    {
    enum
    {
        SpinBoxMinimum,
        SpinBoxMaximum,
        DisplayType
    };

    enum
    {
        Default,
        Kb,
        Mb,
        Gb
    };
    }

    namespace ComboProperty {
    enum
    {
        ComboSorting
    };
    }

    namespace DoubleProperty {
    enum
    {
        SpinBoxMinimum,
        SpinBoxMaximum,
        Precision
    };
    }

    namespace FileProperty {
    enum
    {
        OpenFile,
        OpenDirectory
    };

    enum
    {
        DialogType,
        SaveDefaultDir,
        SaveFilter,
        LoadFilter,
        FileSizeLimit
    };
    }

    namespace VariantListProperty
    {
    enum
    {
        CreateObjectType,           //(int) qMetaTypeId типа данных, который будет создан по нажатию на кнопку добавления
        EditorSize                  //(QSize) размер редактора
    };

    }

    namespace VariantMapProperty
    {
    enum
    {
        EditorSize                  //(QSize) размер редактора
    };

    }

    namespace StringListProperty
    {
    enum
    {
        EditorType,         //(int) тип редактора
        EditorSize,         //(QSize) радмер редактора                          (StringListEditor)
        IsDialog,           //(bool) будет ли редактор модальным                (StringListEditor | OpenFiles)
        Filter,             //(QString)фильтр для QFileDialog                   (OpenFiles)
        Options,            //(QFileDialog::Options)опции для QFileDialog       (OpenFiles)
        DialogCaption,      //(QString)заголовок для QFileDialog                (OpenFiles)
        DefaultDirectory   //(QString)каталог по-умолчанию для QFileDialog      (OpenFiles)
    };

    enum //EditorType
    {
        OpenFiles,          //Диалог для выбора списка файлов
        StringListEditor    //редактор списка строк
    };
    }

    namespace ByteArrayProperty
    {
    enum
    {
        EditorSize,             //(QSize)размер редактора
        ArraySize,              //(int)размер данных для редактирования
        DataSizeEditable        //(bool)можно ли пользователю изменять размер данных
    };
    }

    namespace EnumProperty
    {
    enum
    {
        FriendlyNamesMap        //(QVariantMap) названия для элементов выпадающего списка
    };
    }

    namespace FlagsProperty
    {
    enum
    {
        FriendlyNamesMap        //(QVariantMap) названия для элементов списка флагов
    };
    }

}
