#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QDebug>
#include <QStandardItem>
#include <QStandardItemModel>
#include <string>
#include<windows.h>
#include<QTimer>
#include<QMenu>
#include<QSignalMapper>
#include "share.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int log_id=-1,log_type=-1;
    QString button_style="QPushButton{background-color:black;\
                          color: white;   border-radius: 10px;  border: 2px groove gray;\
                          border-style: outset;}"
                          "QPushButton:hover{background-color:white; color: black;}"
                          "QPushButton:pressed{background-color:rgb(85, 170, 255);\
                          border-style: inset; }";
    QFont button_font=QFont("Microsoft YaHei", 10, 75);
    int acttype=-1;//0:modify 1:add
    QString sql[9];

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tabWidget_tabBarClicked(int);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void delete_course();

    void modify_course();

    void choose_course();

    void delete_teacher();

    void modify_teacher();

    void choose_teacher();

    void on_buttonBox_2_accepted();

    void on_buttonBox_2_rejected();

    void on_checkBox_4_stateChanged(int arg1);

    void on_checkBox_5_stateChanged(int arg1);

    void on_checkBox_6_stateChanged(int arg1);

    void on_checkBox_7_stateChanged(int arg1);

    void on_buttonBox_3_accepted();

    void on_buttonBox_3_rejected();

    void on_pushButton_6_customContextMenuRequested(const QPoint &pos);

    void Increase_course();

    void Screen_course();

    void Increase_teacher();

    void Screen_teacher();

    void on_checkBox_8_stateChanged(int arg1);

    void on_checkBox_9_stateChanged(int arg1);

    void on_checkBox_10_stateChanged(int arg1);

    void on_checkBox_11_stateChanged(int arg1);

    void screen(int);//course

    void on_pushButton_7_clicked();

    void on_buttonBox_5_accepted();

    void on_buttonBox_5_rejected();

    void on_pushButton_8_clicked();

    void on_buttonBox_6_accepted();

    void on_buttonBox_6_rejected();

    void on_pushButton_9_clicked();

    void on_pushButton_9_customContextMenuRequested(const QPoint &pos);

    void Delete_mentor();

    void on_buttonBox_7_accepted();

    void on_buttonBox_7_rejected();

    void on_pushButton_8_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_10_clicked();

    void delete_student();

    void modify_student();

    void on_buttonBox_8_accepted();

    void on_buttonBox_8_rejected();

    void on_pushButton_11_clicked();

    void on_pushButton_11_customContextMenuRequested(const QPoint &pos);

    void delete_department();

    void modify_department();

    void Screen_department();

    void Increase_department();

    void on_pushButton_12_clicked();

    void on_pushButton_12_customContextMenuRequested(const QPoint &pos);

    void Screen_student();

    void Increase_student();

    void on_pushButton_3_customContextMenuRequested(const QPoint &pos);

    private:
    Ui::MainWindow *ui;
    QStandardItemModel * mod;
};
bool connectMySQL();
#endif // MAINWINDOW_H
