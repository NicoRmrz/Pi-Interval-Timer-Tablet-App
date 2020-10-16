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
    GUI_Style    GUI_Style;
    QMap<QString, QString> map;

    QVBoxLayout *mainVLayout;
    void getMoveList();

signals:
    void sendStatusBar(QString message, int time);

};
