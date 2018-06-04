#include "viewimage.h"
#include <QFileDialog>
#include <QMessageBox>
#include <vtkMetaImageReader.h>
#include <vtkMarchingCubes.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkPolyDataAlgorithm.h>
#include <vtkImageData.h>
#include <vtkRenderWindow.h>
#include <QTextStream>
#include <QPainter>
#include <QPoint>
#include <QBrush>
#include <QLabel>
#include <QPen>
#include "QVTKWidget.h"
#include <QSize>
#include <QIcon>
#include <QMouseEvent>
#include "vtkSmartPointer.h"
#include <QSettings>
#include <QCheckBox>
#include <QSlider>
#include "QVTKWidget.h"
     

viewImage::viewImage(QWidget *parent)
	: QMainWindow(parent)
{
	
	ui.setupUi(this);
	m_pIdSlider1 = -1;
	m_pIdSlider2 = -1;
	m_pIdSlider3 = -1;
	m_pIdSlider4 = -1;
	m_pIdSlider5 = -1;
	m_pIdSlider6 = -1;

	m_pCloseButton = new QPushButton(this);
	m_pCloseButton->setObjectName(QStringLiteral("closelabel"));
	m_pCloseButton->setGeometry(QRect(680, 0, 20, 20));
	m_pCloseButton->setStyleSheet("background-color:rgb(54,55,60)");

	connect( m_pCloseButton, SIGNAL( pressed()), this, SLOT( closeWidget_slot() ) );


	QPixmap pixmapClose("./Icon/1.png");
	m_pCloseButton->setIcon( QIcon(pixmapClose) );
	m_pCloseButton->setIconSize(QSize(20, 20));

	/// add by wang xiong ///
	 ///  读取配置文件   ///
	
	configureFileInitialize();
	/////////////////////////
	
	m_pWidget_all = NULL;
	m_pWidget_each = NULL;

	QPixmap pixmap("./Icon/icon.png");
	QDir dir;
	std::cout<< dir.currentPath().toLocal8Bit().data()<<std::endl;

	ui.pushButton_path->setIcon(QIcon(pixmap));
	ui.pushButton_path->setIconSize(QSize(50, 45));

	setWindowFlags( Qt::FramelessWindowHint );
	m_pIsload = false;  // 初始化
	m_pIsShowEach = false;
	m_pIsShowAll  = false;

	m_pImage = QImage( 1200, 1000 , QImage::Format_RGB32 );
	m_pImage.fill(QColor(54,55,60));
	this->setFixedSize( this->width(), this->height() );

	//文字和圆圈初始化
	setCircleTextInit();

	// 初始化去当前文件夹下读取数据
	QFile file("filePath.txt");
	bool isOk = file.open( QIODevice::ReadOnly );
	if( true == isOk )
	{
		QTextStream txtInput( &file );
		QString   filePath;
		filePath = txtInput.readAll();

		if(  !filePath.isEmpty()  ) 
		{
			ui.lineEdit_path->setText( filePath );
		}
	}
	file.close();


	connect( ui.pushButton_path, SIGNAL( clicked()), this, SLOT( pushButton_path_clicked() ) );

	connect( ui.pushButton_load, SIGNAL( clicked()), this, SLOT( pushButton_load_clicked() ) );

	connect( ui.pushButton_each, SIGNAL( clicked()), this, SLOT( pushButton_each_clicked() ) );

	connect( ui.pushButton_all,  SIGNAL( clicked()), this, SLOT( pushButton_all_clicked() ) );

	connect( this,   SIGNAL( lineEdit_changed()), this, SLOT( lineEdit_changed_slot() ) );
}

viewImage::~viewImage()
{

}


//  choose file path
void viewImage::pushButton_path_clicked()
{  
	m_pFilePathVector.clear();
	m_pPath = QFileDialog::getExistingDirectory( this, QString::fromLocal8Bit("选择文件路径"),"./");

	if( m_pPath.isEmpty() == true )
		return;
	ui.lineEdit_path->setText( m_pPath );

	QFile file("filePath.txt");
	file.open( QIODevice::WriteOnly );
	file.write( m_pPath.toLocal8Bit().data() );
	file.close();
	emit lineEdit_changed();
}

// load file
void viewImage::pushButton_load_clicked()
{
	m_pOrganNameVector.clear();
	m_pFilePathVector.clear();
	m_pOrganNameDisplayVector.clear();

	m_pPath = ui.lineEdit_path->text();
	QDir dir( m_pPath );

	foreach( QFileInfo mhdFileInfo, dir.entryInfoList( QStringList() << "*.mhd", QDir::Files, QDir::NoSort ) )
	{
		m_pFilePathVector.push_back( mhdFileInfo.absoluteFilePath() ); //获取文件绝对路径名
		std::cout<< mhdFileInfo.baseName().toLocal8Bit().data() <<std::endl;
		m_pOrganNameVector.push_back( mhdFileInfo.fileName().left( mhdFileInfo.fileName().size() - 4 ) );
		
	}
	m_pSize = m_pFilePathVector.size();

	if( m_pSize < 1)
	{
		QMessageBox::warning( this, "Failed", "There is no mhd file in this current file,please change the path!" );
		return;
	}

	m_pTranparency = new double[m_pSize];

	if( !m_pIsload )
	{
		// 布局管理
		m_pIsload = true;
		m_pLayout = new double*[m_pSize];
		for( int i =0; i < m_pSize; i++ )
		{
			m_pLayout[i] = new double[4];
		}
		setViewLayout( m_pLayout, m_pSize );

		// 设置颜色
		m_pColor = new double*[m_pSize];
		for( int i = 0; i < m_pSize ; i++ )
		{
			m_pColor[i] = new double[4];
		}
		setViewColor( m_pOrganNameVector, m_pColor );

		//设置Renderer
		setRenderer( m_pFilePathVector );
	}

}

