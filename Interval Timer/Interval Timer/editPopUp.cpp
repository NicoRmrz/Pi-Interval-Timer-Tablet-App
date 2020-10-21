
/* File: editPopUp.cpp

	Contains functions for edit pop up window

	Author: Nico Ramirez
*/
#include "editPopUp.h"

using namespace std;

/* Constructor: editPopUp

		Lays out all objects for the the edit pop up window

	Parameters:

		parent - Inherits QObject attributes
*/
editWindow::editWindow(QDialog *parent = 0) :
	GUI_Style(parent)
{
	setFixedSize(300, 400);
	setWindowTitle("Edit");
	setStyleSheet(GUI_Style.mainWindowIdle);
	setWindowIcon(QIcon(MAIN_ICON));

	rollSecondInput = new QComboBox();
	QScroller::grabGesture(rollSecondInput, QScroller::LeftMouseButtonGesture);
	rollSecondInput->setStyleSheet(GUI_Style.comboBox);
	rollSecondInput->setFixedHeight(35);
	rollSecondInput->setFixedWidth(32);

	restSecondInput = new QComboBox();
	QScroller::grabGesture(restSecondInput, QScroller::LeftMouseButtonGesture);
	restSecondInput->setStyleSheet(GUI_Style.comboBox);
	restSecondInput->setFixedHeight(35);
	restSecondInput->setFixedWidth(32);

	rollMinuteInput = new QSpinBox();
	QScroller::grabGesture(rollMinuteInput, QScroller::LeftMouseButtonGesture);
	rollMinuteInput->setRange(0, 60);

	restMinuteInput = new QSlider();
	QScroller::grabGesture(restMinuteInput, QScroller::LeftMouseButtonGesture);


	mainVLayout = new QVBoxLayout();
	mainVLayout->setContentsMargins(0, 0, 0, 0);
	mainVLayout->setSpacing(20);
	mainVLayout->addWidget(rollSecondInput);
	mainVLayout->addWidget(rollMinuteInput);
	mainVLayout->addWidget(restSecondInput);
	mainVLayout->addWidget(restMinuteInput);

	setLayout(mainVLayout);

	setComboBoxes();
}

/* Define: setComboBoxes

	function to populate all combo boxes with initial numbers

 */
void editWindow::setComboBoxes(void)
{
	for (int x = 0; x < 60; x++)
	{
		rollSecondInput->addItem(QString::number(x));

	}

	rollSecondInput->setCurrentIndex(30);
}