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
#define MAINBACKGROUND  QString("rgba(49, 51, 53, 240)")
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
    mainWindow = "background-color: "+ MAINBACKGROUND+ "; ";

   
}
