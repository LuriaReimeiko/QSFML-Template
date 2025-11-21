#include "QSFML.hpp"
#include <QTimer>

QSFML::QSFML(QWidget* parent) : QWidget(parent)
{
	setAttribute(Qt::WA_NativeWindow);
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAttribute(Qt::WA_NoSystemBackground);

    setAutoFillBackground(false);
    setFocusPolicy(Qt::StrongFocus);

    int frameLength = 8; // In MilliSeconds, 1 000 / 8 = 125fps

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]()->void{ repaint(); });
    timer->start(frameLength);
}

void QSFML::showEvent(QShowEvent* event)
{
    Q_UNUSED(event);

    if (!initialized)
    {
        WId wid = winId();
        RenderWindow::create(static_cast<sf::WindowHandle>(wid));

        initialized = true;
    }
}

void QSFML::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    RenderWindow::clear();

    RenderWindow::display();
}

QPaintEngine* QSFML::paintEngine() const
{
    return nullptr;
}
