#ifndef _QSFML_HPP
#define _QSFML_HPP

#include <QWidget>
#include <SFML/Graphics/RenderWindow.hpp>

class QSFML : public QWidget, public sf::RenderWindow
{
public:
    explicit QSFML(QWidget* parent = nullptr);

protected:
    void showEvent(QShowEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

    QPaintEngine* paintEngine() const override;

private:
    bool initialized = false;
};

#endif