void  viewImage::pushButton_each_clicked()
{
	if( m_pActorVector.size()< 1  )
	{
		QMessageBox::information( this, "Failed", "You haven't load the data,Please load the data!");
		return;
	}
	if( m_pWidget_each == NULL )
	{
		m_pWidget_each = new MyWidget;

		////// 设置程序标题
		m_pWidget_each->setWindowIcon( QIcon("./Icon/miPlatform.ico") );
		m_pWidget_each->setWindowTitle("View Each");
		////////////////////////////////////////////


		m_pWidget_each->setIdIndex( 1 );

		connect( m_pWidget_each, SIGNAL( isClosed(int)), this, SLOT( mywidget_closed( int)) );

		m_pWidget_each->setGeometry(QRect( 40,40, 1680, 1000));
		m_pWidget_each->setFixedSize( m_pWidget_each->width(), m_pWidget_each->height() );

		m_pQVTKWidget_each = new QVTKWidget( m_pWidget_each );
		m_pQVTKWidget_each->setGeometry(QRect(0, 0, 1680, 1000) );

		m_pRenderWindowEach = vtkRenderWindow::New();

		m_pRenderWindowEach->SetWindowName( "PolyDataMarchingCubes" );
		m_pRenderWindowEach->SetSize( 1280,1080);

		for( int i = 0; i < m_pSize;  i++ )
		{	
			m_pRenderWindowEach->AddRenderer(m_pRendererVector[i] );
		}

		m_pQVTKWidget_each->SetRenderWindow( m_pRenderWindowEach );
		m_pQVTKWidget_each->GetRenderWindow()->Render( );
		m_pWidget_each->show();

	}

}


void viewImage::pushButton_all_clicked()
{

	if( m_pActorVector.size()< 1  )
	{
		QMessageBox::information( this, "Failed", "You haven't load the data,Please load the data!");
		return;
	}



	if(  m_pWidget_all == NULL )
	{
		m_pWidget_all = new viewAllWidget;
		////// 设置程序标题
		m_pWidget_all->setWindowIcon( QIcon("./Icon/miPlatform.ico") );
		m_pWidget_all->setWindowTitle("View All");

		///////// 根据m_pIdSlider的值来初始化 slider 和 checkbox   
		if( m_pIdSlider1 > -1)
		{	
			m_pWidget_all->getSlider1()->setEnabled(true);
			m_pWidget_all->getCheckBox1()->setEnabled(true);
			m_pWidget_all->getCheckBox1()->setChecked(true);
		}

		if( m_pIdSlider2 > -1)
		{	
			m_pWidget_all->getSlider2()->setEnabled(true);
			m_pWidget_all->getCheckBox2()->setEnabled(true);
			m_pWidget_all->getCheckBox2()->setChecked(true);
		}

		if( m_pIdSlider3 > -1)
		{	
			m_pWidget_all->getSlider3()->setEnabled(true);
			m_pWidget_all->getCheckBox3()->setEnabled(true);
			m_pWidget_all->getCheckBox3()->setChecked(true);
		}

		if( m_pIdSlider4 > -1)
		{	
			m_pWidget_all->getSlider4()->setEnabled(true);
			m_pWidget_all->getCheckBox4()->setEnabled(true);
			m_pWidget_all->getCheckBox4()->setChecked(true);
		}

		if( m_pIdSlider5 > -1)
		{	
			m_pWidget_all->getSlider5()->setEnabled(true);
			m_pWidget_all->getCheckBox5()->setEnabled(true);
			m_pWidget_all->getCheckBox5()->setChecked(true);
		}

		if( m_pIdSlider6 > -1)
		{	
			m_pWidget_all->getSlider6()->setEnabled(true);
			m_pWidget_all->getCheckBox6()->setEnabled(true);
			m_pWidget_all->getCheckBox6()->setChecked(true);
		}

		////////////////////////////////////////////

		////////////////  设置label的标签名  //////
		m_pWidget_all->getCheckBox1()->setText( ui.lineEdit_label1->text() );
		m_pWidget_all->getCheckBox2()->setText( ui.lineEdit_label2->text() );
		m_pWidget_all->getCheckBox3()->setText( ui.lineEdit_label3->text() );
		m_pWidget_all->getCheckBox4()->setText( ui.lineEdit_label4->text() );
		m_pWidget_all->getCheckBox5()->setText( ui.lineEdit_label5->text() );
		m_pWidget_all->getCheckBox6()->setText( ui.lineEdit_label6->text() );

		/////////////// 设置slider的初始值   ////
		m_pWidget_all->getSlider1()->setValue( int( m_pConfigureTransparencyVector[0]*100 ) );
        m_pWidget_all->getSlider2()->setValue( int( m_pConfigureTransparencyVector[1]*100 ) );
		m_pWidget_all->getSlider3()->setValue( int( m_pConfigureTransparencyVector[2]*100 ) );
		m_pWidget_all->getSlider4()->setValue( int( m_pConfigureTransparencyVector[3]*100 ) );
		m_pWidget_all->getSlider5()->setValue( int( m_pConfigureTransparencyVector[4]*100 ) );
		std::cout<< m_pConfigureTransparencyVector[5]<<std::endl;
		m_pWidget_all->getSlider6()->setValue( int( m_pConfigureTransparencyVector[5]*100 ) );
		//////////////////////////////////////////


		///////////////////////////      将6个slider的 和对应的 槽函数连接起来      //////////////////////////////
		connect( m_pWidget_all->getSlider1(), SIGNAL( valueChanged(int) ), this, SLOT( slider1ValueChanged_slot(int) ) );
		connect( m_pWidget_all->getSlider2(), SIGNAL( valueChanged(int) ), this, SLOT( slider2ValueChanged_slot(int) ) );
		connect( m_pWidget_all->getSlider3(), SIGNAL( valueChanged(int) ), this, SLOT( slider3ValueChanged_slot(int) ) );
		connect( m_pWidget_all->getSlider4(), SIGNAL( valueChanged(int) ), this, SLOT( slider4ValueChanged_slot(int) ) );
		connect( m_pWidget_all->getSlider5(), SIGNAL( valueChanged(int) ), this, SLOT( slider5ValueChanged_slot(int) ) );
		connect( m_pWidget_all->getSlider6(), SIGNAL( valueChanged(int) ), this, SLOT( slider6ValueChanged_slot(int) ) );
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////     将6个checkbox的stateChanged(int)信号和槽函数连接起来     ///////////////////////
		connect( m_pWidget_all->getCheckBox1(), SIGNAL( stateChanged(int) ), this, SLOT( checkBox1StatedChanged_slot(int)) );
		connect( m_pWidget_all->getCheckBox2(), SIGNAL( stateChanged(int) ), this, SLOT( checkBox2StatedChanged_slot(int)) );
		connect( m_pWidget_all->getCheckBox3(), SIGNAL( stateChanged(int) ), this, SLOT( checkBox3StatedChanged_slot(int)) );
		connect( m_pWidget_all->getCheckBox4(), SIGNAL( stateChanged(int) ), this, SLOT( checkBox4StatedChanged_slot(int)) );
		connect( m_pWidget_all->getCheckBox5(), SIGNAL( stateChanged(int) ), this, SLOT( checkBox5StatedChanged_slot(int)) );
		connect( m_pWidget_all->getCheckBox6(), SIGNAL( stateChanged(int) ), this, SLOT( checkBox6StatedChanged_slot(int)) );
		////////////////////////////////////////////////////////////////////////////////////////////////////////////


		m_pWidget_all->setIdIndex(2);

		connect( m_pWidget_all, SIGNAL( isClosed(int) ), this, SLOT( mywidget_closed( int) ) );

		m_pWidget_all->setGeometry(QRect( 40,40, 1320, 793));
		m_pWidget_all->setFixedSize( m_pWidget_all->width(), m_pWidget_all->height() );

	

		m_pRendererAll = vtkRenderer::New();
		m_pRenderWindowAll = vtkRenderWindow::New();

		for( int i = 0; i < m_pSize ; i++)
		{
			m_pRendererAll->AddActor( m_pActorVector[i] );
		}

		m_pTextActorAll = vtkTextActor::New();
		m_pTextActorAll->SetInput("All");
		m_pTextActorAll->GetTextProperty()->SetFontSize(24);
		m_pTextActorAll->GetTextProperty()->SetColor( 1.0, 0.0, 0.0 );
		m_pRendererAll->AddActor2D( m_pTextActorAll );
		m_pRendererAll->SetBackground(1.0, 1.0, 1.0);

		m_pRenderWindowAll->SetSize(800,600);
		m_pRenderWindowAll->AddRenderer(m_pRendererAll);
		m_pRenderWindowAll->SetWindowName("PolyMarchingCubes");

		m_pRenderWindowAll->StereoUpdate();
        m_pWidget_all->getQVTKWidget()->SetRenderWindow( m_pRenderWindowAll );
		m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		m_pWidget_all->show();
	}

}

