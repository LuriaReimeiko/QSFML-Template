#include "MainWindow.hpp"
#include <QApplication>
#include <QScreen>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	app.setApplicationName("application-name");
	app.setApplicationDisplayName("Application Name");

	// Get the primary screen and store its geometry
	QScreen* screen = QGuiApplication::primaryScreen();
	QRect screenGeometry = screen->geometry();

	// Get the primary screen's size
	int screenWidth = screenGeometry.width();
	int screenHeight = screenGeometry.height();

	// Create the window
	MainWindow window;

	// Set the window to the center of the screen
	// at percentage% of the screen's size
	double percentage = 0.8;

	int w = static_cast<int>(screenWidth * percentage);
	int h = static_cast<int>(screenHeight * percentage);
	int x = (screenWidth - w) / 2;
	int y = (screenHeight - h) / 2;

	window.setGeometry(x, y, w, h);

	// Link the GUI window element to the application
	window.show();

	// Execute the application
	return app.exec();
}
