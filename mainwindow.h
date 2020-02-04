#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QCoreApplication>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QFile>
#include <QTime>

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

private slots:
	void on_pushButton_clicked();
	void serialRecieve(); //getting data

private:
	Ui::MainWindow *ui;
	QSerialPort *serialPort;
	QFile file;
	QString string;
	QByteArray data;
};
#endif // MAINWINDOW_H