void viewImage::setViewLayout(double **Layout, int Size)
{
	double dx;
	if( Size%2 ==0 )
	{
		dx =  2.0 / Size;  //布局为m*2
		for( int i =0; i< Size; i++ )
		{
			Layout[i][0] = ( i/2 ) * dx;
			Layout[i][1] = ( i%2 ) * 0.5;
			Layout[i][2] = ( i/2 +1) * dx;
			Layout[i][3] = ( i%2 +1) * 0.5;
		}
	}
	else
	{
		dx = 2.0 /( Size+1 );
		for( int i=0; i< Size-1 ;i++ )
		{
			Layout[i][0] = ( i/2 ) * dx;
			Layout[i][1] = ( i%2 ) * 0.5;
			Layout[i][2] = ( i/2 +1) * dx;
			Layout[i][3] = ( i%2 +1) * 0.5;
		}
		Layout[Size-1][0] = ( Size-1 )/2 * dx;
		Layout[Size-1][1] = 0;
		Layout[Size-1][2] = ( Size+1 )/2 *dx;
		Layout[Size-1][3] = 1.0;
	}
}

void viewImage::setViewColor(std::vector< QString > &OrganName , double **Color)
{
	QPainter p(&m_pImage);
	QPen   pen;
	pen.setWidth(1);
	pen.setStyle( Qt::SolidLine );
	

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	


	for( int i = 0; i < m_pSize; i++ )
	{
		if( OrganName[i].compare(m_pCofigureFileVector[0], Qt::CaseInsensitive ) ==0 )
		{
			// 前三个表示RGB，第四个表示透明度
			Color[i][0] = m_pOrganColor[0][0]/255.0;  
			Color[i][1] = m_pOrganColor[0][1]/255.0 ;
			Color[i][2] = m_pOrganColor[0][2]/255.0 ;
			Color[i][3] =0.2 ;
			pen.setColor( QColor(m_pOrganColor[0][0],m_pOrganColor[0][1], m_pOrganColor[0][2]));
			brush.setColor( QColor(m_pOrganColor[0][0],m_pOrganColor[0][1], m_pOrganColor[0][2]) );
			p.setPen(pen);
			p.setBrush( brush );

			p.drawEllipse( *m_pPosi_label1, 10, 10 );
			m_pTranparency[i] = m_pConfigureTransparencyVector[0];

			///m_pIdSlider1用来存储对应的Organ在OrganName中的id序号
			m_pIdSlider1 = i;

			m_pOrganNameDisplayVector.push_back( ui.lineEdit_label1->text() );

		}
		else if( OrganName[i].compare( m_pCofigureFileVector[1], Qt::CaseInsensitive ) ==0 )
		{
			// 前三个表示RGB，第四个表示透明度
			Color[i][0] = m_pOrganColor[1][0]/255.0;   
			Color[i][1] = m_pOrganColor[1][1]/255.0;
			Color[i][2] = m_pOrganColor[1][2]/255.0;
			Color[i][3] =0.5 ;
			pen.setColor( QColor(m_pOrganColor[1][0],m_pOrganColor[1][1], m_pOrganColor[1][2]));
			brush.setColor( QColor(m_pOrganColor[1][0],m_pOrganColor[1][1], m_pOrganColor[1][2]) );
			p.setPen(pen);
			p.setBrush( brush );

			p.drawEllipse( *m_pPosi_label2, 10, 10 );
			m_pTranparency[i] = m_pConfigureTransparencyVector[1];


			///m_pIdSlider2用来存储对应的Organ在OrganName中的id序号
			m_pIdSlider2 = i;
			m_pOrganNameDisplayVector.push_back( ui.lineEdit_label2->text() );
		}
		else if( OrganName[i].compare( m_pCofigureFileVector[2], Qt::CaseInsensitive ) ==0 )
		{
			// 前三个表示RGB，第四个表示透明度
			Color[i][0] = m_pOrganColor[2][0]/255.0;   
			Color[i][1] = m_pOrganColor[2][1]/255.0;
			Color[i][2] = m_pOrganColor[2][2]/255.0;
			Color[i][3] = 0.5;
			pen.setColor( QColor(m_pOrganColor[2][0],m_pOrganColor[2][1], m_pOrganColor[2][2]));
			brush.setColor( QColor(m_pOrganColor[2][0],m_pOrganColor[2][1], m_pOrganColor[2][2]) );
			p.setPen(pen);
			p.setBrush( brush );

			p.drawEllipse( *m_pPosi_label3, 10, 10 );
			m_pTranparency[i] = m_pConfigureTransparencyVector[2];

			///m_pIdSlider3用来存储对应的Organ在OrganName中的id序号
			m_pIdSlider3 = i;
			m_pOrganNameDisplayVector.push_back( ui.lineEdit_label3->text() );
		}
		else if( OrganName[i].compare( m_pCofigureFileVector[3], Qt::CaseInsensitive ) ==0 )
		{
			// 前三个表示RGB，第四个表示透明度
			Color[i][0] = m_pOrganColor[3][0]/255.0;
			Color[i][1] = m_pOrganColor[3][1]/255.0;
			Color[i][2] = m_pOrganColor[3][2]/255.0;
			Color[i][3] =0.5 ;

			pen.setColor( QColor( m_pOrganColor[3][0],m_pOrganColor[3][1], m_pOrganColor[3][2] ));
			brush.setColor( QColor( m_pOrganColor[3][0],m_pOrganColor[3][1], m_pOrganColor[3][2] ) );
			p.setPen(pen);
			p.setBrush( brush );
			p.drawEllipse( *m_pPosi_label4, 10, 10 );
			m_pTranparency[i] = m_pConfigureTransparencyVector[3];

			///m_pIdSlider4用来存储对应的Organ在OrganName中的id序号
			m_pIdSlider4 = i;
			m_pOrganNameDisplayVector.push_back( ui.lineEdit_label4->text() );

		}
		else if( OrganName[i].compare( m_pCofigureFileVector[4], Qt::CaseInsensitive ) ==0 )
		{
			// 前三个表示RGB，第四个表示透明度
			Color[i][0] = m_pOrganColor[4][0]/255.0;   
			Color[i][1] = m_pOrganColor[4][1]/255.0;
			Color[i][2] = m_pOrganColor[4][2]/255.0;
			Color[i][3] =0.5 ;
			pen.setColor( QColor( m_pOrganColor[4][0],m_pOrganColor[4][1], m_pOrganColor[4][2] ));
			brush.setColor( QColor( m_pOrganColor[4][0],m_pOrganColor[4][1], m_pOrganColor[4][2] ) );
			p.setPen(pen);
			p.setBrush( brush );
			p.drawEllipse( *m_pPosi_label5, 10, 10 );
			m_pTranparency[i] = m_pConfigureTransparencyVector[4];

			///m_pIdSlider1用来存储对应的Organ在OrganName中的id序号
			m_pIdSlider5 = i;
			m_pOrganNameDisplayVector.push_back( ui.lineEdit_label5->text() );

		}
		else if( OrganName[i].compare( m_pCofigureFileVector[5], Qt::CaseInsensitive ) ==0 )
		{
			// 前三个表示RGB，第四个表示透明度
			Color[i][0] = m_pOrganColor[5][0]/255.0 ;   
			Color[i][1] = m_pOrganColor[5][1]/255.0 ;
			Color[i][2] = m_pOrganColor[5][2]/255.0 ;

			std::cout<< Color[i][0] <<","<<Color[i][1]<<","<<Color[i][2]<<std::endl;

			Color[i][3] =0.5 ;
			pen.setColor( QColor( m_pOrganColor[5][0],m_pOrganColor[5][1], m_pOrganColor[5][2] ));
			brush.setColor( QColor( m_pOrganColor[5][0],m_pOrganColor[5][1], m_pOrganColor[5][2] ) );
			p.setPen(pen);
			p.setBrush( brush );
			p.drawEllipse( *m_pPosi_label6, 10, 10 );
			m_pTranparency[i] = m_pConfigureTransparencyVector[5];
			///m_pIdSlider1用来存储对应的Organ在OrganName中的id序号
			m_pIdSlider6 = i;
			m_pOrganNameDisplayVector.push_back( ui.lineEdit_label6->text() );

		}
		else
		{
			// 前三个表示RGB，第四个表示透明度
			Color[i][0] =174/255.0 ;   
			Color[i][1] =236/255.0 ;
			Color[i][2] =160/255.0 ;
			Color[i][3] =0.5 ;
			pen.setColor( QColor(174, 236, 160));
			brush.setColor( QColor(174, 236, 160) );
			p.setPen(pen);
			p.setBrush( brush );
			p.drawEllipse( *m_pPosi_other, 10, 10 );
			m_pTranparency[i] = 0.5;
			m_pOrganNameDisplayVector.push_back( QString::fromLocal8Bit("其他") );
		}
	}
	update();

}

