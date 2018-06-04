/********************************************************************************
** Form generated from reading UI file 'viewallwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWALLWIDGET_H
#define UI_VIEWALLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QCheckBox *checkBox1;
    QSlider *horizontalSlider1;
    QSlider *horizontalSlider2;
    QCheckBox *checkBox2;
    QSlider *horizontalSlider3;
    QCheckBox *checkBox3;
    QCheckBox *checkBox4;
    QSlider *horizontalSlider4;
    QCheckBox *checkBox5;
    QSlider *horizontalSlider5;
    QCheckBox *checkBox6;
    QVTKWidget *qvtkWidget;
    QSlider *horizontalSlider6;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(1290, 753);
        checkBox1 = new QCheckBox(Form);
        checkBox1->setObjectName(QStringLiteral("checkBox1"));
        checkBox1->setEnabled(true);
        checkBox1->setGeometry(QRect(25, 30, 101, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        checkBox1->setFont(font);
        horizontalSlider1 = new QSlider(Form);
        horizontalSlider1->setObjectName(QStringLiteral("horizontalSlider1"));
        horizontalSlider1->setEnabled(true);
        horizontalSlider1->setGeometry(QRect(26, 52, 150, 19));
        horizontalSlider1->setMaximum(100);
        horizontalSlider1->setSingleStep(1);
        horizontalSlider1->setOrientation(Qt::Horizontal);
        horizontalSlider2 = new QSlider(Form);
        horizontalSlider2->setObjectName(QStringLiteral("horizontalSlider2"));
        horizontalSlider2->setEnabled(false);
        horizontalSlider2->setGeometry(QRect(25, 123, 150, 19));
        horizontalSlider2->setMaximum(100);
        horizontalSlider2->setOrientation(Qt::Horizontal);
        checkBox2 = new QCheckBox(Form);
        checkBox2->setObjectName(QStringLiteral("checkBox2"));
        checkBox2->setEnabled(true);
        checkBox2->setGeometry(QRect(25, 93, 101, 21));
        checkBox2->setFont(font);
        checkBox2->setAcceptDrops(false);
        checkBox2->setCheckable(true);
        checkBox2->setChecked(false);
        checkBox2->setTristate(false);
        horizontalSlider3 = new QSlider(Form);
        horizontalSlider3->setObjectName(QStringLiteral("horizontalSlider3"));
        horizontalSlider3->setEnabled(false);
        horizontalSlider3->setGeometry(QRect(25, 198, 150, 19));
        horizontalSlider3->setMaximum(100);
        horizontalSlider3->setOrientation(Qt::Horizontal);
        checkBox3 = new QCheckBox(Form);
        checkBox3->setObjectName(QStringLiteral("checkBox3"));
        checkBox3->setEnabled(false);
        checkBox3->setGeometry(QRect(25, 168, 101, 21));
        checkBox3->setFont(font);
        checkBox4 = new QCheckBox(Form);
        checkBox4->setObjectName(QStringLiteral("checkBox4"));
        checkBox4->setEnabled(false);
        checkBox4->setGeometry(QRect(25, 239, 101, 21));
        checkBox4->setFont(font);
        horizontalSlider4 = new QSlider(Form);
        horizontalSlider4->setObjectName(QStringLiteral("horizontalSlider4"));
        horizontalSlider4->setEnabled(false);
        horizontalSlider4->setGeometry(QRect(25, 269, 150, 19));
        horizontalSlider4->setMaximum(100);
        horizontalSlider4->setOrientation(Qt::Horizontal);
        checkBox5 = new QCheckBox(Form);
        checkBox5->setObjectName(QStringLiteral("checkBox5"));
        checkBox5->setEnabled(false);
        checkBox5->setGeometry(QRect(25, 315, 101, 21));
        checkBox5->setFont(font);
        horizontalSlider5 = new QSlider(Form);
        horizontalSlider5->setObjectName(QStringLiteral("horizontalSlider5"));
        horizontalSlider5->setEnabled(false);
        horizontalSlider5->setGeometry(QRect(25, 345, 150, 19));
        horizontalSlider5->setMaximum(100);
        horizontalSlider5->setOrientation(Qt::Horizontal);
        checkBox6 = new QCheckBox(Form);
        checkBox6->setObjectName(QStringLiteral("checkBox6"));
        checkBox6->setEnabled(false);
        checkBox6->setGeometry(QRect(25, 396, 101, 21));
        checkBox6->setFont(font);
        qvtkWidget = new QVTKWidget(Form);
        qvtkWidget->setObjectName(QStringLiteral("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(210, 0, 1081, 751));
        horizontalSlider6 = new QSlider(Form);
        horizontalSlider6->setObjectName(QStringLiteral("horizontalSlider6"));
        horizontalSlider6->setEnabled(false);
        horizontalSlider6->setGeometry(QRect(25, 424, 150, 19));
        horizontalSlider6->setMaximum(100);
        horizontalSlider6->setOrientation(Qt::Horizontal);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        checkBox1->setText(QApplication::translate("Form", "label1", 0));
        checkBox2->setText(QApplication::translate("Form", "label2", 0));
        checkBox3->setText(QApplication::translate("Form", "label3", 0));
        checkBox4->setText(QApplication::translate("Form", "label4", 0));
        checkBox5->setText(QApplication::translate("Form", "label5", 0));
        checkBox6->setText(QApplication::translate("Form", "label6", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWALLWIDGET_H
