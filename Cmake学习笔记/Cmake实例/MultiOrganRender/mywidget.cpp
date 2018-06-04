#include "mywidget.h"
#include <QObject>
#include <QCloseEvent>

MyWidget::MyWidget( QWidget *parent ) :QWidget( parent )
{
	m_pIndex = 0;
}

MyWidget::~MyWidget()
{

}

void MyWidget::closeEvent(QCloseEvent *)
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

void MyWidget::setIdIndex( int i)
{
	m_pIndex = i;
}