void viewImage::setRenderer( std::vector< QString > & FilePathVector)
{
	QString fileName;
	for( int i = 0; i< FilePathVector.size(); i++ )
	{
		fileName = FilePathVector[i];

		QByteArray ba = fileName.toLocal8Bit();
		const char *fileName_str = ba.data();

		m_pReader= vtkMetaImageReader::New();  
		m_pReader->SetFileName(fileName_str);
		std::cout<<fileName_str<<std::endl;
		m_pReader->Update();
		m_pReaderVector.push_back( m_pReader );  //存储

		m_pSurface = vtkMarchingCubes::New();      //采用vtkMarchingCubes对mask体数据进行渲染
		m_pSurface->SetInputData( m_pReader->GetOutput() );
		m_pSurface->ComputeNormalsOn();
		m_pSurface->SetValue(0, 1);
		m_pSurfaceVector.push_back( m_pSurface );  //存储，为释放提供指针

		m_pPolyDataMapper=vtkPolyDataMapper::New();
		m_pPolyDataMapper->SetInputConnection(m_pSurface->GetOutputPort());
		m_pPolyDataMapper->ScalarVisibilityOff();
		m_pPolyDataMapperVector.push_back( m_pPolyDataMapper ); //存储

		m_pActor = vtkActor::New();
		m_pActor->SetMapper(m_pPolyDataMapper);
		m_pActor->GetProperty()->SetColor( m_pColor[i][0],  m_pColor[i][1],  m_pColor[i][2]);
		m_pActor->GetProperty()->SetOpacity( m_pTranparency[i] );
		m_pActorVector.push_back( m_pActor );  //存储,以便释放

		m_pRenderer = vtkRenderer::New();
		m_pRenderer->AddActor( m_pActor );
		m_pRenderer->SetBackground( 1.0, 1.0, 1.0 );
		m_pRenderer->SetViewport(m_pLayout[i][0],m_pLayout[i][1],m_pLayout[i][2],m_pLayout[i][3]);

		m_pTextActor = vtkTextActor::New();
		m_pTextActor->SetInput( m_pOrganNameVector[i].toLocal8Bit().data() );
		m_pTextActor->SetPosition( 20, 40 );
		m_pTextActor->GetTextProperty()->SetFontSize( 24 );
		m_pTextActor->GetTextProperty()->SetColor( 1.0, 0.0, 0.0 );
		m_pTextActorVector.push_back( m_pTextActor );    //存储,以便释放

		m_pRenderer->AddActor2D( m_pTextActor );
		m_pRendererVector.push_back(m_pRenderer);
	}
}

