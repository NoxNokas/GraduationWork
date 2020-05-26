#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Menu)
{
	ui->setupUi(this);

	serialPort = new QSerialPort(this);

		foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
			{
				ui->cmbPort->addItem(serialPortInfo.portName());
			}
		foreach (const qint32 &serialPortInfo, QSerialPortInfo::standardBaudRates())
			{
				ui->cmbBaudRates->addItem(QString::number(serialPortInfo));
			}
		ui->cmbBaudRates->setCurrentIndex(12);


}

Menu::~Menu()
{
	delete ui;
}

QString Menu::portName()
{
	return ui->cmbPort->currentText();
}

int Menu::numberMeasurement()
{
	return ui->numberMeasurement->value();
}

qint32 Menu::baudRate()
{
	return ui->cmbBaudRates->currentText().toInt();
}

void Menu::on_acceptButton_clicked()
{
	if (!serialPort)
	{
		QMessageBox::warning(this, "Error", serialPort->errorString());
		return;
	}
	serialPort->setPortName(portName());
	serialPort->setBaudRate(baudRate());
	serialPort->open(QIODevice::ReadWrite);
	if (!serialPort)
	{
		QMessageBox::warning(this, "Error", serialPort->errorString());
		return;
	}
	hide();
}

void Menu::on_refreshButton_clicked()
{
	hide();
}
