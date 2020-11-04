QT           += core gui widgets

HEADERS       = intervalTimerPage.h \
				editPopUp.h \
				GUI_Stylesheet.h \
				mainScreenWidget.h \
				MainWindow.h \
				situationalPage.h \
				timer.h \
				ui_MainWindow.h 

SOURCES       = intervalTimerPage.cpp \
                main.cpp \
				editPopUp.cpp \
				GUI_Stylesheet.cpp \
				mainScreenWidget.cpp \
				MainWindow.cpp \
				situationalPage.cpp \
				timer.cpp 
				
#OTHER_SOURCES += inputMoveList/bjjMoveList.json

RESOURCES = Resource.qrc
CONFIG      += debug
#DEFINES      += QT_NO_DEBUG_OUTPUT
DEFINES      += DEBUG
#RC_ICONS = /icons/icon.ico

#DESTDIR = /home/pi/Desktop
DESTDIR = ../../build/
OBJECTS_DIR = obj/
MOC_DIR = moc/

