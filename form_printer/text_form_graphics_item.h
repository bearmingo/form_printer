#ifndef __FORM_PRINTER_TEXT_FORM_GRAPHICS_ITEM_H__
#define __FORM_PRINTER_TEXT_FORM_GRAPHICS_ITEM_H__

#include "form_graphics_item.h"

class TextFormGraphicsItem
    : public FormGraphicsItem
{
public:
    TextFormGraphicsItem();
    ~TextFormGraphicsItem();

    void setText(const QString& text);

private:
    virtual void paintContext(QPainter*painter,
                              const QStyleOptionGraphicsItem* option,
                              QWidget* widget);
private:
    QString text_;
};

#endif /* __FORM_PRINTER_TEXT_FORM_GRAPHICS_ITEM_H__ */