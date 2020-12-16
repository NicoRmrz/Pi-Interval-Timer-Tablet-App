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
situationalGame::situationalGame(QWidget *parent) 
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

    moveListWidget = new QListWidget(parent);
    moveListWidget->setDragEnabled(true);
    moveListWidget->setAcceptDrops(false);
    moveListWidget->setAutoScroll(true);
    moveListWidget->setDropIndicatorShown(true);
    moveListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    moveListWidget->setDefaultDropAction(Qt::MoveAction);
	moveListWidget->setMinimumWidth(0);
	moveListWidget->setMaximumWidth(0);
	moveListWidget->setFixedWidth(0);    
    moveListWidget->setViewMode(QListView::ListMode);
    moveListWidget->setWordWrap(true);
    moveListWidget->setResizeMode(QListWidget::Adjust);
    moveListWidget->setSelectionMode(QListWidget::SingleSelection);
    moveListWidget->setFlow(QListView::TopToBottom);
    moveListWidget->setMovement(QListView::Free);
    moveListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    moveListWidget->setDragDropMode(QAbstractItemView::NoDragDrop);
    moveListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    moveListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

	mainLayout = new QHBoxLayout();
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setSpacing(0);
	mainLayout->addWidget(backBtn, 0, Qt::AlignTop);
	mainLayout->addWidget(bjjBtn, 0, Qt::AlignCenter);

	leftContainer = new QWidget(parent);
	leftContainer->setLayout(mainLayout);

	horizontalSplitter = new QSplitter(parent);
	horizontalSplitter->addWidget(leftContainer);
	horizontalSplitter->addWidget(moveListWidget);
	horizontalSplitter->handle(1)->installEventFilter(this);

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
	connect(moveListWidget, &QListWidget::itemClicked, this, &situationalGame::moveListItemClicked);

    // set stylesheet for each object
    parent->setStyleSheet(mainWindowGrey);
	backBtn->setStyleSheet(iconOnlyButton);
	bjjBtn->setStyleSheet(bjjMoveBoxSTYLE);
    moveListWidget->setStyleSheet(moveListSTYLE);
	horizontalSplitter->setStyleSheet(splitterClosed);

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
        bjjMove inputMove;
        inputMove.position = json_arr.at(i)["Name"].toString();
        inputMove.level = json_arr.at(i)["Level"].toString();
        inputMove.position.replace(" ", "\n");

		if (inputMove.level != "Beginner")
		{
			bjjMoveList.append(inputMove);
			populateMoveList(inputMove.position, inputMove.level);
		}
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
    moveListWidget->addItem(item);                // add item to QListWidget
    moveListWidget->scrollToBottom();
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
	bjjBtn->setStyleSheet(bjjMoveBox_pressed);
}

/* Function: bjjButton_Released

		Slot to handle back button is released.
*/
void situationalGame::bjjButton_Released()
{
    int randomNum = rand() % bjjMoveList.size();
    moveListWidget->setCurrentRow(randomNum);

    bjjBtn->setText(bjjMoveList[randomNum].position);
	bjjBtn->setStyleSheet(bjjMoveBoxSTYLE);
}

/* Function: eventFilter

		Function to handle QSplitter handle press to open/close qlistwidget
*/
bool situationalGame::eventFilter(QObject * obj, QEvent * event)
{
	if (event->type() == QEvent::MouseButtonPress)
	{
		//QMouseEvent* me = QMouseEvent*(event);
		//int p = me->globalX();

		if (splitterOpen)
		{
			horizontalSplitter->setStyleSheet(splitterClosed);
			splitterOpen = false;

			for (int i = 0; i < 5; i++)
			{
				moveListWidget->setMinimumWidth(0);
				moveListWidget->setMaximumWidth(0);
				moveListWidget->setFixedWidth(0);
			}
		}
		else
		{
			horizontalSplitter->setStyleSheet(splitterSTYLE);
			splitterOpen = true;

			for (int i = 0; i < 5; i++)
			{
				moveListWidget->setMinimumWidth(150);
				moveListWidget->setMaximumWidth(150);
				moveListWidget->setFixedWidth(150);
			}
		}
	}

	return false;
}

/* Function: moveListItemClicked

		Slot to handle a single click on a bjj move in the layer order QListWidget
*/
void situationalGame::moveListItemClicked(QListWidgetItem* listWidgetItem)
{
	bjjBtn->setText(listWidgetItem->text());
}
