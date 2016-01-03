#include "text_form_graphics_item.h"
#include <QtGui/QTextOption>
#include <QtGui/QPainter>

TextFormGraphicsItem::TextFormGraphicsItem()
{
}

TextFormGraphicsItem::~TextFormGraphicsItem()
{
}

void TextFormGraphicsItem::setText(const QString& text)
{
    text_ = text;

    //update();
}

void TextFormGraphicsItem::paintContext(QPainter* painter,
                                        const QStyleOptionGraphicsItem* option,
                                        QWidget* widget)
{
    // Draw text
    QTextOption text_option;
    text_option.setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    painter->drawText(this->getDrawingRect(), text_, text_option);
}