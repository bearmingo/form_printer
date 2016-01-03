#ifndef FORM_PRINTER_H
#define FORM_PRINTER_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsScene>
#include "ui_form_printer.h"

class FormPrinter : public QMainWindow
{
	Q_OBJECT

public:
	FormPrinter(QWidget *parent = 0);
	~FormPrinter();

private:
	QGraphicsScene* graphics_scene_;
	Ui::form_printerClass ui;
};

#endif // FORM_PRINTER_H
