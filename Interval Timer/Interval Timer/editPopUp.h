#pragma once
#include <QWidget>
#include <QObject>
#include <QDialog>
#include <QIcon>
#include <QVBoxLayout>
#include <QComboBox>
#include <QScroller>
#include <QSpinBox>
#include <QSlider>
#include "GUI_Stylesheet.h"

#define MAIN_ICON QString(":/images/icons/specific/bjj_stand_up.PNG")

/* Class: editWindow

	QDialog pop up window
*/
class editWindow : public QDialog
{
	Q_OBJECT

public:
	editWindow(QDialog *parent);
	~editWindow() {};
	GUI_Style    GUI_Stylesheet;
	QVBoxLayout *mainVLayout;
	QComboBox	*rollSecondInput;
	QComboBox	*restSecondInput;
	QSpinBox	*rollMinuteInput;
	QSlider		*restMinuteInput;

private:
	void setComboBoxes(void);

};
