/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *calcPushButton;
    QTableWidget *tableWidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *hLineEdit;
    QLabel *label_7;
    QLabel *label;
    QLineEdit *fovLineEdit;
    QComboBox *fovComboBox;
    QLabel *label_3;
    QLineEdit *angLineEdit;
    QComboBox *angComboBox;
    QLabel *label_4;
    QLineEdit *rLineEdit;
    QLabel *label_11;
    QLabel *label_5;
    QLineEdit *pxLineEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(691, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        calcPushButton = new QPushButton(centralWidget);
        calcPushButton->setObjectName(QStringLiteral("calcPushButton"));
        calcPushButton->setGeometry(QRect(140, 200, 75, 23));
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(230, 11, 441, 211));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(22, 12, 191, 181));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        hLineEdit = new QLineEdit(layoutWidget);
        hLineEdit->setObjectName(QStringLiteral("hLineEdit"));
        hLineEdit->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(hLineEdit, 0, 1, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 0, 2, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        fovLineEdit = new QLineEdit(layoutWidget);
        fovLineEdit->setObjectName(QStringLiteral("fovLineEdit"));
        fovLineEdit->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(fovLineEdit, 1, 1, 1, 1);

        fovComboBox = new QComboBox(layoutWidget);
        fovComboBox->setObjectName(QStringLiteral("fovComboBox"));
        fovComboBox->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(fovComboBox, 1, 2, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        angLineEdit = new QLineEdit(layoutWidget);
        angLineEdit->setObjectName(QStringLiteral("angLineEdit"));
        angLineEdit->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(angLineEdit, 2, 1, 1, 1);

        angComboBox = new QComboBox(layoutWidget);
        angComboBox->setObjectName(QStringLiteral("angComboBox"));
        angComboBox->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(angComboBox, 2, 2, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        rLineEdit = new QLineEdit(layoutWidget);
        rLineEdit->setObjectName(QStringLiteral("rLineEdit"));
        rLineEdit->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(rLineEdit, 3, 1, 1, 1);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 3, 2, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        pxLineEdit = new QLineEdit(layoutWidget);
        pxLineEdit->setObjectName(QStringLiteral("pxLineEdit"));
        pxLineEdit->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(pxLineEdit, 4, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 691, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        calcPushButton->setText(QApplication::translate("MainWindow", "Calculate", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Height:", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "km", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Field of view:", Q_NULLPTR));
        fovComboBox->clear();
        fovComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "rad", Q_NULLPTR)
         << QApplication::translate("MainWindow", "deg", Q_NULLPTR)
         << QApplication::translate("MainWindow", "grad", Q_NULLPTR)
        );
        label_3->setText(QApplication::translate("MainWindow", "Angle:", Q_NULLPTR));
        angComboBox->clear();
        angComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "rad", Q_NULLPTR)
         << QApplication::translate("MainWindow", "deg", Q_NULLPTR)
         << QApplication::translate("MainWindow", "grad", Q_NULLPTR)
        );
        label_4->setText(QApplication::translate("MainWindow", "Planet radius:", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "km", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Pixels:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
