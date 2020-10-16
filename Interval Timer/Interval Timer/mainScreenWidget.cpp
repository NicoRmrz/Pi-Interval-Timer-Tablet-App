
/* File: mainScreenWidget.cpp

    Contains functions for mainScreenWidget

    Author: Nico Ramirez
*/
#include "mainScreenWidget.h"

#include <QDebug>

using namespace std;

/* Constructor: mainScreen

        Lays out all objects for the mainScreen page

    Parameters:

        parent - Inherits QWidget attributes
*/
mainScreen::mainScreen(QWidget *parent) :
    GUI_Style(parent)

{
    // Create timer interval button
    showIntervalTimer = new QPushButton(parent);
    showIntervalTimer->setObjectName(QString::fromUtf8("showIntervalTimer"));
    showIntervalTimer->setMinimumSize(200, 90);
    showIntervalTimer->setMaximumSize(200, 90);
    showIntervalTimer->setText("INTERVAL TIMER");

    // Create timer interval button
    situationalBtn = new QPushButton(parent);
    situationalBtn->setObjectName(QString::fromUtf8("showSituationalPage"));
    situationalBtn->setMinimumSize(200, 90);
    situationalBtn->setMaximumSize(200, 90);
    situationalBtn->setText("SITUATIONAL");

    mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(50);
    mainLayout->addWidget(showIntervalTimer, 0, Qt::AlignCenter);
    mainLayout->addWidget(situationalBtn, 0, Qt::AlignCenter);

    setLayout(mainLayout);

    setStyleSheet(GUI_Style.mainWindowGrey);
    showIntervalTimer->setStyleSheet(GUI_Style.intervalTimerBtn);
    situationalBtn->setStyleSheet(GUI_Style.intervalTimerBtn);
}

