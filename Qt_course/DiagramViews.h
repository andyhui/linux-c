#ifndef _DIAGRAMVIEWS_H_
#define _DIAGRAMVIEWS_H_

#include <QVariant>
#include <QWidget>
#include <QVector>

QT_BEGIN_NAMESPACE
class QPixmap;
class QColor;
QT_END_NAMESPACE

class DiagramViews : public QWidget
{
	Q_OBJECT
public:
	explicit DiagramViews( QWidget *parent = 0 );
	void DrawPixmaps( void );				// 预先画像素图
	void paintEvent( QPaintEvent* );		// 绘制的事件
signals:
	
public slots:
	void SetBackgroundColor( QVariant color );// 设置背景颜色
private:
	QVector<QPixmap>		m_VecPixmap;	// 像素图的向量
	QColor					m_BKColor;		// 背景颜色

	
};

#endif // LINEGRAPH_H
