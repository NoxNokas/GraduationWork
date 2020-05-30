#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Menu)
{
	ui->setupUi(this);

	serialPort = new QSerialPort(this);
	file = new QFile(this);

	//Заполняем комбо-бокс активными COM-портами
	foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
		{
			ui->cmbPort->addItem(serialPortInfo.portName());
		}
	//Заполняем комбо-бокс стандартным баудрейтом
	foreach (const qint32 &serialPortInfo, QSerialPortInfo::standardBaudRates())
		{
			ui->cmbBaudRates->addItem(QString::number(serialPortInfo));
		}
	ui->cmbBaudRates->setCurrentIndex(12);


	//Создание и проверка созданной директории
	dirName = QDir::homePath() + "/documents/DiplomDir";
	if (dir.mkdir(dirName))
	{
		QMessageBox::information(this, "Успех", "Директория создана"+ dirName);
	}
	QDir::setCurrent(dirName);


	//Создание файла
	QString fileName =
			QTime::currentTime().toString().replace(QRegExp("[^\\w]"), "-") + " " +
			QString::number(QDate::currentDate().day()) + '.' +
			QString::number(QDate::currentDate().month()) + '.' +
			QString::number(QDate::currentDate().year()) + ".txt";
	if (!QFile(fileName).exists())
	{
		file->setFileName(fileName);
		file->open(QIODevice::WriteOnly | QIODevice::Text);
	}
	else
	{
		QMessageBox::warning(this, "Ошибка создания", "Не удалось создать текстовый файл для записи данных.");
	}
}

Menu::~Menu()
{
	file->close();
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
	hide();
}

void Menu::on_refreshButton_clicked()
{
	hide();
}
