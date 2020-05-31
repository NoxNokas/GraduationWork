#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
	menu = new Menu(this);

	data.clear();

	//Этот connect вместо loop
	connect(menu->getSerialPort(), &QIODevice::readyRead, this, &MainWindow::serialRecieve);




////////////for plot///////////////////////////

	//ui->customPlot->setInteraction(QCP::iRangeZoom,true);   // Включаем взаимодействие удаления/приближения
	//ui->customPlot->setInteraction(QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика
	//plotTimer = new QTimer(this); //создание экземпляра таймера
	//connect(plotTimer, &QTimer::timeout, this, &MainWindow::drawPlot); //привязка события к функции PlaybackStep()
	//plotTimer->start(2000);
}

MainWindow::~MainWindow()
{
	delete ui;

}



//function for update data
void MainWindow::isPackage()
{
	QStringList l_trashList;
	list.clear();
	data += menu->getSerialPort()->readAll();
	data = data.trimmed();
	l_trashList = data.split('\n');
	//from l_trashList in l_goodList
	for(int i = 0; i < l_trashList.size(); i++)
	{
		l_trashList[i] = l_trashList[i].trimmed();
		if (l_trashList[i].startsWith('*') && l_trashList[i].endsWith('#')
				&& l_trashList[i].count(';') + 1 == menu->numberMeasurement())
		{
			l_trashList[i] = l_trashList[i]
					.remove(QChar('*'), Qt::CaseInsensitive)
					.remove(QChar('#'), Qt::CaseInsensitive);
			list.push_back(l_trashList[i]);
		}
	}
	//if last element in l_trashList not equal full package
	if(l_trashList[l_trashList.size()-1][l_trashList.size()-1] == '#')
	{
		data.clear();
	}
	else
	{
		data.clear();
		data = l_trashList[l_trashList.size() - 1];
	}
}



void MainWindow::serialRecieve()
{
	isPackage();
	for(int i = 0; i < list.size(); i++)
	{
		ui->txtOutput->append(list[i]);
		menu->getFile()->write(list[i].toUtf8());
		menu->getFile()->write(QByteArray("\n"));
	}
	drawPlot();
}



void MainWindow::drawPlot(){
	QStringList l_list;
	dataForPlot.resize(menu->numberMeasurement());
	for(int i = 0; i < menu->numberMeasurement(); i++)
	{
		dataForPlot[i].resize(list.size());
	}
	for(int i = 0; i < list.size(); i++)
	{
		l_list = list[i].trimmed().split(';');
		for(int j = 0; j < menu->numberMeasurement(); j++)
		{
			dataForPlot[j][i] = l_list[j].toDouble();
		}
	}

	if(!dataForPlot.first().isEmpty()){
		ui->customPlot->clearGraphs();
		for (int i = 1; i < dataForPlot.size(); i++){
			ui->customPlot->addGraph();		//Добавляем один график в Graph
			//Говорим, что отрисовать нужно график по нашим двум массивам
			ui->customPlot->graph(i-1)->setData(dataForPlot[0], dataForPlot[i]);
			ui->customPlot->graph(i-1)->setPen(QColor(Qt::GlobalColor(i+6)));		//Цвет линии
		}
		ui->customPlot->xAxis->setRange(dataForPlot.first().first(),dataForPlot.first().last());
		ui->customPlot->yAxis->setRange(-90,90);
		ui->customPlot->replot();
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





void MainWindow::on_menuButton_clicked()
{
	//hide();
	menu->exec();
}
