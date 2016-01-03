#include "corner_grabber.h"

#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsSceneMouseEvent>


CornerGrabber::CornerGrabber(QGraphicsItem* parent /* = 0 */, int corner /* = 0*/)
	: QGraphicsItem(parent),
	outter_border_color_(Qt::black),
	width_(6),
	height_(6),
	corner_(corner),
	mouse_button_state_(MouseState::MouseReleased)
{
	setParentItem(parent);
	outter_border_pen_.setWidth(2);
	outter_border_pen_.setColor(outter_border_color_);

	this->setAcceptHoverEvents(true);
}

void CornerGrabber::setMouseState(CornerGrabber::MouseState state)
{
	mouse_button_state_ = state;
}

CornerGrabber::MouseState CornerGrabber::getMouseState() const
{
	return mouse_button_state_;
}

int CornerGrabber::getCorner()
{
	return corner_;
}

QPointF CornerGrabber::getMouseDown() const
{
    return mouse_down_;
}

void CornerGrabber::setMouseDown(const QPointF& position)
{
    mouse_down_ = position;
}

void CornerGrabber::mouseMoveEvent(QGraphicsSceneDragDropEvent* event)
{
	event->setAccepted(false);
}

void CornerGrabber::mousePressEvent(QGraphicsSceneDragDropEvent* event)
{
	event->setAccepted(false);
}

void CornerGrabber::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	event->setAccepted(false);
}

void CornerGrabber::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	event->setAccepted(false);
}

void CornerGrabber::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	event->setAccepted(false);
}

void CornerGrabber::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
	outter_border_color_ = Qt::red;
	this->update(0, 0, width_, height_);
}

void CornerGrabber::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
	outter_border_color_ = Qt::black;
	this->update(0, 0, width_, height_);
}

QRectF CornerGrabber::boundingRect() const
{
    return QRectF(0, 0, width_, height_);
}

void CornerGrabber::paint(QPainter* painter,
						  const QStyleOptionGraphicsItem*,
						  QWidget*)
{
	outter_border_pen_.setCapStyle(Qt::SquareCap);
	outter_border_pen_.setStyle(Qt::SolidLine);
	painter->setPen(outter_border_pen_);

	QPointF top_left(0, 0);
	QPointF bottom_right(width_, height_);

	QRectF rect(top_left, bottom_right);

	QBrush brush(Qt::SolidPattern);
	brush.setColor(outter_border_color_);
	painter->fillRect(rect, brush);
}


