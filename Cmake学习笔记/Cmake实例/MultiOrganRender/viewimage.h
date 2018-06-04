#ifndef VIEWIMAGE_H
#define VIEWIMAGE_H

#include <QtWidgets/QMainWindow>
#include "ui_viewimage.h"
#include "mywidget.h"
#include "viewallwidget.h"

#include<Qstring>
#include<vector>
#include<QImage>
#include<QPainter>
#include<QVTKWidget.h>
#include <QMoveEvent>
#include <QEvent>
#include "vtkSmartPointer.h"
#include <QLabel>


class vtkMetaImageReader;
class vtkMarchingCubes;
class vtkPolyDataMapper;
class vtkActor;
class vtkTextActor;
class vtkRenderer;
class vtkRenderWindow;
class vtkRenderWindowInteractor;


class viewImage : public QMainWindow
{
	Q_OBJECT

public:
	viewImage(QWidget *parent = 0);
	~viewImage();

	void setViewLayout( double **Layout, int Size);
	void setRenderer( std::vector< QString > & );
	void setViewColor( std::vector< QString > &, double **Color);

	void setCircleTextInit();
	void configureFileInitialize();

public slots:
	void pushButton_path_clicked();
	void pushButton_load_clicked();
	void pushButton_each_clicked();
	void pushButton_all_clicked();
	void mywidget_closed( int i);
	void lineEdit_changed_slot();
	void closeWidget_slot();

	/// 6个slider发生变化时，对应的槽函数
	void slider1ValueChanged_slot( int i);
	void slider2ValueChanged_slot( int i);
	void slider3ValueChanged_slot( int i);
	void slider4ValueChanged_slot( int i);
	void slider5ValueChanged_slot( int i);
	void slider6ValueChanged_slot( int i);
	
	//// 6个checkbox发生变化时，对应的槽函数
	void checkBox1StatedChanged_slot( int state );
	void checkBox2StatedChanged_slot( int state );
	void checkBox3StatedChanged_slot( int state );
	void checkBox4StatedChanged_slot( int state );
	void checkBox5StatedChanged_slot( int state );
	void checkBox6StatedChanged_slot( int state );

signals:
	void lineEdit_changed();

protected:
	void paintEvent(QPaintEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);

private:
	Ui::viewImageClass ui;
	int                       m_pSize;
	double                    **m_pLayout;              //图像布局
	double                    **m_pColor;               //颜色设置

	QString                   m_pPath;                  //文件路径
	std::vector<QString>      m_pFilePathVector;        //存储绝对文件路径的容器
	std::vector<QString>      m_pOrganNameVector;       //将各个文件所代表的器官名存储到容器中
	double                    *m_pTranparency;         //存储各个器官显示的透明度

	QImage                    m_pImage;

private:
	vtkMetaImageReader          *m_pReader;
	vtkMarchingCubes            *m_pSurface;
	vtkPolyDataMapper           *m_pPolyDataMapper;
	vtkActor                    *m_pActor;
	vtkTextActor                *m_pTextActor;
	vtkRenderer                 *m_pRenderer;
	vtkRenderWindow             *m_pRendererWindow;

	vtkRenderWindow             *m_pRenderWindowEach;

	vtkTextActor                *m_pTextActorAll;
	vtkRenderer                 *m_pRendererAll;
	vtkRenderWindow             *m_pRenderWindowAll;
	vtkRenderWindowInteractor   *m_pRenderWindowInteractorAll;

	

	QVTKWidget                  *m_pQVTKWidget_each;
	QVTKWidget                  *m_pQVTKWidget_all;
	MyWidget                     *m_pWidget_each;
	viewAllWidget                *m_pWidget_all;
	bool                         m_pIsload;        //判断数据是否已经加载
	bool                         m_pIsShowEach;    //判断是否显示each
	bool                         m_pIsShowAll;     //判断是否显示all
	QPoint                       m_pPosi;      //主界面中，当前鼠标点的位置

	/// 添加几个脏器 圆圈显示的
	QPoint                       *m_pPosi_label1;
	QPoint                       *m_pPosi_label2;
	QPoint                       *m_pPosi_label3;
	QPoint                       *m_pPosi_label4;
	QPoint                       *m_pPosi_label5;
	QPoint                       *m_pPosi_label6;
	QPoint                       *m_pPosi_other;



	///// add by wangxiong  ///
	std::vector< vtkMetaImageReader* >  m_pReaderVector;
	std::vector<vtkMarchingCubes*>      m_pSurfaceVector;

	std::vector<vtkPolyDataMapper*>     m_pPolyDataMapperVector;
	std::vector<vtkTextActor*>          m_pTextActorVector;

	std::vector<vtkActor*>              m_pActorVector;
	std::vector<vtkRenderer*>           m_pRendererVector;


	std::vector<QString>                m_pCofigureFileVector;
	std::vector<double>                 m_pConfigureTransparencyVector;
	QPushButton                         *m_pCloseButton;

	      /////     add by wangxiogn 2017/8/24          ////
	///// 添加6个int型变量，用来存储6个slider所对应的 organ的id号 /////
	int                                 m_pIdSlider1;
	int                                 m_pIdSlider2;
	int                                 m_pIdSlider3;
	int                                 m_pIdSlider4;
	int                                 m_pIdSlider5;
	int                                 m_pIdSlider6;

	//// add by wangxiong 2017/08/29   ///
	//////     添加数组用来存储六个器官显示的颜色   /////////
	int                                 m_pOrganColor[6][3];
	std::vector<QString>                m_pOrganNameDisplayVector;

};

#endif // VIEWIMAGE_H
