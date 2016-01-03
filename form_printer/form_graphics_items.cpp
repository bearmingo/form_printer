#include "form_graphics_item.h"

#include <QtCore/QDebug>
#include <QtCore/QEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include "corner_grabber.h"

namespace {

const int kMinWidth = 40;
const int kMinHeight = 40;
}
FormGraphicsItem::FormGraphicsItem()
	: outter_border_color_(Qt::black),
	  location_(0, 0),
	  drag_start_(0, 0),
	  grid_space_(10),
	  width_(100),
	  height_(20),
	  corner_drag_start_(0, 0),
	  x_corner_grab_buffer_(6),
	  y_corner_grab_buffer_(6),
	  drawing_width_(width_ - x_corner_grab_buffer_),
      drawing_height_(height_ - y_corner_grab_buffer_),
	  drawing_origin_x_(x_corner_grab_buffer_),
	  drawing_origin_y_(y_corner_grab_buffer_)
{
    outter_border_pen_.setWidth(2);
    outter_border_pen_.setColor(outter_border_color_);

    this->setAcceptHoverEvents(true);
}

FormGraphicsItem::~FormGraphicsItem()
{
}

/**
 * To allow the user to grab the corners to resize, we need to get a hover
 * indication. But if the mouse pointer points to the left, then when the mouse
 * tip is to the left but just outsize the box, we will not get the hover.
 * So the solutions is to tell the graphics scene the box is larger than
 * what the pointer actually paints in. This way when the user gets the mouse
 * within a few pixels of what appears to be the edge of the box, we get
 * the hover indication.
 *
 * So the |corner_grab_buffer_| is a few pixel wide buffer zone around 
 * the outsize edge of the box
 */
void FormGraphicsItem::adjustSize(int x, int y)
{
    width_ += x;
    height_ += y;

    drawing_width_ = width_ - x_corner_grab_buffer_;
    drawing_height_ = height_ - y_corner_grab_buffer_;
}

/**
 * This scene event filter has been registered with all four corner grabber items.
 * When called, a pointer to the sending item is provided along with a generic
 * event, A dynamic_cast is used to determine if the event type is one of the events
 * we are interestd in.
 */
bool FormGraphicsItem::sceneEventFilter(QGraphicsItem* watched, QEvent* event)
{
    qDebug() << " QEvent == " + QString::number(event->type());

    CornerGrabber* corner = dynamic_cast<CornerGrabber*>(watched);
    if (NULL == corner)
        return false;

    QGraphicsSceneMouseEvent* mouse_event =
        dynamic_cast<QGraphicsSceneMouseEvent*>(event);
    if (NULL == event)
        return false;

    switch (event->type()) {
    case QEvent::GraphicsSceneMousePress:
        corner->setMouseState(CornerGrabber::MouseDown);
        corner->setMouseDown(mouse_event->pos());
        break;
    case QEvent::GraphicsSceneMouseRelease:
        corner->setMouseState(CornerGrabber::MouseReleased);
        break;
    case QEvent::GraphicsSceneMouseMove:
        corner->setMouseState(CornerGrabber::MouseMoving);
        break;
    default:
        // we do not care about the rest of the events
        return false;
    }

    if (corner->getMouseState() == CornerGrabber::MouseMoving) {
        qreal x = mouse_event->pos().x();
        qreal y = mouse_event->pos().y();

        // Depending on which corner has been grabbed, we want to move the position
        // of the item as it graws/shrinks accordingly. So we need either add
        // or subtract the offsets based on which corner this is.
        
        int x_axis_sign = 0;
        int y_axis_sign = 0;
        switch (corner->getCorner()) {
        case 0:
            x_axis_sign = +1;
            y_axis_sign = +1;
            break;
        case 1:
            x_axis_sign = -1;
            y_axis_sign = +1;
            break;
        case 2:
            x_axis_sign = -1;
            y_axis_sign = -1;
            break;
        case 3:
            x_axis_sign = +1;
            y_axis_sign = -1;
            break;
        }

        // If the mouse is being dragged, calculate a new size and alse re-position
        // the box to give the appearance of dragging the corner out/in to resize 
        // the box

        int x_moved = corner->getMouseDown().x() - x;
        int y_moved = corner->getMouseDown().y() - y;

        int new_width = width_ + (x_axis_sign * x_moved);
        if (new_width < kMinWidth)
            new_width = kMinWidth;

        int new_height = height_ + (y_axis_sign * y_moved);
        if (new_height < kMinHeight)
            new_height = kMinHeight;

        int delta_width = new_width - width_;
        int delta_height = new_height - height_;

        adjustSize(delta_width, delta_height);

        delta_width *= -1;
        delta_height *= -1;

        if (corner->getCorner() == 0) {
            int new_x_pos = this->pos().x() + delta_width;
            int new_y_pos = this->pos().y() + delta_height;
            this->setPos(new_x_pos, new_y_pos);
        }
        else if (corner->getCorner() == 1) {
            int new_y_pos = this->pos().y() + delta_height;
            this->setPos(this->pos().x(), new_y_pos);
        }
        else if (corner->getCorner() == 3) {
            int new_x_pos = this->pos().x() + delta_width;
            this->setPos(new_x_pos, this->pos().y());
        }

        setCornerPositions();

        this->update();
    }

    // true -> Do not send event to watched - we are finished with thie event
    return true;
}

