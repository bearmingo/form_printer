#include "form_printer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FormPrinter w;
	w.show();

	return a.exec();
}
