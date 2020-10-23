/* File: situationalPage.cpp

Contains functions for situational page.

Author: Nico Ramirez
*/
#include "situationalPage.h"
#include <QDebug>
#include <string>

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
    splitterOpen = false;

	setFixedSize(QSize(parent->size()));

	backBtn = new QPushButton(parent);
	backBtn->setObjectName(QString::fromUtf8("back"));
	backBtn->setMinimumSize(BACKICONSIZE, BACKICONSIZE);
	backBtn->setMaximumSize(BACKICONSIZE, BACKICONSIZE);
	backBtn->setIcon(QIcon(backIcon2));
	backBtn->setIconSize(QSize(BACKICONSIZE, BACKICONSIZE));

	bjjBtn = new QPushButton(parent);
	bjjBtn->setText("touch");
	bjjBtn->setMaximumHeight(400);

	moveList = new QListWidget(parent);
	moveList->setDragEnabled(true);
	moveList->setAcceptDrops(true);
	moveList->setAutoScroll(false);
	moveList->setDropIndicatorShown(true);
	moveList->setDefaultDropAction(Qt::MoveAction);
	moveList->setMaximumWidth(150);
	moveList->setLineWidth(0);
	moveList->setViewMode(QListView::ListMode);
	moveList->setWordWrap(true);
	moveList->setResizeMode(QListWidget::Adjust);
	moveList->setSelectionMode(QListWidget::SingleSelection);
	moveList->setFlow(QListView::TopToBottom);
	moveList->setMovement(QListView::Free);
	moveList->setSelectionBehavior(QAbstractItemView::SelectRows);
	moveList->setDragDropMode(QAbstractItemView::NoDragDrop);
	moveList->setSelectionMode(QAbstractItemView::SingleSelection);

	mainLayout = new QHBoxLayout();
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setSpacing(0);
	mainLayout->addWidget(backBtn, 0, Qt::AlignTop);
	mainLayout->addWidget(bjjBtn, 0, Qt::AlignCenter);

	leftContainer = new QWidget(parent);
	leftContainer->setLayout(mainLayout);

	horizontalSplitter = new QSplitter(parent);
	horizontalSplitter->addWidget(leftContainer);
	horizontalSplitter->addWidget(moveList);
    QList<int> sizes;
    sizes << 0 ;
	horizontalSplitter->setSizes(sizes);

    // set layout
    mainHLayout = new QHBoxLayout();
	mainHLayout->setContentsMargins(0, 0, 10, 0);
	mainHLayout->setSpacing(0);
	mainHLayout->addWidget(horizontalSplitter);

    setLayout(mainHLayout);

    // connect signals
	connect(backBtn, &QPushButton::pressed, this, &situationalGame::backButton_Pressed);
	connect(backBtn, &QPushButton::released, this, &situationalGame::backButton_Released);
	connect(bjjBtn, &QPushButton::pressed, this, &situationalGame::bjjButton_Pressed);
	connect(bjjBtn, &QPushButton::released, this, &situationalGame::bjjButton_Released);
	connect(horizontalSplitter, &QSplitter::splitterMoved, this, &situationalGame::splitterHasMoved);

    // set stylesheet for each object
    parent->setStyleSheet(GUI_Style.mainWindowGrey);
	backBtn->setStyleSheet(GUI_Style.iconOnlyButton);
	bjjBtn->setStyleSheet(GUI_Style.bjjMoveBox);
	moveList->setStyleSheet(GUI_Style.moveList);
	horizontalSplitter->setStyleSheet(GUI_Style.splitterClosed);

    getMoveList(JSONmoveList);
}

/* Define: getMoveList

    Get bjj moves list and store them in QMap

 */
void situationalGame::getMoveList(QString inputFile)
{
    // read in JSON file
    QString val;
    QFile file;
    file.setFileName(inputFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        val = file.readAll();
        file.close();
    }
    else
    {
        emit sendStatusBar("Unable to open file", 5000);
    }

    // Convert Data read in to QJSON Document
    QJsonDocument JSONdoc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject json_obj = JSONdoc.object();
    QJsonValue json_Val = json_obj.value(QString("bjjPosition"));

    // set JSON array to class variabel
    json_arr = json_Val.toArray();

    for (int i = 0; i < json_arr.size(); i++)
    {
        QString position = json_arr.at(i)["Name"].toString();
        QString level = json_arr.at(i)["Level"].toString();

        populateMoveList(position, level);
    }

}

/* Function: populateMoveList

		Function to populate move list widget
*/
void situationalGame::populateMoveList(QString move, QString difficulty)
{
	QListWidgetItem *item;

	item = new QListWidgetItem(tr(""));
	item->setData(Qt::UserRole, difficulty);    // set path to backend data for later retireval
	item->setText(move);            // set for image icon to be dropped
	moveList->addItem(item);                // add item to QListWidget
	moveList->scrollToBottom();
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

/* Function: bjjButton_Pressed

		Slot to handle backbutton being pressed
*/
void situationalGame::bjjButton_Pressed()
{
	// color button green indicating pressed button
	bjjBtn->setStyleSheet(GUI_Style.bjjMoveBox_pressed);
}
/* Function: bjjButton_Released

		Slot to handle back button is released.
*/
void situationalGame::bjjButton_Released()
{


	bjjBtn->setStyleSheet(GUI_Style.bjjMoveBox);
}

/* Function: splitterHasMoved

        Function to change splitter icon when collapsed
*/
void situationalGame::splitterHasMoved(int pos, int index)
{
    if (pos > 720) // splitter closed
    {
        horizontalSplitter->setStyleSheet(GUI_Style.splitterClosed);
        splitterOpen = false;
    }
    else
    {
        if (splitterOpen == false)
        {
            horizontalSplitter->setStyleSheet(GUI_Style.splitter);
            splitterOpen = true;
        }
    }
}