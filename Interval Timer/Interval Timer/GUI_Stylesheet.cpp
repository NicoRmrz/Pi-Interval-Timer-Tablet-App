/* File: GUI_Stylesheet.cpp

    Creates the custom string per UI object for the objects setStylsheet()

    Author: Nico Ramirez
    Date: 1/2/2020
*/

#include <QObject>
#include <QString>
#include "GUI_Stylesheet.h"

/* Define: Color Scheme

    Color scheme for GUI Objects setStyleSheet rgba/ hex values
 */
//#define GREYBACKGROUND  QString("rgba(49, 51, 53, 240)")
#define GREYBACKGROUND  QString("#20292F")
#define GREENBACKGROUND QString("#07c40d")
#define REDBACKGROUND   QString("#E3242B")
#define BLUEBACKGROUND  QString("#6593F5")
#define ICONPRESSED		QString("rgba(72,146,73,240)")

#define TABHOVER        QString("rgba(38,79,120,255)")
#define BUTTONPRESSED   QString("rgb(100,100,100)")
#define UIBUTTON        QString("#6497b1")

/* Constructor: GUI_Style

        QObject class to hold all string customization of front end.
        To be called out by .setStyleSheet() function of each object

   Parameters:

        parent - Inherits QObject attributes
*/
GUI_Style::GUI_Style(QObject *parent) : QObject(parent)
{
    mainWindowGrey = "background-color: "+ GREYBACKGROUND + "; ";

    mainWindowRest = "background-color: "+ GREENBACKGROUND + "; ";

    mainWindowRoll = "background-color: "+ REDBACKGROUND + "; ";

    mainWindowIdle = "background-color: "+ BLUEBACKGROUND + "; ";

    mainTimer = "font: 200px Bold Courier New; "
                    "color: white;"
                    "border: none";

	iconBtn = "background-color: " + TABHOVER +" ;"
					//"border:none; "
					"border-style: outset; "
					"border-width: 20px; "
					"border-radius: 70px; "
					"border-color:  " + TABHOVER + ";";

	iconBtn1 = "background-color: " + TABHOVER + ";"
				"border-style: outset; "
				"border-width: 20px; "
				"border-radius: 70px; "
				"border-color:  " + TABHOVER + ";";

	iconBtnPressed = "background-color: " + ICONPRESSED + "; "
					"border-style: outset; "
					"border-width: 20px; "
					"border-color: " + ICONPRESSED + ";"
					"border-radius: 70px";

    situationalBtn = "font: bold 12px Verdana; "
                        //"background-color:  #6497b1; "
                         "background-color: #00A86B;"
                        //"background-color: #FADA5E;"
                        "border-radius: 4px";

    buttonPressed = "font: bold 20px Verdana; "
                        "background-color: rgb(100,100,100); "
                        "border-radius: 4px";


    statusBar = "QStatusBar { background:  rgba(100,100,100,0);"
                "color:white; border:none;"
                "font: 11px Verdana; } "
                "QStatusBar::item {border: none; "
                "font: 11px Verdana;  "
                "border-radius: 3px; }";

}
