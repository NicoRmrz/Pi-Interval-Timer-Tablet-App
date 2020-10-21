#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QList>
#include <QFile>
#include <QMap>
#include <QSplitter>
#include <QListWidget>

#include "GUI_Stylesheet.h"

/* Class: IntervalTimer

    QWidget widget to hold all objects needed for IntervalTimer implementation
*/
class situationalGame : public QWidget
{
    Q_OBJECT

public:
    situationalGame(QWidget *parent);
    ~situationalGame() {};
    GUI_Style	GUI_Style;
	QPushButton	*backBtn;
    QHBoxLayout	*mainHLayout;
    QHBoxLayout	*mainLayout;
    QWidget		*leftContainer;
	QPushButton		*bjjBtn;
	QListWidget	*moveList;
	QSplitter	*horizontalSplitter;
    void getMoveList();
	//QList moveList;


private:
	void populateMoveList(QString move, QString difficulty);

public slots:
	void backButton_Pressed();
	void backButton_Released();	
	void bjjButton_Pressed();
	void bjjButton_Released();

signals:
    void sendStatusBar(QString message, int time);
	void returnPage(QString page);

};
