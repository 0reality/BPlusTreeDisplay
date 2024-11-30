/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QWidget *displayWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *displayBox;
    QLabel *messegeLabel;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *inKeyLabel;
    QSpinBox *inKeySpinBox;
    QLabel *inValueLabel;
    QSpinBox *inValueSpinBox;
    QPushButton *inButton;
    QSpacerItem *verticalSpacer_3;
    QLabel *delKeyLabel;
    QSpinBox *delKeySpinButton;
    QPushButton *delButton;
    QSpacerItem *verticalSpacer_2;
    QLabel *findKeyLabel;
    QSpinBox *findKeySpinBox;
    QPushButton *findButton;
    QSpacerItem *verticalSpacer_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1270, 720);
        MainWindow->setMinimumSize(QSize(1270, 720));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        displayWidget = new QWidget(centralwidget);
        displayWidget->setObjectName("displayWidget");
        displayWidget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(displayWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        displayBox = new QVBoxLayout();
        displayBox->setObjectName("displayBox");

        horizontalLayout_2->addLayout(displayBox);


        verticalLayout_2->addWidget(displayWidget);

        messegeLabel = new QLabel(centralwidget);
        messegeLabel->setObjectName("messegeLabel");
        messegeLabel->setEnabled(true);
        messegeLabel->setMinimumSize(QSize(0, 100));
        messegeLabel->setMaximumSize(QSize(16777215, 100));

        verticalLayout_2->addWidget(messegeLabel);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        inKeyLabel = new QLabel(centralwidget);
        inKeyLabel->setObjectName("inKeyLabel");

        verticalLayout->addWidget(inKeyLabel);

        inKeySpinBox = new QSpinBox(centralwidget);
        inKeySpinBox->setObjectName("inKeySpinBox");

        verticalLayout->addWidget(inKeySpinBox);

        inValueLabel = new QLabel(centralwidget);
        inValueLabel->setObjectName("inValueLabel");

        verticalLayout->addWidget(inValueLabel);

        inValueSpinBox = new QSpinBox(centralwidget);
        inValueSpinBox->setObjectName("inValueSpinBox");

        verticalLayout->addWidget(inValueSpinBox);

        inButton = new QPushButton(centralwidget);
        inButton->setObjectName("inButton");

        verticalLayout->addWidget(inButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        delKeyLabel = new QLabel(centralwidget);
        delKeyLabel->setObjectName("delKeyLabel");

        verticalLayout->addWidget(delKeyLabel);

        delKeySpinButton = new QSpinBox(centralwidget);
        delKeySpinButton->setObjectName("delKeySpinButton");

        verticalLayout->addWidget(delKeySpinButton);

        delButton = new QPushButton(centralwidget);
        delButton->setObjectName("delButton");
        delButton->setEnabled(true);
        delButton->setMinimumSize(QSize(200, 0));

        verticalLayout->addWidget(delButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        findKeyLabel = new QLabel(centralwidget);
        findKeyLabel->setObjectName("findKeyLabel");

        verticalLayout->addWidget(findKeyLabel);

        findKeySpinBox = new QSpinBox(centralwidget);
        findKeySpinBox->setObjectName("findKeySpinBox");

        verticalLayout->addWidget(findKeySpinBox);

        findButton = new QPushButton(centralwidget);
        findButton->setObjectName("findButton");

        verticalLayout->addWidget(findButton);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 6);
        horizontalLayout->setStretch(1, 1);

        horizontalLayout_3->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1270, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        messegeLabel->setText(QCoreApplication::translate("MainWindow", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", nullptr));
        inKeyLabel->setText(QCoreApplication::translate("MainWindow", "Key:", nullptr));
        inValueLabel->setText(QCoreApplication::translate("MainWindow", "Value:", nullptr));
        inButton->setText(QCoreApplication::translate("MainWindow", "\346\217\222\345\205\245", nullptr));
        delKeyLabel->setText(QCoreApplication::translate("MainWindow", "Key:", nullptr));
        delButton->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        findKeyLabel->setText(QCoreApplication::translate("MainWindow", "Key:", nullptr));
        findButton->setText(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
