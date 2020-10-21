#pragma once
#include <QWidget>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QFile>
#include <QMap>

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
    QVBoxLayout *mainVLayout;
    void getMoveList();


public slots:
	void backButton_Pressed();
	void backButton_Released();

signals:
    void sendStatusBar(QString message, int time);
	void returnPage(QString page);

};
