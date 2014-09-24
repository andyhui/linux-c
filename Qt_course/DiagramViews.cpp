#include <QtGui>
#include "DiagramViews.h"
#include "Histogram.h"

DiagramViews::DiagramViews(QWidget *parent): QWidget( parent )
{
	m_BKColor = QColor( 255, 197, 243 );
	m_VecPixmap.clear( );

	setAutoFillBackground( true );
	setPalette( QPalette( m_BKColor ) );
	setMinimumSize( 640, 480 );
	adjustSize( );
	DrawPixmaps( );
}

void DiagramViews::DrawPixmaps( void )
{
	m_VecPixmap.clear( );
	for ( quint32 i = 0; i < 3; i++ )
	{
		QPixmap pixmap( minimumSize( ) * 0.8 );
		pixmap.fill( QColor( 170, 255, 255 ) );
		m_VecPixmap.push_back( pixmap );
	}

	// 绘制第一张像素图
	Histogram histogram;
	histogram.SetMaxValue( 64 );
	histogram.AddItem( tr( "East" ), 32, QColor( 125, 0, 0 ) );
	histogram.AddItem( tr( "West" ), 48, QColor( 0, 125, 0 ) );
	histogram.AddItem( tr( "South" ), 24, QColor( 0, 0, 125 ) );
	histogram.AddItem( tr( "North" ), 26, QColor( 125, 125, 125 ) );
	histogram.Paint( &m_VecPixmap[0] );
}

void DiagramViews::paintEvent( QPaintEvent* )
{
	QPainter painter( this );
	QPoint pixmapPt;
	pixmapPt.setX( minimumSize( ).width( ) * 0.1 );
	pixmapPt.setY( minimumSize( ).height( ) * 0.1 );
	painter.drawPixmap( pixmapPt, m_VecPixmap[0] );
}

void DiagramViews::SetBackgroundColor( QVariant color )
{
	// 因为它有个复制构造函数（和QRgb），
	// 而QRgb = uint = unsigned int
	// 所以编译能够成功。
	setPalette( QPalette( color.toUInt( ) ) );
}
