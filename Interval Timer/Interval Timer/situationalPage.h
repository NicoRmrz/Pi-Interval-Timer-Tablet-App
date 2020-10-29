#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QSplitter>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTouchEvent>
#include <QEvent>

#include "GUI_Stylesheet.h"

#define JSONmoveList ":/images/inputMoveList/bjjMoveList.json"

// struct of bjj moves and level of difficulty
struct bjjMove {
    QString position;
    QString level;
};

/* Class: IntervalTimer

    QWidget widget to hold all objects needed for IntervalTimer implementation
*/
class situationalGame : public QWidget
{
    Q_OBJECT

public:
    situationalGame(QWidget *parent);
    ~situationalGame() {};
    GUI_Style	GUI_Stylesheet;
    QPushButton	*backBtn;
    QHBoxLayout	*mainLayout;
    QHBoxLayout	*mainHLayout;
    QWidget		*leftContainer;
    QPushButton *bjjBtn;
    QListWidget	*moveListWidget;
    QSplitter	*horizontalSplitter;
    void getMoveList(QString inputFile);
    bool event (QEvent *event);
    //~ bool eventFilter(QObject* obj, QEvent* event);
    //~ void sendTouchEvent();

private:
	void populateMoveList(QString move, QString difficulty);
    QJsonArray json_arr;
    bool splitterOpen;
    QList<bjjMove> bjjMoveList;
    QList<QTouchEvent::TouchPoint> touchPoints;

public slots:
	void backButton_Pressed();
	void backButton_Released();	
	void bjjButton_Pressed();
	void bjjButton_Released();
	void splitterHasMoved(int pos, int index);

signals:
    void sendStatusBar(QString message, int time);
	void returnPage(QString page);

};