void viewImage::paintEvent(QPaintEvent *e)
{
	QPainter p(this);
	QRectF target( 0, 0,700, 550);
	QRectF source(0.0, 0.0, 700,550 );

	p.drawImage( target, m_pImage, source );
}

void viewImage::mousePressEvent(QMouseEvent *e)
{
	if( e->button() ==  Qt::RightButton )
	{
		if( m_pWidget_all != NULL )
		{
			m_pWidget_all->close();
			delete m_pWidget_all;
		}
		if( m_pWidget_each != NULL )
		{
			m_pWidget_each->close();
			delete m_pWidget_each;
		}
		close();
	}
	else if( e->button() == Qt::LeftButton )
	{
		m_pPosi = e->globalPos() - this->frameGeometry().topLeft();
	}
}

void viewImage::mouseMoveEvent(QMouseEvent *e)
{
	if( e->buttons() & Qt::LeftButton )
	{
		move( e->globalPos() - m_pPosi );
	}
}

//bool viewImage::event(QEvent *e)
//{
//	if( e->type)
//}


void viewImage::setCircleTextInit()
{
	QRect rect;

	int dy = 20;

	rect = ui.lineEdit_label1->geometry();
	m_pPosi_label1 = new QPoint(rect.center().x(), rect.center().y() - rect.height() - dy );


	rect = ui.lineEdit_label2->geometry();
	m_pPosi_label2 = new QPoint(rect.center().x(), rect.center().y() - rect.height() - dy );

	rect = ui.lineEdit_label3->geometry();
	m_pPosi_label3 = new QPoint(rect.center().x(), rect.center().y() - rect.height() - dy );

	rect = ui.lineEdit_label4->geometry();
	m_pPosi_label4 = new QPoint(rect.center().x(), rect.center().y() - rect.height() - dy );

	rect = ui.lineEdit_label5->geometry();
	m_pPosi_label5 = new QPoint(rect.center().x(), rect.center().y() - rect.height() - dy );

	rect = ui.lineEdit_label6->geometry();
	m_pPosi_label6 = new QPoint(rect.center().x(), rect.center().y() - rect.height() - dy );

	rect = ui.lineEdit_other->geometry();
	m_pPosi_other = new QPoint(rect.center().x(), rect.center().y() - rect.height() - dy );


	/////////
	QPainter p(&m_pImage);
	QPen   pen;
	pen.setWidth(1);
	pen.setColor( QColor(187, 187, 187));
	pen.setStyle( Qt::SolidLine );

	p.setPen(pen);

	QBrush brush;
	brush.setColor( QColor(187, 187, 187) );
	brush.setStyle(Qt::SolidPattern);
	p.setBrush( brush );
	p.drawEllipse( *m_pPosi_label1, 10, 10 );

	p.drawEllipse( *m_pPosi_label2, 10, 10 );
	p.drawEllipse( *m_pPosi_label3, 10, 10 );
	p.drawEllipse( *m_pPosi_label4, 10, 10 );
	p.drawEllipse( *m_pPosi_label5, 10, 10 );
	p.drawEllipse( *m_pPosi_label6, 10, 10 );
	p.drawEllipse( *m_pPosi_other, 10, 10 );
	update();
	////////////

	m_pSize = 0;       //初始化
	QBrush myBrush;
	QPalette palette;

	//设置PushButton的颜色
	QFont ft("Arial",11,QFont::Black);
	ft.setPixelSize(14);
	ui.lineEdit_path->setFont( ft );

	///// 修改PushButton的字体  ///
	//ft.setFamily("宋体");
	//ft.setPixelSize(18);
	//ui.pushButton_each->setFont(ft);
	//ui.pushButton_all->setFont(ft);
	////////////////////////////////

	myBrush = QBrush( Qt::white, Qt::DiagCrossPattern );
	palette.setBrush( QPalette::ButtonText, QColor(238, 238, 238) );
	ui.pushButton_path->setStyleSheet("background-color:rgb(238,238,238)");
	//ui.pushButton_path->setPalette(palette);

	QFont font_load = ui.pushButton_load->font();
	font_load.setPixelSize(16);
	ui.pushButton_load->setStyleSheet("background-color:rgb(22,158,131)");
	ui.pushButton_load->setPalette(palette);
	ui.pushButton_load->setFont( font_load);

	QFont font_each = ui.pushButton_each->font();
	font_each.setPixelSize(20);
	ui.pushButton_each->setStyleSheet("background-color:rgb(22,158,131)");
	ui.pushButton_each->setPalette(palette);

	ui.pushButton_each->setFont(font_each);

	ui.pushButton_all->setStyleSheet("background-color:rgb(22,158,131)");
	ui.pushButton_all->setPalette(palette);
	ui.pushButton_all->setFont(font_each);



	myBrush = QBrush( Qt::white, Qt::DiagCrossPattern );
	palette.setBrush( QPalette::Text, myBrush );

	QFont  font = ui.lineEdit_label1->font();
	font.setPixelSize(16);

	ui.lineEdit_label1->setStyleSheet("background-color:rgb(54,55,60)");
	//ui.lineEdit_aorta->setFont( QFont("Timer", 8, QFont::Bold) );
	ui.lineEdit_label1->setPalette(palette);
	ui.lineEdit_label1->setFont(font);

	ui.lineEdit_label2->setStyleSheet("background-color:rgb(54,55,60)");
	//ui.lineEdit_liver->setFont( QFont("Timer", 8, QFont::Bold) );
	ui.lineEdit_label2->setPalette(palette);
	ui.lineEdit_label2->setFont(font);

	ui.lineEdit_label3->setStyleSheet("background-color:rgb(54,55,60)");
	//ui.lineEdit_spleen->setFont( QFont("Timer", 8, QFont::Bold) );
	ui.lineEdit_label3->setPalette(palette);
	ui.lineEdit_label3->setFont(font);

	ui.lineEdit_label4->setStyleSheet("background-color:rgb(54,55,60)");
	//ui.lineEdit_pancrease->setFont( QFont("Timer", 8, QFont::Bold) );
	ui.lineEdit_label4->setPalette(palette);
	ui.lineEdit_label4->setFont(font);

	ui.lineEdit_label5->setStyleSheet("background-color:rgb(54,55,60)");
	//ui.lineEdit_postcava->setFont( QFont("Timer", 8, QFont::Bold) );
	ui.lineEdit_label5->setPalette(palette);
	ui.lineEdit_label5->setFont(font);

	ui.lineEdit_label6->setStyleSheet("background-color:rgb(54,55,60)");
	ui.lineEdit_label6->setPalette( palette );
	ui.lineEdit_label6->setFont(font);

	ui.lineEdit_other->setStyleSheet("background-color:rgb(54,55,60)");
	//ui.lineEdit_other->setFont( QFont("Timer", 8, QFont::Bold) );
	ui.lineEdit_other->setPalette(palette);
	ui.lineEdit_other->setFont(font);
}

