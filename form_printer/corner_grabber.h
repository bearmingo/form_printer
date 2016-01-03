#ifndef __FORM_PRINTER_CORNER_GRABBER_H__
#define __FORM_PRINTER_CORNER_GRABBER_H__

#include <QtGui/QPen>
#include <QtWidgets/QGraphicsItem>

class CornerGrabber
	: public QGraphicsItem
{
public:
	explicit CornerGrabber(QGraphicsItem* parent = 0, int coner = 0);

	int getCorner();

	enum MouseState {
		MouseReleased = 0,
		MouseDown,
		MouseMoving
	};

	void setMouseState(MouseState);
	MouseState getMouseState() const;

    QPointF getMouseDown() const;
    void setMouseDown(const QPointF& position);

private:
	// Override QGraphicsItem
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter* painter,
					   const QStyleOptionGraphicsItem* option,
					   QWidget* widget);
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
	// once the hover event handlers are implemented in this class,
	// the mouse events must allow be implemented because of
	// some linkage issue - apparrently there is some connection
	// between the hover events and mouseMove/Press/Release
	// events which triggers a vtable issue
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
	virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);
	virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
	virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

private:
    QPointF mouse_down_;

	QColor outter_border_color_;
	QPen outter_border_pen_;

	qreal width_;
	qreal height_;

	int corner_;
	MouseState mouse_button_state_;
};

#endif /* __FORM_PRINTER_CORNER_GRABBER_H__ */