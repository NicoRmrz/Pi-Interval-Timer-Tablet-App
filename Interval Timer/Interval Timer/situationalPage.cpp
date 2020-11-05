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
    GUI_Stylesheet(parent)
{
    splitterOpen = false;

	setFixedSize(QSize(parent->size()));

    backBtn = new QPushButton(parent);
    backBtn->setObjectName(QString::fromUtf8("back"));
    backBtn->setMinimumSize(BACKICONSIZE, BACKICONSIZE);
    backBtn = new QPushButton(parent);
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
    moveListWidget->setMaximumWidth(150);
    moveListWidget->setLineWidth(0);
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
	//horizontalSplitter->setAttribute(Qt::WA_AcceptTouchEvents);
	
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
    parent->setStyleSheet(GUI_Stylesheet.mainWindowGrey);
	backBtn->setStyleSheet(GUI_Stylesheet.iconOnlyButton);
	bjjBtn->setStyleSheet(GUI_Stylesheet.bjjMoveBox);
    moveListWidget->setStyleSheet(GUI_Stylesheet.moveList);
	horizontalSplitter->setStyleSheet(GUI_Stylesheet.splitterClosed);

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
	bjjBtn->setStyleSheet(GUI_Stylesheet.bjjMoveBox_pressed);
}
/* Function: bjjButton_Released

		Slot to handle back button is released.
*/
void situationalGame::bjjButton_Released()
{
    int randomNum = rand() % bjjMoveList.size();
    moveListWidget->setCurrentRow(randomNum);

    bjjBtn->setText(bjjMoveList[randomNum].position);
	bjjBtn->setStyleSheet(GUI_Stylesheet.bjjMoveBox);
}

/* Function: splitterHasMoved

        Function to change splitter icon when collapsed
*/
void situationalGame::splitterHasMoved(int pos, int index)
{
    if (pos > 720) // splitter closed
    {
        horizontalSplitter->setStyleSheet(GUI_Stylesheet.splitterClosed);
        splitterOpen = false;
    }
    else
    {
        if (splitterOpen == false)
        {
            horizontalSplitter->setStyleSheet(GUI_Stylesheet.splitter);
            splitterOpen = true;
        }
    }
}

bool situationalGame::event(QEvent* event)
{
    if (event->type() == QEvent::TouchBegin)
    {
	QTouchEvent::TouchPoint touchPoint;
	qDebug() << "Touch";
    }
    else if (event->type() == QEvent::MouseButtonPress)
    {
	QTouchEvent::TouchPoint touchPoint;
	qDebug() << "MOUSE Touch";
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
	QTouchEvent::TouchPoint touchPoint;
	qDebug() << "MOUSE release";
    }
    else if (event->type() == QEvent::MouseTrackingChange)
    {
	QTouchEvent::TouchPoint touchPoint;
	qDebug() << "MOUSE move";
    }
    QWidget::event(event);
    return true;
}

//~ bool situationalGame::eventFilter(QObject* obj, QEvent* event)
//~ {
    //~ if (event->type() == QEvent::MouseButtonPress
        //~ || event->type() == QEvent::MouseButtonRelease
        //~ || event->type() == QEvent::MouseButtonDblClick
        //~ || event->type() == QEvent::MouseMove) {
	    
	//~ QMouseEvent* ev = static_cast<QMouseEvent*>(event);
        //~ if (ev->type() == QEvent::MouseMove && !(ev->buttons() & Qt::LeftButton))
            //~ return false;

        //~ QTouchEvent::TouchPoint touchPoint;
        //~ touchPoint.setState(Qt::TouchPointMoved);
        //~ if ((ev->type() == QEvent::MouseButtonPress || ev->type() == QEvent::MouseButtonDblClick))
            //~ touchPoint.setState(Qt::TouchPointPressed);
        //~ else if (ev->type() == QEvent::MouseButtonRelease)
            //~ touchPoint.setState(Qt::TouchPointReleased);

        //~ touchPoint.setId(0);
        //~ touchPoint.setScreenPos(ev->globalPos());
        //~ touchPoint.setPos(ev->pos());
        //~ touchPoint.setPressure(1);
	
	  //~ // If the point already exists, update it. Otherwise create it.
        //~ if (touchPoints.size() > 0 && !touchPoints[0].id())
            //~ touchPoints[0] = touchPoint;
        //~ else if (touchPoints.size() > 1 && !touchPoints[1].id())
            //~ touchPoints[1] = touchPoint;
        //~ else
            //~ touchPoints.append(touchPoint);

        //~ sendTouchEvent();
	//~ }
	//~ else if (event->type() == QEvent::KeyPress
        //~ && static_cast<QKeyEvent*>(event)->key() == Qt::Key_F
        //~ && static_cast<QKeyEvent*>(event)->modifiers() == Qt::ControlModifier) {

        //~ // If the keyboard point is already pressed, release it.
        //~ // Otherwise create it and append to touchPoints.
        //~ if (touchPoints.size() > 0 && touchPoints[0].id() == 1) {
            //~ touchPoints[0].setState(Qt::TouchPointReleased);
            //~ sendTouchEvent();
        //~ } else if (touchPoints.size() > 1 && touchPoints[1].id() == 1) {
            //~ touchPoints[1].setState(Qt::TouchPointReleased);
            //~ sendTouchEvent();
        //~ } else {
            //~ QTouchEvent::TouchPoint touchPoint;
            //~ touchPoint.setState(Qt::TouchPointPressed);
            //~ touchPoint.setId(1);
            //~ touchPoint.setScreenPos(QCursor::pos());
          //~ //  touchPoint.setPos(m_view->mapFromGlobal(QCursor::pos()));
            //~ touchPoint.setPressure(1);
            //~ touchPoints.append(touchPoint);
            //~ sendTouchEvent();

            //~ // After sending the event, change the touchpoint state to stationary
            //~ touchPoints.last().setState(Qt::TouchPointStationary);
        //~ }
    //~ }
    //~ return false;
//~ }

//~ void situationalGame::sendTouchEvent()
//~ {
    //~ if (touchPoints.isEmpty())
        //~ return;

    //~ QEvent::Type type = QEvent::TouchUpdate;
    //~ if (touchPoints.size() == 1) {
        //~ if (touchPoints[0].state() == Qt::TouchPointReleased)
            //~ type = QEvent::TouchEnd;
        //~ else if (touchPoints[0].state() == Qt::TouchPointPressed)
            //~ type = QEvent::TouchBegin;
    //~ }

    //~ QTouchEvent touchEv(type);
    //~ touchEv.setTouchPoints(touchPoints);
    //~ //QCoreApplication::sendEvent(horizontalSplitter, &touchEv);

    //~ // After sending the event, remove all touchpoints that were released
    //~ if (touchPoints[0].state() == Qt::TouchPointReleased)
        //~ touchPoints.removeAt(0);
    //~ if (touchPoints.size() > 1 && touchPoints[1].state() == Qt::TouchPointReleased)
        //~ touchPoints.removeAt(1);
//~ }