void viewImage::mywidget_closed( int i)
{
	if( i== 1 )
	{

		delete m_pWidget_each;
		m_pRenderWindowEach->Delete();

		m_pWidget_each = NULL;
	}

	if( i == 2 )
	{
		m_pRendererAll->Delete();
		m_pRenderWindowAll->Delete();
		m_pTextActorAll->Delete();

		delete m_pWidget_all;
		m_pWidget_all = NULL;
	}
}


void viewImage::lineEdit_changed_slot()
{
	m_pIsload = false;
	m_pSize = 0;
	m_pOrganNameVector.clear();
	m_pFilePathVector.clear();
	
	
	for( int i = 0; i< m_pActorVector.size(); i++ )
	{
		m_pTextActorVector[i]->Delete();
		m_pRendererVector[i]->Delete();
		m_pActorVector[i]->Delete();
		m_pPolyDataMapperVector[i]->Delete();
		m_pSurfaceVector[i]->Delete();
		m_pReaderVector[i]->Delete();
	}

	m_pTextActorVector.clear();
	m_pRendererVector.clear();
	m_pActorVector.clear();
	m_pPolyDataMapperVector.clear();
	m_pSurfaceVector.clear();
	m_pReaderVector.clear();


	if( m_pWidget_each != NULL )
	{
		delete m_pWidget_each;
		m_pRenderWindowEach->Delete();

		m_pWidget_each = NULL;
	}

	if( m_pWidget_all != NULL )
	{
		m_pRendererAll->Delete();
		m_pRenderWindowAll->Delete();
		m_pTextActorAll->Delete();

		delete m_pWidget_all;
		m_pWidget_all = NULL;
	}
	setCircleTextInit();

	m_pIdSlider1 = -1;
	m_pIdSlider2 = -1;
	m_pIdSlider3 = -1;
	m_pIdSlider4 = -1;
	m_pIdSlider5 = -1;
	m_pIdSlider6 = -1;
}


