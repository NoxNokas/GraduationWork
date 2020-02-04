#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	serialPort = new QSerialPort(this);
	data.clear();
	foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
		{
			ui->cmbPort->addItem(serialPortInfo.portName());
		}

	serialPort->setPortName(this->ui->cmbPort->currentText());
	serialPort->setBaudRate(QSerialPort::Baud115200);
	if (!serialPort->open(QIODevice::ReadWrite)) {
			//если подключится не получится то покажем сообщение с ошибкой
			QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
			return;
		}

	file.setFileName("myfile.txt");
	if (!file.open(QIODevice::ReadWrite))
	{
		QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
	}

	//serialPort->flush();
	//delay(5000);
	serialPort->write("i");
	//delay(2000);
	serialPort->write("m");
	connect(serialPort, &QIODevice::readyRead, this, &MainWindow::serialRecieve);
}

MainWindow::~MainWindow()
{
	delete ui;

	//ну и закрываем порт
	serialPort->close();
	delete serialPort;
	file.close();
}

void MainWindow::serialRecieve()
{
	QByteArray temp;  // специальный тип QT для хранения последовательности байтов
	temp.clear();
	temp = data + serialPort->readAll();
	int i = temp.size();
	data.clear();
	data.resize(0);
	while (temp[i] != '\n')
	{
		i--;
		if (i<0) //if no \n then return
		{
			data = temp;
			return;
		}
	}
i++;
	for(int j = 0; j<i;j++)
	{
		data.append(temp[j]);
	}

	file.write(data);
	ui->txtOutput->append(data);
//Запись того, что осталось после строки
	data.clear();
	data.resize(0);
	while(temp.size() - i)
	{
		data.append(temp[i]);
		i++;
	}

}

void MainWindow::delay( int millisecondsToWait )
{
	QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
	while( QTime::currentTime() < dieTime )
	{
		QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
	}
}

void MainWindow::on_pushButton_clicked()
{

}
