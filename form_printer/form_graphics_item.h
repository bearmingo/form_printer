#ifndef __FORM_PRITNER_FORM_GRAPHICS_ITEM_H__
#define __FORM_PRITNER_FORM_GRAPHICS_ITEM_H__

#include <QtGui/QPen>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/QGraphicsTextItem>

class CornerGrabber;

class FormGraphicsItem
	: public QGraphicsItem
{
public:
	FormGraphicsItem();
	~FormGraphicsItem();

	void setSize(const QSize& size);

    // Get rect which can draw context.
    QRectF getDrawingRect() const;
private:
	// Override QGraphicsItem
	virtual QRectF boundingRect()const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event); ///< must be re-implemented to handle mouse hover enter events
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event); ///< must be re-implemented to handle mouse hover leave events

	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);///< allows the main object to be moved in the scene by capturing the mouse move events
	virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

	virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);
	virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);
	virtual bool sceneEventFilter(QGraphicsItem * watched, QEvent * event);

    // For children class to draw context;
    virtual void paintContext(QPainter*painter,
                              const QStyleOptionGraphicsItem* option,
                              QWidget* widget);

	void setCornerPositions();
	void adjustSize(int x, int y);

private:
    QString text_;
	QColor outter_border_color_;
	QPen outter_border_pen_;
	QPointF location_;
	QPointF drag_start_;
	int grid_space_;
	qreal width_;
	qreal height_;
	QPointF corner_drag_start_;

	int x_corner_grab_buffer_;
	int y_corner_grab_buffer_;
	qreal drawing_width_;
	qreal drawing_height_;
	qreal drawing_origin_x_;
	qreal drawing_origin_y_;

	CornerGrabber* corners_[4];

};

#endif /*__FORM_PRITNER_FORM_GRAPHICS_ITEM_H__*/