void  viewImage::configureFileInitialize()
{
	QSettings settings("viewimage.ini", QSettings::IniFormat);
	settings.setIniCodec("UTF8");

	int length;

	ui.lineEdit_label1->setText( settings.value("Label1/name").toString() );
	length = settings.value("Label1/mask").toString().size();
	std::cout<< settings.value("Label1/mask").toString().toLocal8Bit().data()<<std::endl;

	m_pCofigureFileVector.push_back( settings.value("Label1/mask").toString().left( length - 4 )  );
	m_pConfigureTransparencyVector.push_back( settings.value("Label1/transparency").toDouble() );
	m_pOrganColor[0][0] = settings.value("Label1/R").toInt();
	m_pOrganColor[0][1] = settings.value("Label1/G").toInt();
	m_pOrganColor[0][2] = settings.value("Label1/B").toInt();

	ui.lineEdit_label2->setText( settings.value("Label2/name").toString() );
	length = settings.value("Label2/mask").toString().size();
	std::cout<< settings.value("Label2/mask").toString().toLocal8Bit().data()<<std::endl;
	m_pCofigureFileVector.push_back( settings.value("Label2/mask").toString().left( length - 4 ) );
	m_pConfigureTransparencyVector.push_back( settings.value("Label2/transparency").toDouble() );
	m_pOrganColor[1][0] = settings.value("Label2/R").toInt();
	m_pOrganColor[1][1] = settings.value("Label2/G").toInt();
	m_pOrganColor[1][2] = settings.value("Label2/B").toInt();

	ui.lineEdit_label3->setText( settings.value("Label3/name").toString() );
	length = settings.value("Label3/mask").toString().size();
	std::cout<< settings.value("Label3/mask").toString().toLocal8Bit().data()<<std::endl;
	m_pCofigureFileVector.push_back( settings.value("Label3/mask").toString().left( length - 4 ) );
	m_pConfigureTransparencyVector.push_back( settings.value("Label3/transparency").toDouble() );
	m_pOrganColor[2][0] = settings.value("Label3/R").toInt();
	m_pOrganColor[2][1] = settings.value("Label3/G").toInt();
	m_pOrganColor[2][2] = settings.value("Label3/B").toInt();

	ui.lineEdit_label4->setText( settings.value("Label4/name").toString() );
	length = settings.value("Label4/mask").toString().size();
	std::cout<< settings.value("Label4/mask").toString().toLocal8Bit().data()<<std::endl;
	m_pCofigureFileVector.push_back( settings.value("Label4/mask").toString().left( length - 4 )   );
	m_pConfigureTransparencyVector.push_back( settings.value("Label4/transparency").toDouble() );
	m_pOrganColor[3][0] = settings.value("Label4/R").toInt();
	m_pOrganColor[3][1] = settings.value("Label4/G").toInt();
	m_pOrganColor[3][2] = settings.value("Label4/B").toInt();

	ui.lineEdit_label5->setText( settings.value("Label5/name").toString() );
	length = settings.value("Label5/mask").toString().size();
	std::cout<< settings.value("Label5/mask").toString().toLocal8Bit().data()<<std::endl;
	m_pCofigureFileVector.push_back( settings.value("Label5/mask").toString().left( length - 4 )  );
	m_pConfigureTransparencyVector.push_back( settings.value("Label5/transparency").toDouble() );
	m_pOrganColor[4][0] = settings.value("Label5/R").toInt();
	m_pOrganColor[4][1] = settings.value("Label5/G").toInt();
	m_pOrganColor[4][2] = settings.value("Label5/B").toInt();

	ui.lineEdit_label6->setText( settings.value("Label6/name").toString() );
	length = settings.value("Label6/mask").toString().size();
	std::cout<< settings.value("Label6/mask").toString().toLocal8Bit().data()<<std::endl;
	m_pCofigureFileVector.push_back( settings.value("Label6/mask").toString().left( length - 4 )  );
	m_pConfigureTransparencyVector.push_back( settings.value("Label6/transparency").toDouble() );
	m_pOrganColor[5][0] = settings.value("Label6/R").toInt();
	m_pOrganColor[5][1] = settings.value("Label6/G").toInt();
	m_pOrganColor[5][2] = settings.value("Label6/B").toInt();
	std::cout<<m_pOrganColor[5][0]<<","<<m_pOrganColor[5][1]<<","<<m_pOrganColor[5][2]<<std::endl;

}

