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

QT_BEGIN_NAMESPACE

/* Class: Ui_MainWindow

	Creates most GUI object that will be displayed on MainWindow
*/
class Ui_MainWindow
{
public:
	QWidget     *centralwidget;
	QStatusBar  *statusbar;
	QVBoxLayout *mainLayout;
    QPushButton *showIntervalTimer;

	/* Function: setupUi

		Function creating and laying out all UI Objects
	*/
	void setupUi(QMainWindow *MainWindow)
	{
		// Create main central widget 
		centralwidget = new QWidget(MainWindow);
		centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
		MainWindow->setCentralWidget(centralwidget);
        MainWindow->setFixedSize(800, 480);

        /*---------------------------------------------------*/
        /*----------------- Create Objects ------------------*/
        /*---------------------------------------------------*/

        // Create timer interval button
        showIntervalTimer = new QPushButton(MainWindow);
        showIntervalTimer->setObjectName(QString::fromUtf8("showIntervalTimer"));
        showIntervalTimer->setMinimumSize(200, 90);
        showIntervalTimer->setMaximumSize(200, 90);
        showIntervalTimer->setText("INTERVAL TIMER");

		// status bar
		statusbar = new QStatusBar(MainWindow);
		statusbar->setObjectName(QString::fromUtf8("statusbar"));
		statusbar->showMessage("Initializing...", 5000);

		// set status bar
		MainWindow->setStatusBar(statusbar);

		/*---------------------------------------------------*/
		/*--------------------- Layout  ---------------------*/
		/*---------------------------------------------------*/
        mainLayout = new QVBoxLayout(MainWindow);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);
        mainLayout->addWidget(showIntervalTimer, 0, Qt::AlignCenter);

		// Set final layout on central UI widget
		centralwidget->setLayout(mainLayout);
		centralwidget->isWindow();

	}    // setupUi
};

namespace Ui
{
	class MainWindow : public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE
