#include "situationalPage.h"
#include <QDebug>

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

    // set layout
    mainVLayout = new QVBoxLayout();
    mainVLayout->setContentsMargins(0, 0, 0, 0);
    mainVLayout->setSpacing(0);
    //mainVLayout->addWidget(exeTimer, 0, Qt::AlignCenter);
    //mainVLayout->addWidget(startBtn, 0, Qt::AlignCenter);
    //mainVLayout->addWidget(pauseResumeBtn, 0, Qt::AlignCenter);

    setLayout(mainVLayout);


    // connect signals
    //connect(startBtn, &QPushButton::pressed, this, &IntervalTimer::startButton_Pressed);
   
    // set stylesheet for each object
    //exeTimer->setStyleSheet(GUI_Style.mainTimer);
    setStyleSheet(GUI_Style.mainWindowIdle);

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