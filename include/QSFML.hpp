#ifndef _QSFML_HPP
#define _QSFML_HPP

#include <QWidget>
#include <SFML/Graphics/RenderWindow.hpp>

// Inherit from QWidget to place on the QApplication
// Inherit from sf::RenderWindow for less redundancy compared to storing one
class QSFML : public QWidget, public sf::RenderWindow
{
public:
    explicit QSFML(QWidget* parent = nullptr);

protected:
    // Used as initialization call
    void showEvent(QShowEvent* event) override;

    // Update calls to the SFML render window
    void paintEvent(QPaintEvent* event) override;

    // Disable Qt5's paint engine
    QPaintEngine* paintEngine() const override;

private:
    bool initialized = false;
};

#endif
