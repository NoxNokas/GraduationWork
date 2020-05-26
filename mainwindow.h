#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QCoreApplication>



#include <QFile>
#include <QTime>
#include "qcustomplot.h"
#include <QString>
#include <QChar>
#include "menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QDialog
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	void delay(int millisecondsToWait);
	void isPackage(); //if true then good package

private slots:
	void serialRecieve();	//getting data
	void drawPlot();

	void on_menuButton_clicked();

private:
	Ui::MainWindow *ui;
	Menu *menu;

	QString data;
	QStringList list;
	QVector <QVector <double> > dataForPlot;
	QFile file;
	QTimer* plotTimer;
	const int maxState = 500;
};
#endif // MAINWINDOW_H
