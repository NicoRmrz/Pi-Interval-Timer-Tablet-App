/* File: GUI_Stylesheet.h

    Creates the custom string per UI object for the objects setStylsheet()

    Author: Nico Ramirez
*/
#pragma once
#include <qstring.h> 
#include <qobject.h> 

#define ICONSIZE 100
#define BACKICONSIZE 50

/* Class: GUI_Style

    QObject class to hold all strings customization of front end.
    To be called out by .setStyleSheet() function of each object
*/
class GUI_Style : public QObject
{
public:
    /* Function declarations */
    GUI_Style(QObject *parent);

    /* Variable declarations */
    QString mainWindowGrey;
    QString mainWindowRest;
    QString mainWindowRoll;
    QString mainWindowIdle;
    QString bjjMoveBox;
    QString bjjMoveBox_pressed;
    QString moveList;
    QString splitterClosed;
    QString splitter;
    QString mainTimer;
    QString iconBtn;
    QString iconBtn1;
    QString iconBtnPressed;
    QString iconOnlyButton;
    QString buttonPressed;
    QString buttonIdle;
    QString optionsLabel;
    QString statusBar;
    QString comboBox;
    QString timerState;
	QString spinBox;


};

