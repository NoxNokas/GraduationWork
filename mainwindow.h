#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QCoreApplication>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QFile>
#include <QTime>
#include "qcustomplot.h"
#include <QString>
#include <QChar>

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
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void serialRecieve();	//getting data
	void drawPlot();

private:
	Ui::MainWindow *ui;
	QSerialPort *serialPort;
	QString data;
	QStringList list;
	QVector <QVector <double> > dataForPlot;
	QFile file;
	QTimer* plotTimer;
	const int maxState = 500;
};
#endif // MAINWINDOW_H
