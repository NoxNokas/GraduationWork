#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QDir>
#include <QDateTime>
#include <QMessageBox>
namespace Ui {
class Menu;
}

class Menu : public QDialog
{
	Q_OBJECT

public:
	explicit Menu(QWidget *parent = nullptr);
	~Menu();
	QString portName();
	int numberMeasurement();
	qint32 baudRate();
	QSerialPort* getSerialPort() { return serialPort; }
	QFile* getFile() { return file; }

private slots:
	void on_acceptButton_clicked();
	void on_refreshButton_clicked();

private:
	Ui::Menu *ui;
	QSerialPort *serialPort;
	QDir dir;
	QString dirName;
	QFile* file;
};

#endif // MENU_H
