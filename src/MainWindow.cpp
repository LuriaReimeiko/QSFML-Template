#include "MainWindow.hpp"
#include "QSFML.hpp"
#include <QPushButton>
#include <QSplitter>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setContextMenuPolicy(Qt::NoContextMenu);

    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setHandleWidth(4);

    QSFML* qsfml = new QSFML(splitter);
    splitter->setStretchFactor(0, 5);

    QWidget* holder = new QWidget(splitter);
    splitter->setStretchFactor(1, 1);
    
    QPushButton* buttonP = new QPushButton(holder);
    QPushButton* buttonM = new QPushButton(holder);
    
    buttonP->setText("Zoom In");
    buttonM->setText("Zoom Out");


    setCentralWidget(splitter);
}
