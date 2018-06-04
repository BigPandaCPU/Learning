#ifndef MYWIDGET_H
#define  MYWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QCloseEvent>
#include <QObject>
class MyWidget : public QWidget
{
	Q_OBJECT
public:
	explicit MyWidget( QWidget *parent = 0 );
	~MyWidget();
	void setIdIndex( int i);

signals:
	void isClosed( int i);
protected:
	void closeEvent( QCloseEvent *);
private:
	int m_pIndex;
};
#endif