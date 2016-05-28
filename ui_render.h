/********************************************************************************
** Form generated from reading UI file 'render.ui'
**
** Created: Fri Apr 29 00:33:21 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDER_H
#define UI_RENDER_H

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QSlider>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_render
{
public:
    QPushButton *button_save;
    QPushButton *button_restart;
    QPushButton *button_start;
    QGroupBox *groupBox;
    QLabel *label_size;
    QLineEdit *edit_du;
    QLineEdit *edit_dv;
    QLabel *label_size_2;
    QLabel *label_du_min;
    QLabel *label_du_max;
    QLabel *label_dv_max;
    QLabel *label_dv_min;
    QSlider *slider_du;
    QSlider *slider_dv;
    QGroupBox *groupBox_2;
    QLabel *label_size_3;
    QLineEdit *edit_f;
    QLineEdit *edit_k;
    QLabel *label_size_4;
    QLabel *label_f_max;
    QLabel *label_f_min;
    QLabel *label_k_min;
    QLabel *label_k_max;
    QSlider *slider_f;
    QSlider *slider_k;
    QGroupBox *groupBox_3;
    QLabel *label_size_5;
    QLineEdit *edit_distance;
    QLineEdit *edit_timestep;
    QLabel *label_size_6;
    QLabel *label_dist_max;
    QLabel *label_dist_min;
    QLabel *label_step_min;
    QLabel *label_step_max;
    QSlider *slider_dist;
    QSlider *slider_step;
    QGroupBox *groupBox_4;
    QLabel *label_frame;
    QLabel *label_time;
    QGroupBox *groupBox_5;
    QRadioButton *radio_periodic;
    QRadioButton *radio_zero;
    QPushButton *button_defaults;
    QGroupBox *groupBox_6;
    QRadioButton *radio_rendering_u;
    QRadioButton *radio_rendering_v;
    QRadioButton *radio_rendering_changeu;
    QComboBox *combo_render;
    QCheckBox *checkbox_discard;
    QCheckBox *checkbox_displace;
    QLabel *label_discard_max;
    QSlider *slider_discard;
    QLabel *label_discard_min;
    QLabel *label_displace_max;
    QSlider *slider_displace;
    QLabel *label_displace_min;
    QPushButton *button_loadconfig;
    QPushButton *button_saveconfig;

    void setupUi(QWidget *render)
    {
        if (render->objectName().isEmpty())
            render->setObjectName(QString::fromUtf8("render"));
        render->resize(250, 590);
        button_save = new QPushButton(render);
        button_save->setObjectName(QString::fromUtf8("button_save"));
        button_save->setGeometry(QRect(130, 550, 111, 23));
        button_restart = new QPushButton(render);
        button_restart->setObjectName(QString::fromUtf8("button_restart"));
        button_restart->setGeometry(QRect(14, 490, 101, 23));
        button_start = new QPushButton(render);
        button_start->setObjectName(QString::fromUtf8("button_start"));
        button_start->setGeometry(QRect(130, 490, 111, 23));
        groupBox = new QGroupBox(render);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 231, 81));
        groupBox->setStyleSheet(QString::fromUtf8(""));
        groupBox->setAlignment(Qt::AlignCenter);
        groupBox->setFlat(true);
        label_size = new QLabel(groupBox);
        label_size->setObjectName(QString::fromUtf8("label_size"));
        label_size->setGeometry(QRect(0, 20, 31, 21));
        edit_du = new QLineEdit(groupBox);
        edit_du->setObjectName(QString::fromUtf8("edit_du"));
        edit_du->setGeometry(QRect(30, 20, 41, 20));
        edit_dv = new QLineEdit(groupBox);
        edit_dv->setObjectName(QString::fromUtf8("edit_dv"));
        edit_dv->setGeometry(QRect(30, 50, 41, 20));
        label_size_2 = new QLabel(groupBox);
        label_size_2->setObjectName(QString::fromUtf8("label_size_2"));
        label_size_2->setGeometry(QRect(0, 50, 31, 21));
        label_du_min = new QLabel(groupBox);
        label_du_min->setObjectName(QString::fromUtf8("label_du_min"));
        label_du_min->setGeometry(QRect(80, 20, 21, 21));
        label_du_max = new QLabel(groupBox);
        label_du_max->setObjectName(QString::fromUtf8("label_du_max"));
        label_du_max->setGeometry(QRect(210, 20, 21, 21));
        label_dv_max = new QLabel(groupBox);
        label_dv_max->setObjectName(QString::fromUtf8("label_dv_max"));
        label_dv_max->setGeometry(QRect(210, 50, 21, 21));
        label_dv_min = new QLabel(groupBox);
        label_dv_min->setObjectName(QString::fromUtf8("label_dv_min"));
        label_dv_min->setGeometry(QRect(80, 50, 21, 21));
        slider_du = new QSlider(groupBox);
        slider_du->setObjectName(QString::fromUtf8("slider_du"));
        slider_du->setGeometry(QRect(100, 20, 101, 20));
        slider_du->setAutoFillBackground(false);
        slider_du->setMaximum(99);
        slider_du->setPageStep(1);
        slider_du->setOrientation(Qt::Horizontal);
        slider_du->setTickPosition(QSlider::TicksBelow);
        slider_dv = new QSlider(groupBox);
        slider_dv->setObjectName(QString::fromUtf8("slider_dv"));
        slider_dv->setGeometry(QRect(100, 50, 101, 20));
        slider_dv->setMaximum(99);
        slider_dv->setPageStep(1);
        slider_dv->setOrientation(Qt::Horizontal);
        slider_dv->setTickPosition(QSlider::TicksBelow);
        groupBox_2 = new QGroupBox(render);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 90, 231, 81));
        groupBox_2->setStyleSheet(QString::fromUtf8(""));
        groupBox_2->setAlignment(Qt::AlignCenter);
        groupBox_2->setFlat(true);
        label_size_3 = new QLabel(groupBox_2);
        label_size_3->setObjectName(QString::fromUtf8("label_size_3"));
        label_size_3->setGeometry(QRect(0, 20, 31, 21));
        edit_f = new QLineEdit(groupBox_2);
        edit_f->setObjectName(QString::fromUtf8("edit_f"));
        edit_f->setGeometry(QRect(30, 20, 41, 20));
        edit_k = new QLineEdit(groupBox_2);
        edit_k->setObjectName(QString::fromUtf8("edit_k"));
        edit_k->setGeometry(QRect(30, 50, 41, 20));
        label_size_4 = new QLabel(groupBox_2);
        label_size_4->setObjectName(QString::fromUtf8("label_size_4"));
        label_size_4->setGeometry(QRect(0, 50, 31, 21));
        label_f_max = new QLabel(groupBox_2);
        label_f_max->setObjectName(QString::fromUtf8("label_f_max"));
        label_f_max->setGeometry(QRect(210, 20, 21, 21));
        label_f_min = new QLabel(groupBox_2);
        label_f_min->setObjectName(QString::fromUtf8("label_f_min"));
        label_f_min->setGeometry(QRect(80, 20, 21, 21));
        label_k_min = new QLabel(groupBox_2);
        label_k_min->setObjectName(QString::fromUtf8("label_k_min"));
        label_k_min->setGeometry(QRect(80, 50, 21, 21));
        label_k_max = new QLabel(groupBox_2);
        label_k_max->setObjectName(QString::fromUtf8("label_k_max"));
        label_k_max->setGeometry(QRect(210, 50, 21, 21));
        slider_f = new QSlider(groupBox_2);
        slider_f->setObjectName(QString::fromUtf8("slider_f"));
        slider_f->setGeometry(QRect(100, 20, 101, 20));
        slider_f->setMaximum(99);
        slider_f->setPageStep(1);
        slider_f->setOrientation(Qt::Horizontal);
        slider_f->setTickPosition(QSlider::TicksBelow);
        slider_k = new QSlider(groupBox_2);
        slider_k->setObjectName(QString::fromUtf8("slider_k"));
        slider_k->setGeometry(QRect(100, 50, 101, 20));
        slider_k->setMaximum(99);
        slider_k->setPageStep(1);
        slider_k->setOrientation(Qt::Horizontal);
        slider_k->setTickPosition(QSlider::TicksBelow);
        groupBox_3 = new QGroupBox(render);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 170, 231, 101));
        groupBox_3->setStyleSheet(QString::fromUtf8(""));
        groupBox_3->setAlignment(Qt::AlignCenter);
        groupBox_3->setFlat(true);
        label_size_5 = new QLabel(groupBox_3);
        label_size_5->setObjectName(QString::fromUtf8("label_size_5"));
        label_size_5->setGeometry(QRect(0, 20, 31, 21));
        edit_distance = new QLineEdit(groupBox_3);
        edit_distance->setObjectName(QString::fromUtf8("edit_distance"));
        edit_distance->setGeometry(QRect(30, 20, 41, 20));
        edit_timestep = new QLineEdit(groupBox_3);
        edit_timestep->setObjectName(QString::fromUtf8("edit_timestep"));
        edit_timestep->setGeometry(QRect(30, 50, 41, 20));
        label_size_6 = new QLabel(groupBox_3);
        label_size_6->setObjectName(QString::fromUtf8("label_size_6"));
        label_size_6->setGeometry(QRect(0, 50, 31, 21));
        label_dist_max = new QLabel(groupBox_3);
        label_dist_max->setObjectName(QString::fromUtf8("label_dist_max"));
        label_dist_max->setGeometry(QRect(210, 20, 21, 21));
        label_dist_min = new QLabel(groupBox_3);
        label_dist_min->setObjectName(QString::fromUtf8("label_dist_min"));
        label_dist_min->setGeometry(QRect(80, 20, 21, 21));
        label_step_min = new QLabel(groupBox_3);
        label_step_min->setObjectName(QString::fromUtf8("label_step_min"));
        label_step_min->setGeometry(QRect(80, 50, 21, 21));
        label_step_max = new QLabel(groupBox_3);
        label_step_max->setObjectName(QString::fromUtf8("label_step_max"));
        label_step_max->setGeometry(QRect(210, 50, 21, 21));
        slider_dist = new QSlider(groupBox_3);
        slider_dist->setObjectName(QString::fromUtf8("slider_dist"));
        slider_dist->setGeometry(QRect(100, 20, 101, 20));
        slider_dist->setMaximum(99);
        slider_dist->setPageStep(1);
        slider_dist->setOrientation(Qt::Horizontal);
        slider_dist->setTickPosition(QSlider::TicksBelow);
        slider_step = new QSlider(groupBox_3);
        slider_step->setObjectName(QString::fromUtf8("slider_step"));
        slider_step->setGeometry(QRect(100, 50, 101, 20));
        slider_step->setMaximum(99);
        slider_step->setPageStep(1);
        slider_step->setOrientation(Qt::Horizontal);
        slider_step->setTickPosition(QSlider::TicksBelow);
        groupBox_4 = new QGroupBox(render);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 440, 231, 41));
        groupBox_4->setStyleSheet(QString::fromUtf8(""));
        groupBox_4->setAlignment(Qt::AlignCenter);
        groupBox_4->setFlat(true);
        label_frame = new QLabel(groupBox_4);
        label_frame->setObjectName(QString::fromUtf8("label_frame"));
        label_frame->setGeometry(QRect(30, 20, 111, 21));
        label_time = new QLabel(groupBox_4);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setGeometry(QRect(130, 20, 71, 21));
        groupBox_5 = new QGroupBox(render);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 250, 231, 51));
        groupBox_5->setStyleSheet(QString::fromUtf8(""));
        groupBox_5->setAlignment(Qt::AlignCenter);
        groupBox_5->setFlat(true);
        radio_periodic = new QRadioButton(groupBox_5);
        radio_periodic->setObjectName(QString::fromUtf8("radio_periodic"));
        radio_periodic->setGeometry(QRect(40, 20, 82, 17));
        radio_zero = new QRadioButton(groupBox_5);
        radio_zero->setObjectName(QString::fromUtf8("radio_zero"));
        radio_zero->setGeometry(QRect(130, 20, 61, 17));
        button_defaults = new QPushButton(render);
        button_defaults->setObjectName(QString::fromUtf8("button_defaults"));
        button_defaults->setGeometry(QRect(14, 550, 101, 23));
        groupBox_6 = new QGroupBox(render);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 300, 231, 141));
        groupBox_6->setStyleSheet(QString::fromUtf8(""));
        groupBox_6->setAlignment(Qt::AlignCenter);
        groupBox_6->setFlat(true);
        radio_rendering_u = new QRadioButton(groupBox_6);
        radio_rendering_u->setObjectName(QString::fromUtf8("radio_rendering_u"));
        radio_rendering_u->setGeometry(QRect(40, 20, 31, 17));
        radio_rendering_v = new QRadioButton(groupBox_6);
        radio_rendering_v->setObjectName(QString::fromUtf8("radio_rendering_v"));
        radio_rendering_v->setGeometry(QRect(80, 20, 41, 17));
        radio_rendering_changeu = new QRadioButton(groupBox_6);
        radio_rendering_changeu->setObjectName(QString::fromUtf8("radio_rendering_changeu"));
        radio_rendering_changeu->setGeometry(QRect(120, 20, 91, 17));
        combo_render = new QComboBox(groupBox_6);
        combo_render->setObjectName(QString::fromUtf8("combo_render"));
        combo_render->setGeometry(QRect(0, 50, 231, 22));
        checkbox_discard = new QCheckBox(groupBox_6);
        checkbox_discard->setObjectName(QString::fromUtf8("checkbox_discard"));
        checkbox_discard->setGeometry(QRect(0, 80, 151, 17));
        checkbox_displace = new QCheckBox(groupBox_6);
        checkbox_displace->setObjectName(QString::fromUtf8("checkbox_displace"));
        checkbox_displace->setGeometry(QRect(0, 110, 71, 17));
        label_discard_max = new QLabel(groupBox_6);
        label_discard_max->setObjectName(QString::fromUtf8("label_discard_max"));
        label_discard_max->setGeometry(QRect(210, 80, 21, 21));
        slider_discard = new QSlider(groupBox_6);
        slider_discard->setObjectName(QString::fromUtf8("slider_discard"));
        slider_discard->setGeometry(QRect(100, 80, 101, 20));
        slider_discard->setAutoFillBackground(false);
        slider_discard->setMaximum(99);
        slider_discard->setPageStep(1);
        slider_discard->setOrientation(Qt::Horizontal);
        slider_discard->setTickPosition(QSlider::TicksBelow);
        label_discard_min = new QLabel(groupBox_6);
        label_discard_min->setObjectName(QString::fromUtf8("label_discard_min"));
        label_discard_min->setGeometry(QRect(80, 80, 21, 21));
        label_displace_max = new QLabel(groupBox_6);
        label_displace_max->setObjectName(QString::fromUtf8("label_displace_max"));
        label_displace_max->setGeometry(QRect(210, 110, 21, 21));
        slider_displace = new QSlider(groupBox_6);
        slider_displace->setObjectName(QString::fromUtf8("slider_displace"));
        slider_displace->setGeometry(QRect(100, 110, 101, 20));
        slider_displace->setAutoFillBackground(false);
        slider_displace->setMaximum(99);
        slider_displace->setPageStep(1);
        slider_displace->setOrientation(Qt::Horizontal);
        slider_displace->setTickPosition(QSlider::TicksBelow);
        label_displace_min = new QLabel(groupBox_6);
        label_displace_min->setObjectName(QString::fromUtf8("label_displace_min"));
        label_displace_min->setGeometry(QRect(80, 110, 21, 21));
        radio_rendering_u->raise();
        radio_rendering_v->raise();
        radio_rendering_changeu->raise();
        combo_render->raise();
        checkbox_discard->raise();
        checkbox_displace->raise();
        label_discard_max->raise();
        slider_discard->raise();
        label_discard_min->raise();
        label_displace_max->raise();
        slider_displace->raise();
        label_displace_min->raise();
        button_loadconfig = new QPushButton(render);
        button_loadconfig->setObjectName(QString::fromUtf8("button_loadconfig"));
        button_loadconfig->setGeometry(QRect(14, 520, 101, 23));
        button_saveconfig = new QPushButton(render);
        button_saveconfig->setObjectName(QString::fromUtf8("button_saveconfig"));
        button_saveconfig->setGeometry(QRect(130, 520, 111, 23));

        retranslateUi(render);

        QMetaObject::connectSlotsByName(render);
    } // setupUi

    void retranslateUi(QWidget *render)
    {
        render->setWindowTitle(QApplication::translate("render", "Render2d", 0));
        button_save->setText(QApplication::translate("render", "Save Image", 0));
        button_restart->setText(QApplication::translate("render", "Restart", 0));
        button_start->setText(QApplication::translate("render", "Start", 0));
        groupBox->setTitle(QApplication::translate("render", "Diffusion Coefficients", 0));
        label_size->setText(QApplication::translate("render", "Du", 0));
        label_size_2->setText(QApplication::translate("render", "Dv", 0));
        label_du_min->setText(QApplication::translate("render", "0.0", 0));
        label_du_max->setText(QApplication::translate("render", "0.3", 0));
        label_dv_max->setText(QApplication::translate("render", "0.3", 0));
        label_dv_min->setText(QApplication::translate("render", "0.0", 0));
        groupBox_2->setTitle(QApplication::translate("render", "Reaction Constants", 0));
        label_size_3->setText(QApplication::translate("render", "F", 0));
        label_size_4->setText(QApplication::translate("render", "K", 0));
        label_f_max->setText(QApplication::translate("render", "0.3", 0));
        label_f_min->setText(QApplication::translate("render", "0.0", 0));
        label_k_min->setText(QApplication::translate("render", "0.0", 0));
        label_k_max->setText(QApplication::translate("render", "0.3", 0));
        groupBox_3->setTitle(QApplication::translate("render", "Simulation", 0));
        label_size_5->setText(QApplication::translate("render", "Dist", 0));
        label_size_6->setText(QApplication::translate("render", "Step", 0));
        label_dist_max->setText(QApplication::translate("render", "0.3", 0));
        label_dist_min->setText(QApplication::translate("render", "0.0", 0));
        label_step_min->setText(QApplication::translate("render", "0.0", 0));
        label_step_max->setText(QApplication::translate("render", "0.3", 0));
        groupBox_4->setTitle(QApplication::translate("render", "Statistics", 0));
        label_frame->setText(QApplication::translate("render", "Frame: 0", 0));
        label_time->setText(QApplication::translate("render", "Time: 0 s", 0));
        groupBox_5->setTitle(QApplication::translate("render", "Boundaries", 0));
        radio_periodic->setText(QApplication::translate("render", "Periodic", 0));
        radio_zero->setText(QApplication::translate("render", "Zero", 0));
        button_defaults->setText(QApplication::translate("render", "Defaults", 0));
        groupBox_6->setTitle(QApplication::translate("render", "Rendering", 0));
        radio_rendering_u->setText(QApplication::translate("render", "U", 0));
        radio_rendering_v->setText(QApplication::translate("render", "V", 0));
        radio_rendering_changeu->setText(QApplication::translate("render", "Change of U", 0));
        checkbox_discard->setText(QApplication::translate("render", "Discard", 0));
        checkbox_displace->setText(QApplication::translate("render", "Displace", 0));
        label_discard_max->setText(QApplication::translate("render", "1.0", 0));
        label_discard_min->setText(QApplication::translate("render", "0", 0));
        label_displace_max->setText(QApplication::translate("render", "1.0", 0));
        label_displace_min->setText(QApplication::translate("render", "0.0", 0));
        button_loadconfig->setText(QApplication::translate("render", "Load Config", 0));
        button_saveconfig->setText(QApplication::translate("render", "Save Config", 0));
    } // retranslateUi

};

namespace Ui {
    class render: public Ui_render {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDER_H