// For supporting moving the box across the scene

void FormGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    event->setAccepted(true);
    drag_start_ = event->pos();
}

void FormGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF new_pos = event->pos();
    location_ += (new_pos - drag_start_);
    this->setPos(location_);
}

void FormGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    event->setAccepted(true);
    location_.setX((static_cast<int>(location_.x()) / grid_space_) * grid_space_);
    location_.setY((static_cast<int>(location_.y()) / grid_space_) * grid_space_);
    this->setPos(location_);
}

// Remove the corner grabbers
void FormGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    outter_border_color_ = Qt::black;
    
    for (int i = 0; i < 4; ++i) {
        corners_[i]->setParentItem(NULL);
        delete corners_[i];
        corners_[i] = NULL;
    }
}

// Create the corner grabbers
void FormGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    outter_border_color_ = Qt::red;

    for (int i = 0; i < 4; ++i) {
        corners_[i] = new CornerGrabber(this, i);
        corners_[i]->installSceneEventFilter(this);
    }

    setCornerPositions();
}

void FormGraphicsItem::setCornerPositions()
{
    corners_[0]->setPos(0, 0);
    corners_[1]->setPos(drawing_width_, 0);
    corners_[2]->setPos(drawing_width_, drawing_height_);
    corners_[3]->setPos(0, drawing_height_);
}

void FormGraphicsItem::setSize(const QSize& size)
{
    width_ = size.width();
    height_ = size.height();

    drawing_width_ = width_ - x_corner_grab_buffer_;
    drawing_height_ = height_ - y_corner_grab_buffer_;
}



void FormGraphicsItem::paint(QPainter *painter,
                             const QStyleOptionGraphicsItem *option,
                             QWidget *widget)
{
    // For nice drawing
    painter->setRenderHint(QPainter::Antialiasing);

    // Draw rectange with DashLine style,
    outter_border_pen_.setStyle(Qt::DashLine);
    outter_border_pen_.setColor(QColor(166, 166, 166));
    painter->setPen(outter_border_pen_);

    // Draw the top box, the visible one
    QBrush brush(QColor(244, 244, 244), Qt::SolidPattern);
    painter->setBrush(brush);

    QPointF top_left(drawing_origin_x_, drawing_origin_y_);
    QPointF bottom_right(drawing_width_, drawing_height_);

    QRectF rect2(top_left, bottom_right);
    painter->drawRoundedRect(rect2, 5, 5);

    this->paintContext(painter, option, widget);
}

QRectF FormGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, width_, height_);
}

void FormGraphicsItem::mouseMoveEvent(QGraphicsSceneDragDropEvent* event)
{
    event->setAccepted(false);
}

void FormGraphicsItem::mousePressEvent(QGraphicsSceneDragDropEvent* event)
{
    event->setAccepted(false);
}


QRectF FormGraphicsItem::getDrawingRect() const
{
    return QRectF(drawing_origin_x_, drawing_origin_y_,
                  drawing_width_, drawing_height_);
}

void FormGraphicsItem::paintContext(QPainter*painter,
                                    const QStyleOptionGraphicsItem* option,
                                    QWidget* widget)
{

}