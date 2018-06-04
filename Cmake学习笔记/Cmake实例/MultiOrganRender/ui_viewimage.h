/********************************************************************************
** Form generated from reading UI file 'viewimage.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWIMAGE_H
#define UI_VIEWIMAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_viewImageClass
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit_path;
    QPushButton *pushButton_path;
    QPushButton *pushButton_load;
    QPushButton *pushButton_each;
    QPushButton *pushButton_all;
    QLineEdit *lineEdit_label1;
    QLineEdit *lineEdit_label2;
    QLineEdit *lineEdit_label3;
    QLineEdit *lineEdit_label4;
    QLineEdit *lineEdit_label5;
    QLineEdit *lineEdit_other;
    QLineEdit *lineEdit_label6;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *viewImageClass)
    {
        if (viewImageClass->objectName().isEmpty())
            viewImageClass->setObjectName(QStringLiteral("viewImageClass"));
        viewImageClass->resize(700, 400);
        centralWidget = new QWidget(viewImageClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lineEdit_path = new QLineEdit(centralWidget);
        lineEdit_path->setObjectName(QStringLiteral("lineEdit_path"));
        lineEdit_path->setGeometry(QRect(77, 70, 400, 45));
        pushButton_path = new QPushButton(centralWidget);
        pushButton_path->setObjectName(QStringLiteral("pushButton_path"));
        pushButton_path->setGeometry(QRect(487, 70, 50, 45));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(14);
        pushButton_path->setFont(font);
        pushButton_path->setIconSize(QSize(26, 26));
        pushButton_load = new QPushButton(centralWidget);
        pushButton_load->setObjectName(QStringLiteral("pushButton_load"));
        pushButton_load->setGeometry(QRect(549, 69, 81, 45));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        pushButton_load->setFont(font1);
        pushButton_load->setIconSize(QSize(26, 26));
        pushButton_each = new QPushButton(centralWidget);
        pushButton_each->setObjectName(QStringLiteral("pushButton_each"));
        pushButton_each->setGeometry(QRect(188, 260, 101, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(14);
        pushButton_each->setFont(font2);
        pushButton_all = new QPushButton(centralWidget);
        pushButton_all->setObjectName(QStringLiteral("pushButton_all"));
        pushButton_all->setGeometry(QRect(366, 260, 101, 41));
        pushButton_all->setFont(font2);
        lineEdit_label1 = new QLineEdit(centralWidget);
        lineEdit_label1->setObjectName(QStringLiteral("lineEdit_label1"));
        lineEdit_label1->setGeometry(QRect(71, 200, 76, 31));
        lineEdit_label1->setFont(font1);
        lineEdit_label1->setFrame(false);
        lineEdit_label1->setAlignment(Qt::AlignCenter);
        lineEdit_label2 = new QLineEdit(centralWidget);
        lineEdit_label2->setObjectName(QStringLiteral("lineEdit_label2"));
        lineEdit_label2->setGeometry(QRect(153, 200, 76, 31));
        lineEdit_label2->setFont(font1);
        lineEdit_label2->setFrame(false);
        lineEdit_label2->setAlignment(Qt::AlignCenter);
        lineEdit_label3 = new QLineEdit(centralWidget);
        lineEdit_label3->setObjectName(QStringLiteral("lineEdit_label3"));
        lineEdit_label3->setGeometry(QRect(237, 200, 76, 31));
        lineEdit_label3->setFont(font1);
        lineEdit_label3->setFrame(false);
        lineEdit_label3->setAlignment(Qt::AlignCenter);
        lineEdit_label4 = new QLineEdit(centralWidget);
        lineEdit_label4->setObjectName(QStringLiteral("lineEdit_label4"));
        lineEdit_label4->setGeometry(QRect(325, 200, 76, 31));
        lineEdit_label4->setFont(font1);
        lineEdit_label4->setFrame(false);
        lineEdit_label4->setAlignment(Qt::AlignCenter);
        lineEdit_label5 = new QLineEdit(centralWidget);
        lineEdit_label5->setObjectName(QStringLiteral("lineEdit_label5"));
        lineEdit_label5->setGeometry(QRect(400, 200, 76, 31));
        lineEdit_label5->setFont(font1);
        lineEdit_label5->setFrame(false);
        lineEdit_label5->setEchoMode(QLineEdit::Normal);
        lineEdit_label5->setAlignment(Qt::AlignCenter);
        lineEdit_other = new QLineEdit(centralWidget);
        lineEdit_other->setObjectName(QStringLiteral("lineEdit_other"));
        lineEdit_other->setGeometry(QRect(569, 200, 61, 31));
        lineEdit_other->setFont(font1);
        lineEdit_other->setFrame(false);
        lineEdit_other->setAlignment(Qt::AlignCenter);
        lineEdit_label6 = new QLineEdit(centralWidget);
        lineEdit_label6->setObjectName(QStringLiteral("lineEdit_label6"));
        lineEdit_label6->setGeometry(QRect(476, 200, 76, 31));
        lineEdit_label6->setFont(font1);
        lineEdit_label6->setFrame(false);
        lineEdit_label6->setAlignment(Qt::AlignCenter);
        viewImageClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(viewImageClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 700, 23));
        viewImageClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(viewImageClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        viewImageClass->setStatusBar(statusBar);

        retranslateUi(viewImageClass);

        QMetaObject::connectSlotsByName(viewImageClass);
    } // setupUi

    void retranslateUi(QMainWindow *viewImageClass)
    {
        viewImageClass->setWindowTitle(QApplication::translate("viewImageClass", "viewImage", 0));
        pushButton_path->setText(QString());
        pushButton_load->setText(QApplication::translate("viewImageClass", "\345\212\240\350\275\275\346\225\260\346\215\256", 0));
        pushButton_each->setText(QApplication::translate("viewImageClass", "\345\210\206\345\274\200\346\230\276\347\244\272", 0));
        pushButton_all->setText(QApplication::translate("viewImageClass", "\344\270\200\350\265\267\346\230\276\347\244\272", 0));
        lineEdit_label1->setText(QApplication::translate("viewImageClass", "\344\270\273\345\212\250\350\204\211", 0));
        lineEdit_label2->setText(QApplication::translate("viewImageClass", "\350\202\235\350\204\217", 0));
        lineEdit_label3->setText(QApplication::translate("viewImageClass", "\345\220\216\350\205\224\351\235\231\350\204\211", 0));
        lineEdit_label4->setText(QApplication::translate("viewImageClass", "\350\204\276\350\204\217", 0));
        lineEdit_label5->setText(QApplication::translate("viewImageClass", "\350\203\260\350\205\272", 0));
        lineEdit_other->setText(QApplication::translate("viewImageClass", "\345\205\266\344\273\226", 0));
        lineEdit_label6->setText(QApplication::translate("viewImageClass", "\347\251\272\350\205\224\350\204\217\345\231\250", 0));
    } // retranslateUi

};

namespace Ui {
    class viewImageClass: public Ui_viewImageClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWIMAGE_H
