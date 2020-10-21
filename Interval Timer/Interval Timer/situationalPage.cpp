/* File: situationalPage.cpp

Contains functions for situational page.

Author: Nico Ramirez
*/
#include "situationalPage.h"
#include <QDebug>

QString backIcon2 = ":/images/icons/back.png";
QString backIconPressed2= ":/images/icons/backPressed.png";

using namespace std;

/* Constructor: situationalGame

        Lays out all objects for the Situational page

    Parameters:

        parent - Inherits QWidget attributes
*/
situationalGame::situationalGame(QWidget *parent) :
    GUI_Style(parent)
{
	setFixedSize(QSize(parent->size()));

	backBtn = new QPushButton(parent);
	backBtn->setObjectName(QString::fromUtf8("back"));
	backBtn->setMinimumSize(BACKICONSIZE, BACKICONSIZE);
	backBtn->setMaximumSize(BACKICONSIZE, BACKICONSIZE);
	backBtn->setIcon(QIcon(backIcon2));
	backBtn->setIconSize(QSize(BACKICONSIZE, BACKICONSIZE));

    // set layout
    mainVLayout = new QVBoxLayout();
    mainVLayout->setContentsMargins(0, 0, 0, 0);
    mainVLayout->setSpacing(0);
	mainVLayout->addWidget(backBtn, 0, Qt::AlignLeft);

    //mainVLayout->addWidget(exeTimer, 0, Qt::AlignCenter);
    //mainVLayout->addWidget(startBtn, 0, Qt::AlignCenter);
    //mainVLayout->addWidget(pauseResumeBtn, 0, Qt::AlignCenter);

    setLayout(mainVLayout);


    // connect signals
	connect(backBtn, &QPushButton::pressed, this, &situationalGame::backButton_Pressed);
	connect(backBtn, &QPushButton::released, this, &situationalGame::backButton_Released);

    // set stylesheet for each object
    parent->setStyleSheet(GUI_Style.mainWindowRoll);
	backBtn->setStyleSheet(GUI_Style.iconOnlyButton);

    getMoveList();
}

/* Define: getMoveList

    Get bjj moves list and store them in QMap

 */
void situationalGame::getMoveList()
{

    QString filename = "bjjMoveList.txt";
    QFile myFile(filename);

    if (myFile.open(QIODevice::ReadOnly))
    {
        // read each line of template file 
        while (!myFile.atEnd())
        {
            // read each line from template and write on newfile
            QString line = myFile.readLine();
            line.remove("\r\n");
            QStringList item = line.split(", ");
            qDebug() << item[0] << ", " << item[1];

        }

    }
    else
    {
        emit sendStatusBar("Unable to open file", 5000);
    }

}


/* Function: backButton_Pressed

		Slot to handle backbutton being pressed
*/
void situationalGame::backButton_Pressed()
{
	// color button green indicating pressed button
	backBtn->setIcon(QIcon(backIconPressed2));
}
/* Function: backButton_Released

		Slot to handle back button is released.
*/
void situationalGame::backButton_Released()
{
	backBtn->setIcon(QIcon(backIcon2));
	emit returnPage("situational");
}

