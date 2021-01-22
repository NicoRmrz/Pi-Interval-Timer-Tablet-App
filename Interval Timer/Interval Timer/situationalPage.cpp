/* File: situationalPage.cpp

Contains functions for situational page.

Author: Nico Ramirez
*/
#include "situationalPage.h"
#include <QDebug>
#include <string>

#define BEGINNER 0
#define ADVANCED 1

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
    backBtn->setIconSize(QSize(BACKICONSIZE, BACKICONSIZE));
    backBtn->setFocusPolicy(Qt::NoFocus);

    bjjBtn = new QPushButton(parent);
    bjjBtn->setText("start");
    bjjBtn->setMaximumHeight(400);
    bjjBtn->setFocusPolicy(Qt::NoFocus);

    beginnerDiffButton = new QPushButton(parent);
    beginnerDiffButton->setMinimumSize(DIFFICULTY_BUTTON_WIDTH, DIFFICULTY_BUTTON_HEIGHT);
    beginnerDiffButton->setMaximumSize(DIFFICULTY_BUTTON_WIDTH, DIFFICULTY_BUTTON_HEIGHT);
    beginnerDiffButton->setIconSize(QSize(DIFFICULTY_BUTTON_WIDTH, DIFFICULTY_BUTTON_HEIGHT));
    beginnerDiffButton->setText("Beginner");
    beginnerDiffButton->setCheckable(true);
    beginnerDiffButton->setFocusPolicy(Qt::NoFocus);

    advancedDiffButton = new QPushButton(parent);
    advancedDiffButton->setMinimumSize(DIFFICULTY_BUTTON_WIDTH, DIFFICULTY_BUTTON_HEIGHT);
    advancedDiffButton->setMaximumSize(DIFFICULTY_BUTTON_WIDTH, DIFFICULTY_BUTTON_HEIGHT);
    advancedDiffButton->setIconSize(QSize(DIFFICULTY_BUTTON_WIDTH, DIFFICULTY_BUTTON_HEIGHT));
    advancedDiffButton->setText("Advanced");
    advancedDiffButton->setCheckable(true);
    advancedDiffButton->setFocusPolicy(Qt::NoFocus);

    // start on advanced
    beginnerDiffButton->setChecked(true);
    beginnerDiffButton->setDown(true);

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
    moveListWidget->setAlternatingRowColors(true);
    moveListWidget->setFocusPolicy(Qt::NoFocus);

    buttonLayout = new QHBoxLayout();
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->setSpacing(0);
    buttonLayout->addWidget(beginnerDiffButton, 1, Qt::AlignRight);
    buttonLayout->addWidget(advancedDiffButton, 1, Qt::AlignLeft);

    mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(backBtn, 0, Qt::AlignTop);
    mainLayout->addLayout(buttonLayout, Qt::AlignCenter);

    mainVLayout = new QVBoxLayout();
    mainVLayout->setContentsMargins(0, 0, 0, 0);
    mainVLayout->setSpacing(0);
    mainVLayout->addLayout(mainLayout);
    mainVLayout->addWidget(bjjBtn, 1, Qt::AlignCenter);

	leftContainer = new QWidget(parent);
	leftContainer->setLayout(mainVLayout);

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
	connect(beginnerDiffButton, &QPushButton::pressed, this, &situationalGame::beginnerBtnPressed);
	connect(advancedDiffButton, &QPushButton::pressed, this, &situationalGame::advBtnPressed);
	connect(backBtn, &QPushButton::released, this, &situationalGame::backButton_Released);
	connect(bjjBtn, &QPushButton::released, this, &situationalGame::bjjButton_Released);
	connect(moveListWidget, &QListWidget::itemClicked, this, &situationalGame::moveListItemClicked);

    // set stylesheet for each object
    parent->setStyleSheet(mainWindowGrey);
    backBtn->setStyleSheet(backButtonStyle);
    bjjBtn->setStyleSheet(bjjMoveBoxSTYLE);
    moveListWidget->setStyleSheet(moveListSTYLE);
    horizontalSplitter->setStyleSheet(splitterClosed);
    beginnerDiffButton->setStyleSheet(difficultybuttonsSTYLE);
    advancedDiffButton->setStyleSheet(difficultybuttonsSTYLE);

    getMoveList(JSONmoveList, ADVANCED);
}

/* Define: getMoveList

    Get bjj moves list and store them in QMap

 */
void situationalGame::getMoveList(QString inputFile, int type)
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



		if (type == BEGINNER)
		{
            if (inputMove.level != "Advanced")
            {
                bjjMoveList.append(inputMove);
                populateMoveList(inputMove.position, inputMove.level);
            }
		}
        //else if(inputMove.level != "ALL" || inputMove.level != "Advanced")
        else if (type == ADVANCED)
        {
            if (inputMove.level != "Beginner")
            {
                bjjMoveList.append(inputMove);
                populateMoveList(inputMove.position, inputMove.level);
            }
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
    item->setText(move);
    moveListWidget->addItem(item);                // add item to QListWidget
    moveListWidget->scrollToBottom();
}

/* Function: beginnerBtnPressed

        Slot to handle difficulty push button pressed. RadioButton style like function
*/
void situationalGame::beginnerBtnPressed()
{
    if (!beginnerDiffButton->isChecked())
    {
        beginnerDiffButton->setChecked(true);
        beginnerDiffButton->setDown(true);
    }
    else
    {
        moveListWidget->clear();
        getMoveList(JSONmoveList, BEGINNER);
        advancedDiffButton->setChecked(true);
        advancedDiffButton->setDown(true);
    }
}

/* Function: advBtnPressed

    Slot to handle difficulty push button pressed. RadioButton style like function
*/
void situationalGame::advBtnPressed()
{
    if (!advancedDiffButton->isChecked())
    {
        advancedDiffButton->setChecked(true);
        advancedDiffButton->setDown(true);
    }
    else
    {
        moveListWidget->clear();
        getMoveList(JSONmoveList, ADVANCED);
        beginnerDiffButton->setChecked(true);
        beginnerDiffButton->setDown(true);
    }
}


/* Function: backButton_Released

		Slot to handle back button is released.
*/
void situationalGame::backButton_Released()
{
	emit returnPage("situational");
}

/* Function: bjjButton_Released

		Slot to handle back button is released.
*/
void situationalGame::bjjButton_Released()
{
    int randomNum = rand() % bjjMoveList.size();
    moveListWidget->setCurrentRow(randomNum);

    int size = bjjMoveList[randomNum].position.size();
    if (size >= 10)
    {
        bjjBtn->setStyleSheet(bjjMoveBoxSTYLE_SMALL);
    }
    else
    {
        bjjBtn->setStyleSheet(bjjMoveBoxSTYLE);

    }

    bjjBtn->setText(bjjMoveList[randomNum].position);
}

/* Function: eventFilter

		Function to handle QSplitter handle press to open/close qlistwidget
*/
bool situationalGame::eventFilter(QObject * obj, QEvent * event)
{
	if (event->type() == QEvent::MouseButtonPress)
	{
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
    int size = listWidgetItem->text().size();
    if (size >= 9)
    {
        bjjBtn->setStyleSheet(bjjMoveBoxSTYLE_SMALL);
    }
    else
    {
        bjjBtn->setStyleSheet(bjjMoveBoxSTYLE);

    }

	bjjBtn->setText(listWidgetItem->text());
}

/* Function: playSound

       PlaySound Tone
*/
void situationalGame::playSound(QString sound)
{
    soundProcess = new QProcess(this);
    soundProcess->start(sound);
}
