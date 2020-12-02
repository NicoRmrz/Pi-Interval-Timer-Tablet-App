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
#define ICONBUTTON      QString("rgba(0,0,0,0)")
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

	bjjMoveBox = "font: 150px Bold Courier New; "
				"color: white;"
				"background-color: " + TABHOVER + "; "
				"border-width: 20px; "
				"border-radius: 60px; "
				"border-color:  " + TABHOVER + ";"
				"border-style: outset;";

	bjjMoveBox_pressed = "font: 150px Bold Courier New; "
				"color: white;"
				"background-color: " + ICONPRESSED + "; "
				"border-width: 20px; "
				"border-radius: 60px; "
				"border-color:  " + ICONPRESSED + ";"
				"border-style: outset;";

	moveList =  "QListWidget {"
		"font: 22px Verdana; "
		"color: white;"
		"background-color: " + TABHOVER + "; "
	/*	"border-style: dashed; "
		"border-radius: 4px; "
		"border-width: 4px; "
		"border-color: black;"*/
		"border: none; "
		"padding: 9px;}"
		"QListWidget::item {"
		"border: none;}"
		"QListWidget::item:selected {"
		"font: 22px Verdana; "
		"color: black;"
		"background-color: #add8e6;}";

	splitterClosed = "QSplitter::handle {image:url(:/images/icons/splitterOpen.png);}"
		                "QSplitter::handle:horizontal{width: 50px; }"
                        "QSplitter::handle:vertical{height: 50px; }"
                        "QSplitter::handle:pressed{image:url(:/images/icons/splitterBoth.png); "
                        "background-color: " + ICONPRESSED + "; }";

	splitter = "QSplitter::handle {image:url(:/images/icons/splitterBoth.png);}"
		            "QSplitter::handle:horizontal{width: 50px; }"
		            "QSplitter::handle:vertical{height: 50px; }"
		            "QSplitter::handle:pressed{image:url(:/images/icons/splitterBoth.png); "
						            "background-color: " + ICONPRESSED + "; }";

    mainTimer = "font: 220px Bold Courier New; "
                    "color: white;"
                    "border: none";

    timerState = "font:  50px 'Times New Roman'; "
                    "color: white;"
                    "border: none";

	iconBtn = "background-color: " + TABHOVER +" ;"
					//"border:none; "
					"border-style: outset; "
					"border-width: 20px; "
					"border-radius: 60px; "
					"border-color:  " + TABHOVER + ";";

	iconBtn1 = "background-color: " + TABHOVER + ";"
				"border-style: outset; "
				"border-width: 20px; "
				"border-radius: 60px; "
				"border-color:  " + TABHOVER + ";";

	iconBtnPressed = "background-color: " + ICONPRESSED + "; "
					"border-style: outset; "
					"border-width: 20px; "
					"border-color: " + ICONPRESSED + ";"
					"border-radius: 60px";

    iconOnlyButton = "background-color: " + ICONBUTTON + "; "
					"border: none; ";

    buttonPressed = "font: 30px Bold Courier New; "
						"color: white;"
                        "background-color: rgb(100,100,100); "
                        "border-radius: 4px";

	buttonIdle = "font: 30px Bold Courier New; "
						"color: white;"
						"background-color: " + TABHOVER +"; "
						"border-radius: 4px";

	optionsLabel = "font: 25px Bold Courier New; "
		"color: white;"
		"background-color: " + BUTTONPRESSED + "; "
		"border: none";

    statusBar = "QStatusBar { background:  rgba(100,100,100,0);"
                "color:white; border:none;"
                "font: 11px Verdana; } "
                "QStatusBar::item {border: none; "
                "font: 11px Verdana;  "
                "border-radius: 3px; }";
    
    comboBox = "QComboBox {border: 1px solid gray;"
        "font: 30px Verdana;"
          "border-radius: 3px;"
    //  " background: white;"
       " padding: 1px 18px 1px 3px;"
       "min-width: 55px;}"

      "  QComboBox:editable{background: white;  }"

       " QComboBox:!editable, QComboBox::drop-down:editable{"
           "  background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,"
                                     "    stop : 0 #E1E1E1, stop: 0.4 #DDDDDD,"
                                     "    stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);}"

        /* QComboBox gets the "on" state when the popup is open */
 /*      " QComboBox:!editable:on, QComboBox::drop-down:editable:on{"
         "   background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,"
                "                        stop : 0 #D3D3D3, stop: 0.4 #D8D8D8,"
                "                        stop: 0.5 #DDDDDD, stop: 1.0 #E1E1E1);}"*/

      //"  QComboBox:on{ "/* shift the text when the popup opens */
      //    "  padding-top: 3px;"
      //       //   "font: 40px Verdana;"
      //           "padding-left: 4px;}"

        " QComboBox::indicator{"
            " background-color:transparent;"
            " selection-background-color:transparent;"
            " color:transparent;"
            " selection-color:transparent;}"

    // "   QComboBox:item{ background: white; }"

     "   QComboBox::item:selected:!active, QComboBox::item:selected:active{"
       "  border: 2px solid black;"
     //  "  background-color: black;"
        " background: black;}"

        "QComboBox:item::hover{ background: blue; "
        "color: blue;"
        "background-color: blue;}"

        "QComboBox::drop-down{"
            " subcontrol-origin: padding;"
            " subcontrol-position: top right;"
            " width: 15px;"
            // "  background: white;"
            "  background-color: white;"
            " border-left-width: 1px;"
            " border-left-color: darkgray;"
            " border-left-style: solid;" /* just a single line */
            " border-top-right-radius: 3px;" /* same radius as the QComboBox */
            "border-bottom-right-radius: 3px;}";

	spinBox = "QSpinBox { padding-right: 10px;" /* make room for the arrows */
		"color:white;"
		"font: 30px Verdana;"
		"border: none;}"

		"QSpinBox::up-button{subcontrol-origin: border;"
		"subcontrol-position: top right;" /* position at the top right corner */
	//	"border-position: top;"
		"padding-right: 10px;"
		//"padding: 1px;"
		"border-radius: 3px;"
		"border-color: black;"
		"width: 25px;"
		"height: 25px;";
		//"border-image: url(:/images/icons/splitterBoth.png) 1;}";
		//"border-width: 1px;}";
		
			/*	"QSpinBox::up-arrow {image: url(:/images/icons/splitterBoth.png);"
					"width: 25px;"
					"height: 25px;}";*/
				
}
