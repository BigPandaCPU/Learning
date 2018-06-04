#ifndef VIEWALLWIDGET_H
#define VIEWALLWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QCloseEvent>
#include <QObject>
#include "ui_viewallwidget.h"
#include <vtkRenderWindow.h>


class viewAllWidget : public QWidget
{
	Q_OBJECT
public:
	explicit viewAllWidget( QWidget *parent = 0 );
	~viewAllWidget();
	void setIdIndex( int i);
	QVTKWidget *getQVTKWidget();
	void setRenderWindow( vtkRenderWindow *p );
	QCheckBox * getCheckBox1( );
	QCheckBox * getCheckBox2( );
	QCheckBox * getCheckBox3( );
	QCheckBox * getCheckBox4( );
	QCheckBox * getCheckBox5( );
	QCheckBox * getCheckBox6( );
	QSlider   * getSlider1();
	QSlider   * getSlider2();
	QSlider   * getSlider3();
	QSlider   * getSlider4();
	QSlider   * getSlider5();
	QSlider   * getSlider6();


signals:
	void isClosed( int i);
protected:
	void closeEvent( QCloseEvent *);
private:
	int m_pIndex;
	Ui::Form  ui;

};
#endif