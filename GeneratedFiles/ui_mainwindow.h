/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_PLY;
    QAction *action;
    QWidget *centralWidget;
    QLabel *view;
    QLabel *label;
    QGroupBox *groupBox_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QGroupBox *groupBox;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *le_tranformX;
    QLabel *label_9;
    QLineEdit *le_tranformY;
    QLabel *label_10;
    QLineEdit *le_tranformZ;
    QLineEdit *le_scaleY_2;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *le_scaleZ_2;
    QLineEdit *le_scaleX_2;
    QLabel *label_13;
    QLabel *label_14;
    QLineEdit *le_rotateX;
    QLineEdit *le_rotateZ;
    QLineEdit *le_rotateY;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_2;
    QComboBox *cb_modelName;
    QLabel *label_17;
    QLineEdit *le_localX;
    QLabel *label_19;
    QLineEdit *le_localY;
    QLabel *label_18;
    QLineEdit *le_localZ;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(849, 638);
        action_PLY = new QAction(MainWindow);
        action_PLY->setObjectName(QStringLiteral("action_PLY"));
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        view = new QLabel(centralWidget);
        view->setObjectName(QStringLiteral("view"));
        view->setGeometry(QRect(20, 50, 450, 450));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(530, 140, 41, 16));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(530, 230, 261, 88));
        radioButton = new QRadioButton(groupBox_2);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(30, 60, 89, 16));
        radioButton_2 = new QRadioButton(groupBox_2);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(90, 60, 61, 16));
        radioButton_3 = new QRadioButton(groupBox_2);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(140, 30, 71, 16));
        radioButton_4 = new QRadioButton(groupBox_2);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(50, 30, 71, 16));
        radioButton_5 = new QRadioButton(groupBox_2);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        radioButton_5->setGeometry(QRect(150, 60, 91, 16));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(530, 350, 261, 191));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 30, 54, 12));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 130, 54, 12));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 70, 54, 21));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 50, 16, 16));
        le_tranformX = new QLineEdit(groupBox);
        le_tranformX->setObjectName(QStringLiteral("le_tranformX"));
        le_tranformX->setGeometry(QRect(40, 50, 41, 16));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(100, 50, 16, 16));
        le_tranformY = new QLineEdit(groupBox);
        le_tranformY->setObjectName(QStringLiteral("le_tranformY"));
        le_tranformY->setGeometry(QRect(120, 50, 41, 16));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(180, 50, 16, 16));
        le_tranformZ = new QLineEdit(groupBox);
        le_tranformZ->setObjectName(QStringLiteral("le_tranformZ"));
        le_tranformZ->setGeometry(QRect(200, 50, 41, 16));
        le_scaleY_2 = new QLineEdit(groupBox);
        le_scaleY_2->setObjectName(QStringLiteral("le_scaleY_2"));
        le_scaleY_2->setGeometry(QRect(120, 100, 41, 16));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, 100, 16, 16));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(180, 100, 16, 16));
        le_scaleZ_2 = new QLineEdit(groupBox);
        le_scaleZ_2->setObjectName(QStringLiteral("le_scaleZ_2"));
        le_scaleZ_2->setGeometry(QRect(200, 100, 41, 16));
        le_scaleX_2 = new QLineEdit(groupBox);
        le_scaleX_2->setObjectName(QStringLiteral("le_scaleX_2"));
        le_scaleX_2->setGeometry(QRect(40, 100, 41, 16));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(100, 100, 16, 16));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(20, 150, 16, 16));
        le_rotateX = new QLineEdit(groupBox);
        le_rotateX->setObjectName(QStringLiteral("le_rotateX"));
        le_rotateX->setGeometry(QRect(40, 150, 41, 16));
        le_rotateZ = new QLineEdit(groupBox);
        le_rotateZ->setObjectName(QStringLiteral("le_rotateZ"));
        le_rotateZ->setGeometry(QRect(200, 150, 41, 16));
        le_rotateY = new QLineEdit(groupBox);
        le_rotateY->setObjectName(QStringLiteral("le_rotateY"));
        le_rotateY->setGeometry(QRect(120, 150, 41, 16));
        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(180, 150, 16, 16));
        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(100, 150, 16, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(530, 100, 36, 16));
        cb_modelName = new QComboBox(centralWidget);
        cb_modelName->setObjectName(QStringLiteral("cb_modelName"));
        cb_modelName->setGeometry(QRect(580, 100, 201, 20));
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(537, 165, 16, 16));
        le_localX = new QLineEdit(centralWidget);
        le_localX->setObjectName(QStringLiteral("le_localX"));
        le_localX->setGeometry(QRect(555, 160, 64, 20));
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(625, 165, 16, 16));
        le_localY = new QLineEdit(centralWidget);
        le_localY->setObjectName(QStringLiteral("le_localY"));
        le_localY->setGeometry(QRect(643, 160, 63, 20));
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(712, 165, 16, 16));
        le_localZ = new QLineEdit(centralWidget);
        le_localZ->setObjectName(QStringLiteral("le_localZ"));
        le_localZ->setGeometry(QRect(730, 160, 64, 20));
        MainWindow->setCentralWidget(centralWidget);
        groupBox_2->raise();
        groupBox->raise();
        label_2->raise();
        cb_modelName->raise();
        label_17->raise();
        le_localX->raise();
        label_19->raise();
        le_localY->raise();
        label_18->raise();
        le_localZ->raise();
        view->raise();
        label->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 849, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(action_PLY);
        menu->addAction(action);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        action_PLY->setText(QApplication::translate("MainWindow", "\350\257\273\345\217\226PLY\346\226\207\344\273\266", 0));
        action->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\233\276\347\211\207", 0));
        view->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label->setText(QApplication::translate("MainWindow", "\345\235\220\346\240\207\357\274\232", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\346\235\220\350\264\250", 0));
        radioButton->setText(QApplication::translate("MainWindow", "Matte", 0));
        radioButton_2->setText(QApplication::translate("MainWindow", "Phong", 0));
        radioButton_3->setText(QApplication::translate("MainWindow", "\345\217\215\345\260\204\346\235\220\350\264\250", 0));
        radioButton_4->setText(QApplication::translate("MainWindow", "\351\200\217\346\230\216\346\235\220\350\264\250", 0));
        radioButton_5->setText(QApplication::translate("MainWindow", "Dielectric", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "\345\256\236\344\276\213\345\257\271\350\261\241", 0));
        label_5->setText(QApplication::translate("MainWindow", "\345\271\263\347\247\273\347\237\251\351\230\265\357\274\232", 0));
        label_6->setText(QApplication::translate("MainWindow", "\346\227\213\350\275\254\347\237\251\351\230\265\357\274\232", 0));
        label_7->setText(QApplication::translate("MainWindow", "\347\274\251\346\224\276\347\237\251\351\230\265\357\274\232", 0));
        label_8->setText(QApplication::translate("MainWindow", "X:", 0));
        label_9->setText(QApplication::translate("MainWindow", "Y:", 0));
        label_10->setText(QApplication::translate("MainWindow", "Z:", 0));
        label_11->setText(QApplication::translate("MainWindow", "X:", 0));
        label_12->setText(QApplication::translate("MainWindow", "Z:", 0));
        label_13->setText(QApplication::translate("MainWindow", "Y:", 0));
        label_14->setText(QApplication::translate("MainWindow", "X:", 0));
        label_15->setText(QApplication::translate("MainWindow", "Z:", 0));
        label_16->setText(QApplication::translate("MainWindow", "Y:", 0));
        label_2->setText(QApplication::translate("MainWindow", "\346\250\241\345\236\213\357\274\232", 0));
        label_17->setText(QApplication::translate("MainWindow", "X:", 0));
        label_19->setText(QApplication::translate("MainWindow", "Y:", 0));
        label_18->setText(QApplication::translate("MainWindow", "Z:", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
