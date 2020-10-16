#pragma once
#include <QWidget>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

#include "GUI_Stylesheet.h"

/* Class: mainScreen

    QWidget widget to hold all objects needed for mainScreen implementation
*/
class mainScreen : public QWidget
{
    Q_OBJECT

public:
    mainScreen(QWidget *parent);
    ~mainScreen() {};
    GUI_Style    GUI_Style;
    QVBoxLayout *mainLayout;
    QPushButton *showIntervalTimer;
    QPushButton *situationalBtn;


};
