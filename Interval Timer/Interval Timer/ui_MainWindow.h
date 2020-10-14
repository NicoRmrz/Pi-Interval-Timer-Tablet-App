/* File: ui_MainWindow.h


*/
#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QDockWidget>
#include <QtCore/QElapsedTimer>


QT_BEGIN_NAMESPACE

/* Class: Ui_MainWindow

	Creates most GUI object that will be displayed on MainWindow
*/
class Ui_MainWindow
{
public:
	QWidget     *centralwidget;
	QStatusBar  *statusbar;
	//QHBoxLayout *mainHLayout;
	//QHBoxLayout *buttonLayout;
	//QVBoxLayout *leftPanelVLayout;
	//QHBoxLayout *MainSplitLayout;
	//QPushButton *folderButton;
	//QPushButton *runButton;
	//QTabWidget  *projectTabWidget;
	//QTabWidget  *myTabs;
	//QCheckBox   *focusView;
	//QCheckBox   *gridLines;
	//QSplitter   *IDEHorizontalSplitter;
	//QWidget     *HSplitcontainer;
	//QWidget     *MainLeftcontainer;
	QLabel      *exeTimer;
	QElapsedTimer  *timer;

	//QLabel      *xPos;
	//QLabel      *yPos;
	//QLabel      *redData;
	//QLabel      *greenData;
	//QLabel      *blueData;
	//QDockWidget *outputDock;

	/* Function: setupUi

		Function creating and laying out all UI Objects
	*/
	void setupUi(QMainWindow *MainWindow)
	{
		// Create main central widget 
		centralwidget = new QWidget(MainWindow);
		centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
		MainWindow->setCentralWidget(centralwidget);



		//// set up timer 
		timer = new QElapsedTimer();

		// create label to be displayed on status bar
		exeTimer = new QLabel(MainWindow);
		exeTimer->setObjectName(QString::fromUtf8("exeTimer"));
		exeTimer->setText("Execution Time: 0 \t");


		// status bar
		statusbar = new QStatusBar(MainWindow);
		statusbar->setObjectName(QString::fromUtf8("statusbar"));
		statusbar->showMessage("Initializing...", 5000);
		statusbar->addPermanentWidget(exeTimer, 0);

		// set status bar
		MainWindow->setStatusBar(statusbar);

		/*---------------------------------------------------*/
		/*---------------------------------------------------*/
		/*---------------------------------------------------*/

		// Set final layout on central UI widget
		//centralwidget->setLayout(MainSplitLayout);
		centralwidget->isWindow();

	}    // setupUi
};

namespace Ui
{
	class MainWindow : public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE
