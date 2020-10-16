/* File: GUI_Stylesheet.h

    Creates the custom string per UI object for the objects setStylsheet()

    Author: Nico Ramirez
*/
#pragma once
#include <qstring.h> 
#include <qobject.h> 

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
    QString mainTimer;
    QString intervalTimerBtn;
    QString situationalBtn;
    QString buttonPressed;
    QString statusBar;

};

