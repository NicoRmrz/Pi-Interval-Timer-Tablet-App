/* File: GUI_Stylesheet.h

    Creates the custom string per UI object for the objects setStylsheet()

    Author: Nico Ramirez
*/
#pragma once
#include <QString>
#include "qstring.h"

#define ICONSIZE 100
#define BACKICONSIZE 50
#define MAIN_ICON QString(":/images/icons/specific/bjj_stand_up.PNG")

/* Define: Color Scheme

	Color scheme for GUI Objects setStyleSheet rgba/ hex values
 */
#define TITLECOLOR_BOT_BORDER		QString("rgba(212,175,55,150)")
#define TITLECOLOR			  		QString("rgba(255,223 ,88,200)")
#define GREYBACKGROUND  QString("#20292F")
#define GREENBACKGROUND QString("#07c40d")
#define REDBACKGROUND   QString("#E3242B")
#define BLUEBACKGROUND  QString("#6593F5")
#define ICONPRESSED		QString("rgba(72,146,73,240)")
#define ICONBUTTON      QString("rgba(0,0,0,0)")
#define TABHOVER        QString("rgba(38,79,120,255)")
#define TABHOVER_FADED        QString("rgba(38,79,120,150)")
#define BUTTONPRESSED   QString("rgb(100,100,100)")
#define UIBUTTON        QString("#6497b1")

#define mainWindowGrey	QString("background-color: " + GREYBACKGROUND + "; ")
#define mainWindowRest	QString("background-color: " + GREENBACKGROUND + "; ")
#define mainWindowRoll	QString("background-color: " + REDBACKGROUND + "; ")
#define mainWindowIdle	QString("background-color: " + BLUEBACKGROUND + "; ")

#define bjjMoveBoxSTYLE			QString("QPushButton {font: 150px Bold Courier New; "\
										            "color:  rgba(255,255,255,200);"\
										            "background-color: " + TABHOVER + "; "\
										            "border-width: 20px; "\
										            "border-radius: 60px; "\
										            "border-color:  " + TABHOVER + ";"\
										            "border-style: outset;}"\
                                         "QPushButton:pressed {font: 150px Bold Courier New; "\
										            "color: rgba(255,255,255,200);"\
										            "background-color: " + ICONPRESSED + "; "\
										            "border-width: 20px; "\
										            "border-radius: 60px; "\
										            "border-color:  " + ICONPRESSED + ";"\
										            "border-style: inset;}")

#define bjjMoveBoxSTYLE_SMALL   QString("QPushButton {font: 100px Bold Courier New; "\
										            "color:  rgba(255,255,255,200);"\
										            "background-color: " + TABHOVER + "; "\
										            "border-width: 20px; "\
										            "border-radius: 60px; "\
										            "border-color:  " + TABHOVER + ";"\
										            "border-style: outset;}"\
                                         "QPushButton:pressed {font: 100px Bold Courier New; "\
										            "color: rgba(255,255,255,200);"\
										            "background-color: " + ICONPRESSED + "; "\
										            "border-width: 20px; "\
										            "border-radius: 60px; "\
										            "border-color:  " + ICONPRESSED + ";"\
										            "border-style: inset;}")

#define moveListSTYLE			QString("QListWidget {"\
										"font: 22px Verdana; "\
										"color: white;"\
										"background-color: " + TABHOVER_FADED + "; "\
										"border: none; "\
										"alternate-background-color: "+TITLECOLOR_BOT_BORDER+"; }"\
										"QListWidget::item {"\
										"border: none;}"\
										"QListWidget::item:selected {"\
										"font: 22px Verdana; "\
										"color: black;"\
										"background-color: green;}")

#define splitterClosed	QString("QSplitter::handle {image:url(:/images/icons/splitterOpen.png);}"\
								"QSplitter::handle:horizontal{width: 50px; }"\
								"QSplitter::handle:vertical{height: 50px; }"\
								"QSplitter::handle:pressed{image:url(:/images/icons/splitterBoth.png); "\
								"background-color: " + ICONPRESSED + "; }")\

#define splitterSTYLE 	QString("QSplitter::handle {image:url(:/images/icons/splitterBoth.png);}"\
								"QSplitter::handle:horizontal{width: 50px; }"\
								"QSplitter::handle:vertical{height: 50px; }"\
								"QSplitter::handle:pressed{image:url(:/images/icons/splitterBoth.png); "\
								"background-color: " + ICONPRESSED + "; }")

#define mainTimer		QString("font: 220px Bold Courier New; "\
								"color: white;"\
								"border: none")

#define timerState		QString("font:  50px 'Times New Roman'; "\
								"color: white;"\
								"border: none")

#define iconBtn			QString("background-color: " + TABHOVER + " ;"\
								"border-style: outset; "\
								"border-width: 20px; "\
								"border-radius: 60px; "\
								"border-color:  " + TABHOVER + ";")

#define iconBtn1		QString("background-color: " + TABHOVER + ";"\
								"border-style: outset; "\
								"border-width: 20px; "\
								"border-radius: 60px; "\
								"border-color:  " + TABHOVER + ";")

#define iconBtnPressed	QString("background-color: " + ICONPRESSED + "; "\
								"border-style: outset; "\
								"border-width: 20px; "\
								"border-color: " + ICONPRESSED + ";"\
								"border-radius: 60px")

#define iconOnlyButton	QString("background-color: " + ICONBUTTON + "; "\
								"border: none; ")

#define buttonPressed	QString("font: 30px Bold Courier New; "\
								"color: white;"\
								"background-color: rgb(100,100,100); "\
								"border-radius: 4px")

#define buttonIdle		QString("font: 30px Bold Courier New; "\
								"color: white;"\
								"background-color: " + TABHOVER + "; "\
								"border-radius: 4px")

#define restOptLabel	QString("font: 30px'Times New Roman'; "\
								"color: white;"\
								"background-color: " + GREENBACKGROUND + "; "\
								"border: none")

#define rollOptLabel	QString("font: 30px'Times New Roman'; "\
								"color: white;"\
								"background-color: " + REDBACKGROUND + "; "\
								"border: none")

#define statusBarSTYLE	QString("QStatusBar { background:  rgba(100,100,100,0);"\
											"color:white; border:none;"\
											"font: 11px Verdana; } "\
								"QStatusBar::item {border: none; "\
												"font: 11px Verdana;  "\
												"border-radius: 3px; }")

#define spinBox			QString("QSpinBox { padding-right: 25px;"\
										"color:white;"\
										"font: 30px Verdana;"\
										"border: none;}"\
								"QSpinBox::up-button{subcontrol-origin: border;"\
										"subcontrol-position: top right;" \
										"border-image: url(:/images/icons/back.png);"\
										"width: 30px;"\
										"height: 30px;}")
							/*	"QSpinBox::up-arrow{image: url(:/images/icons/back.png);"\
										"width: 35px;"\
										"height: 25px;}")*/


#define appMainTitle    QString ("font: 40px'Times New Roman'; "\
								"color: "+TITLECOLOR+";"\
                                "border-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop: 0		" + GREYBACKGROUND + ", "\
																				"	   stop: 0.25	" + GREYBACKGROUND + ", "\
																				"	   stop: 0.5	" + TITLECOLOR_BOT_BORDER + ", "\
																				"	   stop: 0.75   " + GREYBACKGROUND + ", "\
																				"	   stop: 1		" + GREYBACKGROUND + "); "\
                                "border-top: none; "\
                                "border-right: none; "\
                                "border-left: none; "\
                                "border-style: double; "\
                                "border-bottom-width: 3px; ")				
