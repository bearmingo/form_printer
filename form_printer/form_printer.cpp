#include "form_printer.h"

#include <QtWidgets/QGraphicsItem>
#include "text_form_graphics_item.h"

FormPrinter::FormPrinter(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	graphics_scene_ = new QGraphicsScene();
    // 
    graphics_scene_->setSceneRect(0, 0, 500, 500);
	ui.graphicsView->setScene(graphics_scene_);	
    ui.graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);


	//ui.graphicsView->setSizePolicy(QSizePolicy::Expanding,
	//							   QSizePolicy::Expanding);
	//graphics_scene_->addRect(QRectF(0.0f, 0.0f, 100, 20));

	auto text_item = new QGraphicsSimpleTextItem();
	//text_item->setBrush(QColor(245, 245, 245));
	text_item->setText(QString::fromWCharArray(L"中国工商银行"));
	graphics_scene_->addItem(text_item);

    auto form_item = new TextFormGraphicsItem();
	form_item->setPos(10, 10);
	form_item->setSize(QSize(200, 40));
    form_item->setText(QString::fromWCharArray(L"中国工商银行"));
	graphics_scene_->addItem(form_item);
}

FormPrinter::~FormPrinter()
{

}