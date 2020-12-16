#pragma once
#include <QWidget>
#include <QObject>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include "GUI_Stylesheet.h"


/* Class: editWindow

	QDialog pop up window
*/
class editWindow : public QDialog
{
	Q_OBJECT

public:
	editWindow(QDialog *parent);
	~editWindow() {};
	QVBoxLayout *mainVLayout;
	QSpinBox	*rollSecondInput;
	QSpinBox	*restSecondInput;
	QSpinBox	*rollMinuteInput;
	QSpinBox	*restMinuteInput;
	QLabel		*restLabel;
	QLabel		*rollLabel;
	QVBoxLayout *restLayout;
	QVBoxLayout *rollLayout;
	QHBoxLayout *restOptionsLayout;
	QHBoxLayout *rollOptionsLayout;
	QPushButton	*saveExitBtn;

public slots:		
	void exitButton_Pressed();
	void exitButton_Released();
};
