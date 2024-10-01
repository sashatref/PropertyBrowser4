#pragma once

#include <QWidget>

namespace PropertyBrowser3Qt
{

class ResizableViewPrivate;

/*!
 * \brief Виджет который позволяет отображать QPixmap изображение.
 * при этом изображение меняет размеры при изменение размеров самого виджета.
 * есть возможность установки отступов от краев лево-право-низ-верх
 */

class ResizableView : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QSize margin READ getMarginSize WRITE setMarginSize)
    Q_PROPERTY(QPixmap image READ getPixmap WRITE setPixmap)
public:
    ResizableView(QWidget *parent = 0);
    virtual ~ResizableView();

    /*!
     * \brief задает изображение, которое будет отображаться
     */
    void setPixmap(const QPixmap &_pixmap);

    /*!
     * \brief возвращает изображение, которое отображается на виджете
     */
    QPixmap getPixmap();

    /*!
     * \brief устанавливает отступы размещения изображения на виджете
     */
    void setMarginSize(const QSize &_marginSize);

    /*!
     * \brief возвращает отступы размерещния изображения на виджете
     */
    QSize getMarginSize() const;

    /*!
     * \brief очищает изображение
     */
    void clear();

    void setDefaultSaveName(const QString &_saveFileName);
    QString getDefaultSaveName() const;

protected:
    bool eventFilter(QObject *_object, QEvent *_event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    ResizableViewPrivate *m_private;
};

}


