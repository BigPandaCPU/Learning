#include "viewallwidget.h"
#include <QObject>
#include <QCloseEvent>
#include <QFile>

viewAllWidget::viewAllWidget( QWidget *parent ) :QWidget( parent )
{
	ui.setupUi(this);
	m_pIndex = 0;
	
   /////   UI界面初始化
	QFile file("./viewallwidget.css");
	bool isOk = file.open(QFile::ReadOnly);
	if( isOk == true )
	{
		QString stylesheet = QLatin1String( file.readAll() );
		this->setStyleSheet( stylesheet );
		file.close();
	}
	else
	{
		std::cout<<"failed to open the stylesheetfile"<<std::endl;
	}

	this->setStyleSheet("background-color:rgb(238,238,238)");
}

viewAllWidget::~viewAllWidget()
{

}

void viewAllWidget::closeEvent(QCloseEvent *)
{
	close();

	if( m_pIndex == 1 )
	{
		emit isClosed( 1 );
	}

	if( m_pIndex == 2 )
	{
		emit isClosed( 2 );
	}
}

void viewAllWidget::setIdIndex( int i)
{
	m_pIndex = i;
}

QVTKWidget* viewAllWidget::getQVTKWidget() 
{
	return  ui.qvtkWidget;
}

void viewAllWidget::setRenderWindow( vtkRenderWindow *p )
{
	ui.qvtkWidget->SetRenderWindow( p );
}



QCheckBox*  viewAllWidget::getCheckBox1()
{
	return ui.checkBox1;
}
QCheckBox*  viewAllWidget::getCheckBox2()
{
	return ui.checkBox2;
}
QCheckBox*  viewAllWidget::getCheckBox3()
{
	return ui.checkBox3;
}
QCheckBox*  viewAllWidget::getCheckBox4()
{
	return ui.checkBox4;
}
QCheckBox*  viewAllWidget::getCheckBox5()
{
	return ui.checkBox5;
}
QCheckBox*  viewAllWidget::getCheckBox6()
{
	return ui.checkBox6;
}


QSlider * viewAllWidget::getSlider1()
{
	return ui.horizontalSlider1;
}

QSlider * viewAllWidget::getSlider2()
{
	return ui.horizontalSlider2;
}

QSlider * viewAllWidget::getSlider3()
{
	return ui.horizontalSlider3;
}

QSlider * viewAllWidget::getSlider4()
{
	return ui.horizontalSlider4;
}

QSlider * viewAllWidget::getSlider5()
{
	return ui.horizontalSlider5;
}

QSlider * viewAllWidget::getSlider6()
{
	return ui.horizontalSlider6;
}