void viewImage::closeWidget_slot()
{
	if( m_pWidget_all != NULL )
	{
		m_pWidget_all->close();
		delete m_pWidget_all;
	}
	if( m_pWidget_each != NULL )
	{
		m_pWidget_each->close();
		delete m_pWidget_each;
	}
	close();
}


//////   6个Slider的ValueChanged对应的槽函数  
void viewImage::slider1ValueChanged_slot( int i)
{
	if( m_pIdSlider1 > -1)
	{
		m_pActorVector[ m_pIdSlider1 ]->GetProperty()->SetOpacity( double(i/100.0) );
		m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		m_pConfigureTransparencyVector[0] = double(i/100);
	}
}

void viewImage::slider2ValueChanged_slot( int i)
{
	if( m_pIdSlider2 > -1)
	{
		m_pActorVector[ m_pIdSlider2 ]->GetProperty()->SetOpacity( double(i/100.0) );
		m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		m_pConfigureTransparencyVector[1] = double(i/100);
	}
}

void viewImage::slider3ValueChanged_slot( int i)
{
	if( m_pIdSlider3 > -1)
	{
		m_pActorVector[ m_pIdSlider3 ]->GetProperty()->SetOpacity( double(i/100.0) );
		m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		m_pConfigureTransparencyVector[2] = double(i/100);
	}
}

void viewImage::slider4ValueChanged_slot( int i)
{
	if( m_pIdSlider4 > -1)
	{
		m_pActorVector[ m_pIdSlider4 ]->GetProperty()->SetOpacity( double(i/100.0) );
		m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		m_pConfigureTransparencyVector[3] = double(i/100);
	}
}

void viewImage::slider5ValueChanged_slot( int i)
{
	if( m_pIdSlider5 > -1)
	{
		m_pActorVector[ m_pIdSlider5 ]->GetProperty()->SetOpacity( double(i/100.0) );
		m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		m_pConfigureTransparencyVector[4] = double(i/100);
	}
}

void viewImage::slider6ValueChanged_slot( int i)
{
	if( m_pIdSlider6 > -1)
	{
		m_pActorVector[ m_pIdSlider6 ]->GetProperty()->SetOpacity( double(i/100.0) );
		m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		m_pConfigureTransparencyVector[5] = double(i/100);
	}
}


////////// 6个checkbox的StatedChanged对应的槽函数  //////////////
void viewImage::checkBox1StatedChanged_slot( int state )
{
	if( m_pIdSlider1 > -1)
	{
		if( state ==  Qt::Checked ) //选中
		{
			m_pActorVector[ m_pIdSlider1 ]->SetVisibility(1);
			m_pWidget_all->getSlider1()->setEnabled( true );
			m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		}
		else
		{
			m_pActorVector[ m_pIdSlider1 ]->SetVisibility(0);
			m_pWidget_all->getSlider1()->setEnabled( false );
			m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		}
	}
}

void viewImage::checkBox2StatedChanged_slot( int state )
{
	if( m_pIdSlider2 > -1)
	{
		if( state ==  Qt::Checked ) //选中
		{
			m_pActorVector[ m_pIdSlider2 ]->SetVisibility(1);
			m_pWidget_all->getSlider2()->setEnabled( true );
			m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		}
		else
		{
			m_pActorVector[ m_pIdSlider2 ]->SetVisibility(0);
			m_pWidget_all->getSlider2()->setEnabled( false );
			m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		}
	}

}


void viewImage::checkBox3StatedChanged_slot( int state )
{
	if( m_pIdSlider3 > -1)
	{
		if( state ==  Qt::Checked ) //选中
		{
			m_pActorVector[ m_pIdSlider3 ]->SetVisibility(1);
			m_pWidget_all->getSlider3()->setEnabled(true);
			m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		}
		else
		{
			m_pActorVector[ m_pIdSlider3 ]->SetVisibility(0);
			m_pWidget_all->getSlider3()->setEnabled( false );
			m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		}
	}

}


void viewImage::checkBox4StatedChanged_slot( int state )
{
	if( m_pIdSlider4 > -1)
	{
		if( state ==  Qt::Checked ) //选中
		{
			m_pActorVector[ m_pIdSlider4 ]->SetVisibility(1);
			m_pWidget_all->getSlider4()->setEnabled( true );
			m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		}
		else
		{
			m_pActorVector[ m_pIdSlider4 ]->SetVisibility(0);
			m_pWidget_all->getSlider4()->setEnabled( false );
			m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		}
	}

}


void viewImage::checkBox5StatedChanged_slot( int state )
{
	if( m_pIdSlider5 > -1)
	{
		if( state ==  Qt::Checked ) //选中
		{
			m_pActorVector[ m_pIdSlider5 ]->SetVisibility(1);
			m_pWidget_all->getSlider5()->setEnabled( true );
			m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		}
		else
		{
			m_pActorVector[ m_pIdSlider5 ]->SetVisibility(0);
			m_pWidget_all->getSlider5()->setEnabled( false );
			m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		}
	}

}


void viewImage::checkBox6StatedChanged_slot( int state )
{
	if( m_pIdSlider6 > -1)
	{
		if( state ==  Qt::Checked ) //选中
		{
			//m_pActorVector[ m_pIdSlider1 ]->GetProperty()->SetOpacity( m_pConfigureTransparencyVector[0] );
			//m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
			m_pActorVector[ m_pIdSlider6 ]->SetVisibility(1);
			m_pWidget_all->getSlider6()->setEnabled( true);
			m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		}
		else
		{
			m_pActorVector[ m_pIdSlider6 ]->SetVisibility(0);
			m_pWidget_all->getSlider6()->setEnabled( false );
			m_pWidget_all->getQVTKWidget()->GetRenderWindow()->Render();
		}
	}

}

