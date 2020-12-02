
/* File: editPopUp.cpp

	Contains functions for edit pop up window

	Author: Nico Ramirez
*/
#include "editPopUp.h"
#include "timer.h"

using namespace std;

/* Constructor: editPopUp

		Lays out all objects for the the edit pop up window

	Parameters:

		parent - Inherits QObject attributes
*/
editWindow::editWindow(QDialog *parent = 0) :
	GUI_Stylesheet(parent)
{
	setFixedSize(350, 425);
	setWindowTitle("Edit");
	setStyleSheet(GUI_Stylesheet.mainWindowGrey);
	setWindowIcon(QIcon(MAIN_ICON));
	setWindowFlags(Qt::FramelessWindowHint);

	saveExitBtn = new QPushButton();
	saveExitBtn->setText("Save and Exit");
	saveExitBtn->setFixedHeight(40);

	restMinuteInput = new QSpinBox();
	restMinuteInput->setRange(0, 60);
	restMinuteInput->setFixedHeight(60);
	restMinuteInput->setFixedWidth(150);
	restMinuteInput->setSuffix(" min");
	restMinuteInput->setValue(DEFAULT_REST_MINUTE);

	restSecondInput = new QSpinBox();
	restSecondInput->setRange(0, 60);
	restSecondInput->setFixedHeight(60);
	restSecondInput->setFixedWidth(150);
	restSecondInput->setSuffix(" sec");
	restSecondInput->setValue(DEFAULT_REST_SECOND);

	rollMinuteInput = new QSpinBox();
	rollMinuteInput->setRange(0, 60);
	rollMinuteInput->setFixedHeight(60);
	rollMinuteInput->setFixedWidth(150);
	rollMinuteInput->setSuffix(" min");
	rollMinuteInput->setValue(DEFAULT_ROLL_MINUTE);

	rollSecondInput = new QSpinBox();
	rollSecondInput->setRange(0, 60);
	rollSecondInput->setFixedHeight(60);
	rollSecondInput->setFixedWidth(150);
	rollSecondInput->setSuffix(" sec");
	rollSecondInput->setValue(DEFAULT_ROLL_SECOND);

	restLabel = new QLabel();
	restLabel->setText("Rest Time");

	rollLabel = new QLabel();
	rollLabel->setText("Roll Time");

	restOptionsLayout = new QHBoxLayout();
	restOptionsLayout->setContentsMargins(0, 0, 0, 0);
	restOptionsLayout->setSpacing(10);
	restOptionsLayout->addWidget(restMinuteInput);
	restOptionsLayout->addWidget(restSecondInput);

	rollOptionsLayout = new QHBoxLayout();
	rollOptionsLayout->setContentsMargins(0, 0, 0, 0);
	rollOptionsLayout->setSpacing(10);
	rollOptionsLayout->addWidget(rollMinuteInput);
	rollOptionsLayout->addWidget(rollSecondInput);


	restLayout = new QVBoxLayout();
	restLayout->setContentsMargins(0, 0, 0, 0);
	restLayout->setSpacing(0);
	restLayout->addWidget(restLabel, 0, Qt::AlignTop);
	restLayout->addLayout(restOptionsLayout, Qt::AlignTop);

	rollLayout = new QVBoxLayout();
	rollLayout->setContentsMargins(0, 0, 0, 0);
	rollLayout->setSpacing(0);
	rollLayout->addWidget(rollLabel, 0, Qt::AlignTop);
	rollLayout->addLayout(rollOptionsLayout, Qt::AlignTop);

	mainVLayout = new QVBoxLayout();
	mainVLayout->setContentsMargins(0, 0, 0, 0);
	mainVLayout->setSpacing(50);
	mainVLayout->addLayout(rollLayout);
	mainVLayout->addLayout(restLayout);
	mainVLayout->addWidget(saveExitBtn);

	setLayout(mainVLayout);

	rollMinuteInput->setStyleSheet(GUI_Stylesheet.spinBox);
	restMinuteInput->setStyleSheet(GUI_Stylesheet.spinBox);
	rollSecondInput->setStyleSheet(GUI_Stylesheet.spinBox);
	restSecondInput->setStyleSheet(GUI_Stylesheet.spinBox);
	saveExitBtn->setStyleSheet(GUI_Stylesheet.buttonIdle);
	rollLabel->setStyleSheet(GUI_Stylesheet.optionsLabel);
	restLabel->setStyleSheet(GUI_Stylesheet.optionsLabel);


	connect(saveExitBtn, &QPushButton::pressed, this, &editWindow::exitButton_Pressed);
	connect(saveExitBtn, &QPushButton::released, this, &editWindow::exitButton_Released);


}


/* Function: exitButton_Pressed

		Slot to handle save and exit button being pressed
*/
void editWindow::exitButton_Pressed()
{
	saveExitBtn->setStyleSheet(GUI_Stylesheet.buttonPressed);
}

/* Function: exitButton_Released

		Slot to handle save and exit button is released.
*/
void editWindow::exitButton_Released()
{
	saveExitBtn->setStyleSheet(GUI_Stylesheet.buttonIdle);
	close();
}
