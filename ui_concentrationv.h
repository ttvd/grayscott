/********************************************************************************
** Form generated from reading UI file 'concentrationv.ui'
**
** Created: Fri Apr 29 00:33:21 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONCENTRATIONV_H
#define UI_CONCENTRATIONV_H

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_concentrationv
{
public:
    QSlider *slider_size;
    QLabel *label_size;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_concentration;
    QSlider *slider_concentration;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *button_clear;
    QPushButton *button_load;
    QPushButton *button_save;
    QPushButton *button_defaults;
    QPushButton *button_invert;
    QLabel *label_7;
    QLabel *label_backgroundconcentration;
    QSlider *slider_backgroundconcentration;
    QLabel *label_8;
    QPushButton *button_random;

    void setupUi(QWidget *concentrationv)
    {
        if (concentrationv->objectName().isEmpty())
            concentrationv->setObjectName(QString::fromUtf8("concentrationv"));
        concentrationv->resize(250, 590);
        slider_size = new QSlider(concentrationv);
        slider_size->setObjectName(QString::fromUtf8("slider_size"));
        slider_size->setGeometry(QRect(40, 30, 145, 20));
        slider_size->setOrientation(Qt::Horizontal);
        slider_size->setTickPosition(QSlider::TicksBelow);
        label_size = new QLabel(concentrationv);
        label_size->setObjectName(QString::fromUtf8("label_size"));
        label_size->setGeometry(QRect(40, 10, 150, 16));
        label_2 = new QLabel(concentrationv);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 30, 10, 20));
        label_3 = new QLabel(concentrationv);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(190, 30, 20, 20));
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_concentration = new QLabel(concentrationv);
        label_concentration->setObjectName(QString::fromUtf8("label_concentration"));
        label_concentration->setGeometry(QRect(40, 60, 150, 16));
        slider_concentration = new QSlider(concentrationv);
        slider_concentration->setObjectName(QString::fromUtf8("slider_concentration"));
        slider_concentration->setGeometry(QRect(40, 80, 145, 20));
        slider_concentration->setPageStep(10);
        slider_concentration->setOrientation(Qt::Horizontal);
        slider_concentration->setTickPosition(QSlider::TicksBelow);
        label_5 = new QLabel(concentrationv);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 80, 10, 20));
        label_6 = new QLabel(concentrationv);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(190, 80, 20, 20));
        label_6->setLayoutDirection(Qt::LeftToRight);
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        button_clear = new QPushButton(concentrationv);
        button_clear->setObjectName(QString::fromUtf8("button_clear"));
        button_clear->setGeometry(QRect(14, 520, 111, 23));
        button_load = new QPushButton(concentrationv);
        button_load->setObjectName(QString::fromUtf8("button_load"));
        button_load->setGeometry(QRect(14, 550, 111, 23));
        button_save = new QPushButton(concentrationv);
        button_save->setObjectName(QString::fromUtf8("button_save"));
        button_save->setGeometry(QRect(130, 550, 111, 23));
        button_defaults = new QPushButton(concentrationv);
        button_defaults->setObjectName(QString::fromUtf8("button_defaults"));
        button_defaults->setGeometry(QRect(14, 490, 111, 23));
        button_invert = new QPushButton(concentrationv);
        button_invert->setObjectName(QString::fromUtf8("button_invert"));
        button_invert->setGeometry(QRect(130, 520, 111, 23));
        label_7 = new QLabel(concentrationv);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(190, 130, 20, 20));
        label_7->setLayoutDirection(Qt::LeftToRight);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_backgroundconcentration = new QLabel(concentrationv);
        label_backgroundconcentration->setObjectName(QString::fromUtf8("label_backgroundconcentration"));
        label_backgroundconcentration->setGeometry(QRect(40, 110, 171, 16));
        slider_backgroundconcentration = new QSlider(concentrationv);
        slider_backgroundconcentration->setObjectName(QString::fromUtf8("slider_backgroundconcentration"));
        slider_backgroundconcentration->setGeometry(QRect(40, 130, 145, 20));
        slider_backgroundconcentration->setPageStep(10);
        slider_backgroundconcentration->setOrientation(Qt::Horizontal);
        slider_backgroundconcentration->setTickPosition(QSlider::TicksBelow);
        label_8 = new QLabel(concentrationv);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(30, 130, 10, 20));
        button_random = new QPushButton(concentrationv);
        button_random->setObjectName(QString::fromUtf8("button_random"));
        button_random->setGeometry(QRect(130, 490, 111, 23));

        retranslateUi(concentrationv);

        QMetaObject::connectSlotsByName(concentrationv);
    } // setupUi

    void retranslateUi(QWidget *concentrationv)
    {
        concentrationv->setWindowTitle(QApplication::translate("concentrationv", "ConcentrationV", 0));
        label_size->setText(QApplication::translate("concentrationv", "Brush size: 10", 0));
        label_2->setText(QApplication::translate("concentrationv", "0", 0));
        label_3->setText(QApplication::translate("concentrationv", "255", 0));
        label_concentration->setText(QApplication::translate("concentrationv", "Brush concentration: 255", 0));
        label_5->setText(QApplication::translate("concentrationv", "0", 0));
        label_6->setText(QApplication::translate("concentrationv", "255", 0));
        button_clear->setText(QApplication::translate("concentrationv", "Clear", 0));
        button_load->setText(QApplication::translate("concentrationv", "Load", 0));
        button_save->setText(QApplication::translate("concentrationv", "Save", 0));
        button_defaults->setText(QApplication::translate("concentrationv", "Defaults", 0));
        button_invert->setText(QApplication::translate("concentrationv", "Invert", 0));
        label_7->setText(QApplication::translate("concentrationv", "255", 0));
        label_backgroundconcentration->setText(QApplication::translate("concentrationv", "Background concentration: 255", 0));
        label_8->setText(QApplication::translate("concentrationv", "0", 0));
        button_random->setText(QApplication::translate("concentrationv", "Random", 0));
    } // retranslateUi

};

namespace Ui {
    class concentrationv: public Ui_concentrationv {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONCENTRATIONV_H
