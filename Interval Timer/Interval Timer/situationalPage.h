#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QSplitter>
#include <QListWidget>
#include <QListWidgetItem>
#include <QEvent>
#include <QProcess>
//#include <QButtonGroup>

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
    QPushButton	*backBtn;
    QHBoxLayout	*mainLayout;
    QHBoxLayout	*mainHLayout;
    QVBoxLayout	*mainVLayout;
    QWidget		*leftContainer;
    QPushButton *bjjBtn;
    //QButtonGroup *buttongroup;
    QPushButton *beginnerDiffButton;
    QListWidget	*moveListWidget;
    QSplitter	*horizontalSplitter;
    void getMoveList(QString inputFile, int type);
	bool eventFilter(QObject * obj, QEvent * event);

private:
	void populateMoveList(QString move, QString difficulty);
    QJsonArray json_arr;
    bool splitterOpen;
    QList<bjjMove> bjjMoveList;
    void playSound(QString sound);
    QProcess    *soundProcess;

public slots:
	void backButton_Released();	
	void bjjButton_Released();
	void moveListItemClicked(QListWidgetItem* listWidgetItem);

signals:
    void sendStatusBar(QString message, int time);
	void returnPage(QString page);

};
