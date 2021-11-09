#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectMySQL();
    on_tabWidget_tabBarClicked(ui->tabWidget->currentIndex());
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    /*隐藏窗口*/
    ui->groupBox->hide();
    ui->groupBox_2->hide();
    ui->groupBox_3->hide();
    ui->groupBox_4->hide();
    ui->groupBox_5->hide();
    ui->groupBox_6->hide();
    ui->groupBox_7->hide();
    ui->groupBox_8->hide();
    ui->label_27->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool connectMySQL()
{
        db.setHostName("127.0.0.1");
        db.setPort(3306);
        db.setDatabaseName("db1");
        db.setUserName("root");
        db.setPassword("1");
        return db.open();
}

void MainWindow::on_pushButton_clicked()//login 赋予按键权限
{
    QSqlQuery result;
    int templogtype=log_type,templogid=log_id;
    if(ui->checkBox->isChecked())//ad
    {
        result=db.exec("select * from admin where id="+ui->lineEdit->text());
        while(result.next())
        {
            if(result.value("password").toString()==ui->lineEdit_2->text())
            {
                log_id=ui->lineEdit->text().toInt();
                log_type=0;
                ui->tableView->hide();
                ui->page->setEnabled(false);

                ui->lineEdit_2->clear();
                ui->lineEdit_2->setPlaceholderText("登录成功");
            }
        }
    }
    else if(ui->checkBox_2->isChecked())//stu
    {
        result=db.exec("select * from student where sno="+ui->lineEdit->text());
        while(result.next())
        {
            //qDebug()<<result.value("password").toString();
            if(result.value("password").toString()==ui->lineEdit_2->text())
            {
                log_id=ui->lineEdit->text().toInt();
                log_type=1;
                ui->tableView->hide();
                ui->page->setEnabled(true);
                ui->pushButton_9->setEnabled(true);
                ui->pushButton_10->setEnabled(false);

                ui->lineEdit_2->clear();
                ui->lineEdit_2->setPlaceholderText("登录成功");
            }
        }
    }
    else if(ui->checkBox_3->isChecked())//tea
    {
        result=db.exec("select * from teacher where no="+ui->lineEdit->text());
        while(result.next())
        {
            if(result.value("password").toString()==ui->lineEdit_2->text())
            {
                log_id=ui->lineEdit->text().toInt();
                log_type=2;
                ui->tableView->hide();
                ui->page->setEnabled(true);
                ui->pushButton_9->setEnabled(false);
                ui->pushButton_10->setEnabled(true);

                ui->lineEdit_2->clear();
                ui->lineEdit_2->setPlaceholderText("登录成功");
            }
        }
    }
    if(log_type==templogtype&&log_id==templogid)
    {
        ui->lineEdit_2->clear();
        ui->lineEdit_2->setPlaceholderText("登陆失败");
    }
    //qDebug()<<log_id;
}

void MainWindow::on_pushButton_2_clicked()//exit
{
    this->close();
}

void MainWindow::on_tabWidget_tabBarClicked(int i)
{
    if(i==1)
    {
        if(log_type==-1)
        {
            ui->tableView->hide();
            ui->toolBox->setEnabled(false);
        }
        else
        {
            ui->label_3->hide();
            ui->toolBox->setEnabled(true);
        }
    }
}

void MainWindow::on_pushButton_3_clicked()//basic info
{
    mod=new QStandardItemModel;
    ui->tableView->setModel(mod);
    /*隐藏窗口*/
    ui->groupBox->hide();

    ui->tableView->horizontalHeader()->setVisible(false);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setShowGrid(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    QSqlQuery res;

        /*创建按键*/
        /*QPushButton *button1 = new QPushButton("修 改");
        button1->setStyleSheet(button_style);
        button1->setFont(button_font);
        connect(button1, SIGNAL(clicked()), this, SLOT(alter()));
        ui->tableView->setIndexWidget(mod->index(1, 5), button1);*/
    if(log_type==1)
    {
        res.clear();
        res=db.exec("select * from student where sno="+QString::number(log_id));
        int from=2;
        QString a[13]={"学号","姓名","年龄","性别","身高","体重","入学时间","学院","政治面貌","职位","电话","邮箱","住址"};

        res.next();
        mod->setItem(1,from+2,new QStandardItem(res.value(0).toString()));
        mod->setItem(2,from+2,new QStandardItem(res.value(1).toString()));
        mod->setItem(3,from+2,new QStandardItem(res.value(2).toString()));
        mod->setItem(4,from+2,new QStandardItem(res.value(3).toString()));
        mod->setItem(5,from+2,new QStandardItem(res.value(9).toString()+" cm"));
        mod->setItem(6,from+2,new QStandardItem(res.value(10).toString()+" kg"));
        mod->setItem(7,from+2,new QStandardItem(res.value(4).toString()));
        QSqlQuery temp=db.exec("select * from department where dno="+res.value(5).toString());
        temp.next();
        mod->setItem(8,from+2,new QStandardItem(temp.value(1).toString()));
        mod->setItem(9,from+2,new QStandardItem(res.value(11).toString()));
        mod->setItem(10,from+2,new QStandardItem(res.value(12).toString()));
        mod->setItem(11,from+2,new QStandardItem(res.value(8).toString()));
        mod->setItem(12,from+2,new QStandardItem(res.value(7).toString()));
        mod->setItem(13,from+2,new QStandardItem(res.value(13).toString()));

        for(int i=0;i<13;i++)
        {
            mod->setItem(i+1,from,new QStandardItem(a[i]));
            mod->item(i+1,from)->setTextAlignment(Qt::AlignRight);
            mod->item(i+1,from+2)->setTextAlignment(Qt::AlignLeft);
        }
    }
    if(log_type==2)
    {
        res.clear();
        res=db.exec("select * from teacher where no="+QString::number(log_id));
        int from=2;

        res.next();
        QString a[13]={"教师号","姓名","年龄","性别","入职时间","部门","邮箱","电话","身高","体重","政治面貌","职位","住址"};

        mod->setItem(1,from+2,new QStandardItem(res.value("no").toString()));
        mod->setItem(2,from+2,new QStandardItem(res.value("name").toString()));
        mod->setItem(3,from+2,new QStandardItem(res.value("age").toString()));
        mod->setItem(4,from+2,new QStandardItem(res.value("gender").toString()));
        mod->setItem(5,from+2,new QStandardItem(res.value("checkin").toString()));
        QSqlQuery temp;
        temp.exec("select a.dname as tttt from department as a,teacher as b where a.dno="+res.value("Dept").toString());
        temp.next();
        mod->setItem(6,from+2,new QStandardItem(temp.value("tttt").toString()));
        mod->setItem(7,from+2,new QStandardItem(res.value("email").toString()));
        mod->setItem(8,from+2,new QStandardItem(res.value("Phonenumber").toString()));
        mod->setItem(9,from+2,new QStandardItem(res.value("Height").toString()+" cm"));
        mod->setItem(10,from+2,new QStandardItem(res.value("Weight").toString()+" kg"));
        mod->setItem(11,from+2,new QStandardItem(res.value("politics_status").toString()));
        mod->setItem(12,from+2,new QStandardItem(res.value("position").toString()));
        mod->setItem(13,from+2,new QStandardItem(res.value("address").toString()));


        for(int i=0;i<13;i++)
        {
            mod->setItem(i+1,from,new QStandardItem(a[i]));
            mod->item(i+1,from)->setTextAlignment(Qt::AlignRight);
            mod->item(i+1,from+2)->setTextAlignment(Qt::AlignLeft);
        }
    }
    ui->tableView->show();
}

void MainWindow::on_pushButton_4_clicked()//my courses
{
    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->verticalHeader()->setVisible(true);
    ui->tableView->setShowGrid(true);
    QString a[9+1]={"课号","课程名称","上课时间","授课老师","教室","学分","课程性质","考核形式","开课时间","退课"};
    mod=new QStandardItemModel;
    ui->tableView->setModel(mod);
    for(int i=0;i<9+1;i++)
    {
        mod->setHorizontalHeaderItem(i,new QStandardItem(a[i]));
    }
    ui->tableView->setModel(mod);
    QSqlQuery res;

    if(log_type==1)
    {
        int i=0;
        res=db.exec("select * from course,select_course where select_course.stu_no="+QString::number(log_id)+" && select_course.cou_no=course.no");
        while(res.next())
        {
            //qDebug()<<11;
            mod->setItem(i,0,new QStandardItem(res.value("no").toString()));
            mod->setItem(i,1,new QStandardItem(res.value("name").toString()));
            mod->setItem(i,2,new QStandardItem(res.value("time").toString()));
            QSqlQuery temp;
            temp.exec("select a.name as tttt from teacher as a,course as b where a.no="+res.value("teach").toString());
            temp.next();
            mod->setItem(i,3,new QStandardItem(temp.value("tttt").toString()));
            mod->setItem(i,4,new QStandardItem(res.value("room").toString()));
            mod->setItem(i,5,new QStandardItem(res.value("credit").toString()));
            mod->setItem(i,6,new QStandardItem(res.value("cchar").toString()));
            mod->setItem(i,7,new QStandardItem(res.value("ctest").toString()));
            mod->setItem(i,8,new QStandardItem(res.value("checkin").toString()));
            mod->setItem(i,9,new QStandardItem(""));
            /*创建按键*/
            QPushButton *button = new QPushButton("Delete");
            button->setStyleSheet(button_style);
            button->setFont(button_font);
            connect(button, SIGNAL(clicked()), this, SLOT(delete_course()));
            ui->tableView->setIndexWidget(mod->index(i, 9), button);

            i++;
            //qDebug()<<22;
        }
    }
    if(log_type==2)
    {
        int i=0;
        res=db.exec("select * from course where teach="+QString::number(log_id));
        while(res.next())
        {
            //qDebug()<<11;
            mod->setItem(i,0,new QStandardItem(res.value("no").toString()));
            mod->setItem(i,1,new QStandardItem(res.value("name").toString()));
            mod->setItem(i,2,new QStandardItem(res.value("time").toString()));
            QSqlQuery temp;
            temp.exec("select a.name as tttt from teacher as a,course as b where a.no="+res.value("teach").toString());
            temp.next();
            mod->setItem(i,3,new QStandardItem(temp.value("tttt").toString()));
            mod->setItem(i,4,new QStandardItem(res.value("room").toString()));
            mod->setItem(i,5,new QStandardItem(res.value("credit").toString()));
            mod->setItem(i,6,new QStandardItem(res.value("cchar").toString()));
            mod->setItem(i,7,new QStandardItem(res.value("ctest").toString()));
            mod->setItem(i,8,new QStandardItem(res.value("checkin").toString()));
            mod->setItem(i,9,new QStandardItem(""));
            mod->setItem(i,10,new QStandardItem(""));
            /*创建按键*/

            QPushButton *button = new QPushButton("Delete");
            button->setStyleSheet(button_style);
            button->setFont(button_font);
            connect(button, SIGNAL(clicked()), this, SLOT(delete_course()));
            ui->tableView->setIndexWidget(mod->index(i, 9), button);

            QPushButton *button1 = new QPushButton("Modify");
            button1->setStyleSheet(button_style);
            button1->setFont(button_font);
            connect(button1, SIGNAL(clicked()), this, SLOT(modify_course()));
            ui->tableView->setIndexWidget(mod->index(i, 10), button1);

            i++;
            //qDebug()<<22;
        }
    }
    ui->tableView->show();
}

void MainWindow::on_buttonBox_rejected()//xiu gai mi ma
{
    ui->groupBox->hide();
    ui->toolBox->setEnabled(true);
}

void MainWindow::on_buttonBox_accepted()
{
    QSqlQuery res;
    QString t=log_type==0?"admin where id=":log_type==1?"student where sno=":"teacher where no=";
    res=db.exec("select password from "+t+QString::number(log_id));
    res.next();
    if(ui->lineEdit_3->text().isEmpty())
        ui->lineEdit_3->setPlaceholderText("请输入旧密码");
    else if(ui->lineEdit_4->text().isEmpty())
        ui->lineEdit_4->setPlaceholderText("请输入新密码");
    else if(ui->lineEdit_5->text().isEmpty())
        ui->lineEdit_5->setPlaceholderText("请确认密码");
    else if(res.value("password").toString()!=ui->lineEdit_3->text())
    {
        ui->lineEdit_3->clear();
        ui->lineEdit_3->setPlaceholderText("密码错误");
    }
    else if(ui->lineEdit_4->text()!=ui->lineEdit_5->text())
    {
        ui->lineEdit_5->clear();
        ui->lineEdit_5->setPlaceholderText("新密码不匹配");
    }
    else
    {
        res.clear();
        QString t1=log_type==0?"admin ":log_type==1?"student ":"teacher ";
        QString t2=log_type==0?" where id=":log_type==1?" where sno=":" where no=";
        bool alter=res.exec("update "+t1+" set password="+ui->lineEdit_5->text()+t2+QString::number(log_id));
        if(alter)
        {
            ui->groupBox->hide();
            ui->tabWidget->setCurrentIndex(0);
            ui->lineEdit_2->clear();
            ui->lineEdit_2->setPlaceholderText("请重新登录");
            log_type=-1;
        }
    }
    ui->toolBox->setEnabled(true);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->tableView->close();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->groupBox->show();
    ui->toolBox->setEnabled(false);
}

void MainWindow::on_pushButton_6_clicked()//all course
{
    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->verticalHeader()->setVisible(true);
    ui->tableView->setShowGrid(true);

    if(log_type==0)
    {
        QString a[9+2]={"课号","课程名称","上课时间","授课老师","教室","学分","课程性质","考核形式","开课时间","删除","修改"};
        mod=new QStandardItemModel;
        ui->tableView->setModel(mod);
        for(int i=0;i<9+2;i++)
        {
            mod->setHorizontalHeaderItem(i,new QStandardItem(a[i]));
        }
        ui->tableView->setModel(mod);
    }
    if(log_type==1)
    {
        QString a[9+1]={"课号","课程名称","上课时间","授课老师","教室","学分","课程性质","考核形式","开课时间","选课"};
        mod=new QStandardItemModel;
        ui->tableView->setModel(mod);
        for(int i=0;i<9+1;i++)
        {
            mod->setHorizontalHeaderItem(i,new QStandardItem(a[i]));
        }
        ui->tableView->setModel(mod);
    }
    if(log_type==2)
    {
        QString a[9]={"课号","课程名称","上课时间","授课老师","教室","学分","课程性质","考核形式","开课时间"};
        mod=new QStandardItemModel;
        ui->tableView->setModel(mod);
        for(int i=0;i<9;i++)
        {
            mod->setHorizontalHeaderItem(i,new QStandardItem(a[i]));
        }
        ui->tableView->setModel(mod);
    }

    QSqlQuery res;

    if(log_type==0)
    {
        int i=0;
        res=db.exec("select * from course");
        while(res.next())
        {
            mod->setItem(i,0,new QStandardItem(res.value("no").toString()));
            mod->setItem(i,1,new QStandardItem(res.value("name").toString()));
            mod->setItem(i,2,new QStandardItem(res.value("time").toString()));
            QSqlQuery temp;
            temp.exec("select a.name as tttt from teacher as a,course as b where a.no="+res.value("teach").toString());
            temp.next();
            mod->setItem(i,3,new QStandardItem(temp.value("tttt").toString()));
            mod->setItem(i,4,new QStandardItem(res.value("room").toString()));
            mod->setItem(i,5,new QStandardItem(res.value("credit").toString()));
            mod->setItem(i,6,new QStandardItem(res.value("cchar").toString()));
            mod->setItem(i,7,new QStandardItem(res.value("ctest").toString()));
            mod->setItem(i,8,new QStandardItem(res.value("checkin").toString()));

            mod->setItem(i,9,new QStandardItem(""));
            mod->setItem(i,10,new QStandardItem(""));
            /*创建按键*/
            QPushButton *button = new QPushButton("Delete");
            button->setStyleSheet(button_style);
            button->setFont(button_font);
            connect(button, SIGNAL(clicked()), this, SLOT(delete_course()));
            ui->tableView->setIndexWidget(mod->index(i, 9), button);

            QPushButton *button1 = new QPushButton("Modify");
            button1->setStyleSheet(button_style);
            button1->setFont(button_font);
            connect(button1, SIGNAL(clicked()), this, SLOT(modify_course()));
            ui->tableView->setIndexWidget(mod->index(i, 10), button1);

            i++;
        }
    }
    if(log_type==1)
    {
        int i=0;
        res=db.exec("select * from course");
        while(res.next())
        {
            mod->setItem(i,0,new QStandardItem(res.value("no").toString()));
            mod->setItem(i,1,new QStandardItem(res.value("name").toString()));
            mod->setItem(i,2,new QStandardItem(res.value("time").toString()));
            QSqlQuery temp;
            temp.exec("select a.name as tttt from teacher as a,course as b where a.no="+res.value("teach").toString());
            temp.next();
            mod->setItem(i,3,new QStandardItem(temp.value("tttt").toString()));
            mod->setItem(i,4,new QStandardItem(res.value("room").toString()));
            mod->setItem(i,5,new QStandardItem(res.value("credit").toString()));
            mod->setItem(i,6,new QStandardItem(res.value("cchar").toString()));
            mod->setItem(i,7,new QStandardItem(res.value("ctest").toString()));
            mod->setItem(i,8,new QStandardItem(res.value("checkin").toString()));

            mod->setItem(i,9,new QStandardItem(""));
            /*创建按键*/
            QPushButton *button = new QPushButton("Choose");
            button->setStyleSheet(button_style);
            button->setFont(button_font);
            connect(button, SIGNAL(clicked()), this, SLOT(choose_course()));
            ui->tableView->setIndexWidget(mod->index(i, 9), button);

            i++;
        }
    }
    if(log_type==2)
    {
        int i=0;
        res=db.exec("select * from course");
        while(res.next())
        {
            mod->setItem(i,0,new QStandardItem(res.value("no").toString()));
            mod->setItem(i,1,new QStandardItem(res.value("name").toString()));
            mod->setItem(i,2,new QStandardItem(res.value("time").toString()));
            QSqlQuery temp;
            temp.exec("select a.name as tttt from teacher as a,course as b where a.no="+res.value("teach").toString());
            temp.next();
            mod->setItem(i,3,new QStandardItem(temp.value("tttt").toString()));
            mod->setItem(i,4,new QStandardItem(res.value("room").toString()));
            mod->setItem(i,5,new QStandardItem(res.value("credit").toString()));
            mod->setItem(i,6,new QStandardItem(res.value("cchar").toString()));
            mod->setItem(i,7,new QStandardItem(res.value("ctest").toString()));
            mod->setItem(i,8,new QStandardItem(res.value("checkin").toString()));

            i++;
        }
    }
    ui->tableView->show();
}

void MainWindow::delete_course()
{
    //qDebug()<<ui->tableView->currentIndex().row();
    ui->groupBox_2->show();
    //ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);//无法选中，防止row变化
    ui->tableView->setEnabled(false);//防止row变化
    ui->toolBox->setEnabled(false);
}

void MainWindow::modify_course()
{
    acttype=0;//
    ui->groupBox_3->setTitle("Modify");
    //ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);//无法选中，防止row变化
    ui->tableView->setEnabled(false);//防止row变化
    ui->toolBox->setEnabled(false);
    //qDebug()<<ui->tableView->currentIndex();
    int temprow=ui->tableView->currentIndex().row();
    ui->lineEdit_6->clear();
    ui->lineEdit_6->setPlaceholderText((mod->index(temprow,1,QModelIndex()).data().toString()));

    ui->lineEdit_7->clear();
    ui->lineEdit_7->setPlaceholderText((mod->index(temprow,2,QModelIndex()).data().toString()));
    /*combobox*/
    ui->comboBox->clear();
    QSqlQuery temp=db.exec("select no,name from teacher");
    while(temp.next())
    {
        ui->comboBox->addItem(temp.value("no").toString()+" "+temp.value("name").toString());
    }
    temp=db.exec("select teach from course where no="+mod->index(temprow,0,QModelIndex()).data().toString());
    temp.next();
    ui->comboBox->setCurrentText(temp.value("teach").toString()+" "+(mod->index(temprow,3,QModelIndex()).data().toString()));

    ui->lineEdit_8->clear();
    ui->lineEdit_8->setPlaceholderText((mod->index(temprow,4,QModelIndex()).data().toString()));

    ui->doubleSpinBox->setValue((mod->index(temprow,5,QModelIndex()).data().toDouble()));
    mod->index(temprow,6,QModelIndex()).data().toString()=="选修"?ui->checkBox_4->setChecked(true):ui->checkBox_5->setChecked(true);
    mod->index(temprow,7,QModelIndex()).data().toString()=="考试"?ui->checkBox_6->setChecked(true):ui->checkBox_7->setChecked(true);
    ui->dateEdit->setDate(mod->index(temprow,8,QModelIndex()).data().toDate());

    ui->groupBox_3->show();
}

void MainWindow::choose_course()
{
    //qDebug()<<ui->tableView->currentIndex().row();
    ui->groupBox_5->show();
    //ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);//无法选中，防止row变化
    ui->tableView->setEnabled(false);//防止row变化
    ui->toolBox->setEnabled(false);
}

void MainWindow::on_buttonBox_3_accepted()//modify course/add course
{
    ui->lineEdit_6->setPlaceholderText("");
    ui->lineEdit_7->setPlaceholderText("");
    ui->lineEdit_8->setPlaceholderText("");
    /*ui->dateEdit->clear();
    ui->comboBox->clear();
    ui->doubleSpinBox->setValue(2);*/

    if(log_type==0)//管理员可以修改所有course
    {
        //ui->comboBox->setEnabled(true);
        //ui->comboBox->setDisabled(false);
    }
    if(log_type==2)//老师只可以自己的
    {
        //ui->comboBox->setEnabled(false);
        //ui->comboBox->setDisabled(true);
    }

    if(acttype==0)
    {
        //QString a[9]={"课号","课程名称","上课时间","授课老师","教室","学分","课程性质","考核形式","开课时间"};
        int temp=ui->tableView->currentIndex().row();
        //qDebug()<<temp;
        QString exeqs;
        if(!ui->lineEdit_6->text().isEmpty())
        {
            exeqs="update course set name='"+ui->lineEdit_6->text()+"' where no="+mod->index(temp,0,QModelIndex()).data().toString();
            db.exec(exeqs);
        }

        if(!ui->lineEdit_7->text().isEmpty())
        {
            exeqs="update course set time='"+ui->lineEdit_7->text()+"' where no="+mod->index(temp,0,QModelIndex()).data().toString();
            db.exec(exeqs);
        }

        exeqs="update course set teach="+ui->comboBox->currentText().left(7)+" where no="+mod->index(temp,0,QModelIndex()).data().toString();
        db.exec(exeqs);

        if(!ui->lineEdit_8->text().isEmpty())
        {
            exeqs="update course set room='"+ui->lineEdit_8->text()+"' where no="+mod->index(temp,0,QModelIndex()).data().toString();
            db.exec(exeqs);
        }

        exeqs="update course set Credit='"+QString::number(ui->doubleSpinBox->value())+"' where no="+mod->index(temp,0,QModelIndex()).data().toString();
        db.exec(exeqs);

        QString tempxb=ui->checkBox_4->isChecked()?"选修":"必修";
        exeqs="update course set Cchar='"+tempxb+"' where no="+mod->index(temp,0,QModelIndex()).data().toString();
        db.exec(exeqs);

        tempxb=ui->checkBox_6->isChecked()?"考试":"考查";
        exeqs="update course set Ctest='"+tempxb+"' where no="+mod->index(temp,0,QModelIndex()).data().toString();
        db.exec(exeqs);

        exeqs="update course set Checkin='"+ui->dateEdit->date().toString("yyyy-MM-dd")+"' where no="+mod->index(temp,0,QModelIndex()).data().toString();
        db.exec(exeqs);

        if(1)
        {
            ui->label_7->setText("Successfully modified course :"+mod->index(temp,0,QModelIndex()).data().toString());
        }
        else
        {
            ui->label_7->setText("Modify failed !");
        }
        ui->label_7->show();
        QTimer::singleShot(1000,ui->label_7,SLOT(hide()));

        ui->groupBox_3->hide();

        //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableView->setEnabled(true);
        ui->toolBox->setEnabled(true);

        QSqlQuery res=db.exec("select * from course where no="+mod->index(temp,0,QModelIndex()).data().toString());
        res.next();
        mod->setItem(temp,0,new QStandardItem(res.value("no").toString()));
        mod->setItem(temp,1,new QStandardItem(res.value("name").toString()));
        mod->setItem(temp,2,new QStandardItem(res.value("time").toString()));
        QSqlQuery temp_chtab;
        temp_chtab.exec("select a.name as tttt from teacher as a,course as b where a.no="+res.value("teach").toString());
        temp_chtab.next();
        mod->setItem(temp,3,new QStandardItem(temp_chtab.value("tttt").toString()));
        mod->setItem(temp,4,new QStandardItem(res.value("room").toString()));
        mod->setItem(temp,5,new QStandardItem(res.value("credit").toString()));
        mod->setItem(temp,6,new QStandardItem(res.value("cchar").toString()));
        mod->setItem(temp,7,new QStandardItem(res.value("ctest").toString()));
        mod->setItem(temp,8,new QStandardItem(res.value("checkin").toString()));
    }
    else if(acttype==1)
    {
        bool addflag=1;
        QString addstr="insert into course (name,time,teach,room,credit,cchar,ctest,checkin) values (";
        if(ui->lineEdit_6->text().isEmpty())
        {
            ui->lineEdit_6->setPlaceholderText("请输入课程名");
            addflag=0;
        }
        else
            addstr.append("'"+ui->lineEdit_6->text()+"',");

        if(ui->lineEdit_7->text().isEmpty())
        {
            ui->lineEdit_7->setPlaceholderText("请输入上课时间");
            addflag=0;
        }
        else
            addstr.append("'"+ui->lineEdit_7->text()+"',");

        addstr.append(ui->comboBox->currentText().left(7)+",");

        if(ui->lineEdit_8->text().isEmpty())
        {
            ui->lineEdit_8->setPlaceholderText("请输入教室");
            addflag=0;
        }
        else
            addstr.append("'"+ui->lineEdit_8->text()+"',");

        addstr.append(QString::number(ui->doubleSpinBox->value())+",");

        QString tempxb=ui->checkBox_4->isChecked()?"选修":"必修";
        addstr.append("'"+tempxb+"',");

        tempxb=ui->checkBox_6->isChecked()?"考试":"考查";
        addstr.append("'"+tempxb+"',");

        addstr.append("'"+ui->dateEdit->date().toString("yyyy-MM-dd")+"');");

        //qDebug()<<addstr;
        if(addflag)
        {
            db.exec("ALTER TABLE course AUTO_INCREMENT = 1;");//自增连续
            db.exec(addstr);

            ui->label_7->setText("Successfully increase course :"+ui->lineEdit_6->text());
            ui->label_7->show();
            QTimer::singleShot(1000,ui->label_7,SLOT(hide()));

            ui->groupBox_3->hide();

            //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->tableView->setEnabled(true);
            ui->toolBox->setEnabled(true);

            /*更新table*/
            int i=-1;
            QSqlQuery res;
            res=db.exec("select * from course");
            while(res.next())
            {
                i++;
            }
            res.last();
            mod->setItem(i,0,new QStandardItem(res.value("no").toString()));
            mod->setItem(i,1,new QStandardItem(res.value("name").toString()));
            mod->setItem(i,2,new QStandardItem(res.value("time").toString()));
            QSqlQuery temp;
            temp.exec("select a.name as tttt from teacher as a,course as b where a.no="+res.value("teach").toString());
            temp.next();
            mod->setItem(i,3,new QStandardItem(temp.value("tttt").toString()));
            mod->setItem(i,4,new QStandardItem(res.value("room").toString()));
            mod->setItem(i,5,new QStandardItem(res.value("credit").toString()));
            mod->setItem(i,6,new QStandardItem(res.value("cchar").toString()));
            mod->setItem(i,7,new QStandardItem(res.value("ctest").toString()));
            mod->setItem(i,8,new QStandardItem(res.value("checkin").toString()));

            mod->setItem(i,9,new QStandardItem(""));
            mod->setItem(i,10,new QStandardItem(""));
            /*创建按键*/
            QPushButton *button = new QPushButton("Delete");
            button->setStyleSheet(button_style);
            button->setFont(button_font);
            connect(button, SIGNAL(clicked()), this, SLOT(delete_course()));
            ui->tableView->setIndexWidget(mod->index(i, 9), button);

            QPushButton *button1 = new QPushButton("Modify");
            button1->setStyleSheet(button_style);
            button1->setFont(button_font);
            connect(button1, SIGNAL(clicked()), this, SLOT(modify_course()));
            ui->tableView->setIndexWidget(mod->index(i, 10), button1);
        }
    }
}

void MainWindow::on_buttonBox_3_rejected()
{
    ui->groupBox_3->hide();
    if(acttype==0)
        ui->label_7->setText("Unmodify !");
    else if(acttype==1)
        ui->label_7->setText("Unincrease !");
    ui->label_7->show();
    QTimer::singleShot(1000,ui->label_7,SLOT(hide()));
    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEnabled(true);
    ui->toolBox->setEnabled(true);
}

void MainWindow::on_buttonBox_2_accepted()//删除课
{
    int temp_row=ui->tableView->currentIndex().row();
    QModelIndex temp=mod->index(temp_row,0,QModelIndex());
    QModelIndex temp1=mod->index(temp_row,1,QModelIndex());
    ui->groupBox_2->hide();
    QSqlQuery r;
    bool t=true;
    if(log_type==0||log_type==2)
        t=r.exec("delete from course where no="+temp.data().toString());
    if(log_type==1)
    {
        t=r.exec("delete from select_course where stu_no="+QString::number(log_id)+"&&cou_no="+temp.data().toString());
        //qDebug()<<"delete from select_course where stu_no="+QString::number(log_id)+"&&cou_no="+temp.data().toString();
    }
    if(t)
    {
        ui->label_7->setText("Successfully deleted course :"+temp.data().toString()+" "+temp1.data().toString());
        //qDebug()<<ui->tableView->currentIndex().row();
        mod->removeRow(temp_row);
    }
    else
    {
        ui->label_7->setText("Delete failed !");
    }
    ui->label_7->show();
    QTimer::singleShot(1000,ui->label_7,SLOT(hide()));

    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEnabled(true);
    ui->toolBox->setEnabled(true);
}

void MainWindow::on_buttonBox_2_rejected()
{
    ui->groupBox_2->hide();
    ui->label_7->setText("Undelete !");
    ui->label_7->show();
    QTimer::singleShot(1000,ui->label_7,SLOT(hide()));

    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEnabled(true);
    ui->toolBox->setEnabled(true);
}

void MainWindow::on_checkBox_4_stateChanged(int arg1)//互斥按键
{
    if(arg1==Qt::CheckState::Checked)
    {
        ui->checkBox_5->blockSignals(true);
        ui->checkBox_5->setCheckState(Qt::CheckState::Unchecked);
        ui->checkBox_5->blockSignals(false);
    }
    if(arg1==Qt::CheckState::Unchecked)
    {
        ui->checkBox_5->blockSignals(true);
        ui->checkBox_5->setCheckState(Qt::CheckState::Checked);
        ui->checkBox_5->blockSignals(false);
    }
}

void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    if(arg1==Qt::CheckState::Checked)
    {
        ui->checkBox_4->blockSignals(true);
        ui->checkBox_4->setCheckState(Qt::CheckState::Unchecked);
        ui->checkBox_4->blockSignals(false);
    }
    if(arg1==Qt::CheckState::Unchecked)
    {
        ui->checkBox_4->blockSignals(true);
        ui->checkBox_4->setCheckState(Qt::CheckState::Checked);
        ui->checkBox_4->blockSignals(false);
    }
}

void MainWindow::on_checkBox_6_stateChanged(int arg1)
{
    if(arg1==Qt::CheckState::Checked)
    {
        ui->checkBox_7->blockSignals(true);
        ui->checkBox_7->setCheckState(Qt::CheckState::Unchecked);
        ui->checkBox_7->blockSignals(false);
    }
    if(arg1==Qt::CheckState::Unchecked)
    {
        ui->checkBox_7->blockSignals(true);
        ui->checkBox_7->setCheckState(Qt::CheckState::Checked);
        ui->checkBox_7->blockSignals(false);
    }
}

void MainWindow::on_checkBox_7_stateChanged(int arg1)
{
    if(arg1==Qt::CheckState::Checked)
    {
        ui->checkBox_6->blockSignals(true);
        ui->checkBox_6->setCheckState(Qt::CheckState::Unchecked);
        ui->checkBox_6->blockSignals(false);
    }
    if(arg1==Qt::CheckState::Unchecked)
    {
        ui->checkBox_6->blockSignals(true);
        ui->checkBox_6->setCheckState(Qt::CheckState::Checked);
        ui->checkBox_6->blockSignals(false);
    }
}

void MainWindow::on_pushButton_6_customContextMenuRequested(const QPoint &/*pos*/)//all course menu
{
    QMenu *cmenu = new QMenu(ui->pushButton);
    QAction *action2 = new QAction(tr("Screen"), this);
    cmenu->addAction(action2);
    // 下面这个on_menu_click(bool)槽函数做自己想做的事
    connect(action2, SIGNAL(triggered(bool)), this, SLOT(Screen_course()));
    if(log_type==0||log_type==2)
    {
        QAction *action1 = new QAction(tr("Increase"), this);
        cmenu->addAction(action1);
        connect(action1, SIGNAL(triggered(bool)), this, SLOT(Increase_course()));
    }
    cmenu->exec(QCursor::pos());
}

void MainWindow::Increase_course()
{
    acttype=1;
    //qDebug()<<11;
    ui->tableView->setEnabled(false);//防止row变化
    ui->toolBox->setEnabled(false);

    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();

    ui->comboBox->clear();
    QSqlQuery temp=db.exec("select no,name from teacher");
    while(temp.next())
    {
        ui->comboBox->addItem(temp.value("no").toString()+" "+temp.value("name").toString());
    }

    ui->doubleSpinBox->setValue(2);
    ui->checkBox_4->setChecked(true);
    ui->checkBox_6->setChecked(true);
    ui->dateEdit->setDate(QDate::currentDate());

    ui->groupBox_3->setTitle("Increase");
    ui->groupBox_3->show();
}

void MainWindow::Screen_course()
{
    //qDebug()<<22;
    //ui->tableView->setEnabled(false);//防止row变化
    ui->toolBox->setEnabled(false);
    ui->lineEdit_9->clear();
    ui->lineEdit_10->clear();
    ui->lineEdit_11->clear();
    ui->lineEdit_12->clear();
    ui->comboBox_2->clear();
    QSqlQuery temp=db.exec("select no,name from teacher");
    while(temp.next())
    {
        ui->comboBox_2->addItem(temp.value("no").toString()+" "+temp.value("name").toString());
    }
    ui->doubleSpinBox_2->setValue(0);
    ui->doubleSpinBox_3->setValue(10);
    ui->checkBox_8->setChecked(true);
    ui->checkBox_10->setChecked(true);
    QString s="10000101";
    ui->dateEdit_2->setDate(QDate::fromString(s,"yyyyMMdd"));
    s="99991231";
    ui->dateEdit_3->setDate(QDate::fromString(s,"yyyyMMdd"));

    sql[0]=" name like '%"+ui->lineEdit_9->text()+"%' ";
    sql[1]=" time like '%"+ui->lineEdit_10->text()+"%' ";
    sql[2]=" room like '%"+ui->lineEdit_11->text()+"%' ";
    sql[3]=" cast(no as char) like '%"+ui->lineEdit_12->text()+"%' ";
    sql[4]=" teach="+ui->comboBox_2->currentText().left(7)+" ";
    sql[5]=" Credit>="+QString::number(ui->doubleSpinBox_2->value())+"&& Credit<="+QString::number(ui->doubleSpinBox_3->value())+" ";
    QString tempxb=ui->checkBox_8->isChecked()?"选修":"必修";
    sql[6]=" Cchar='"+tempxb+"' ";
    tempxb=ui->checkBox_10->isChecked()?"考试":"考查";
    sql[7]=" Ctest='"+tempxb+"' ";
    sql[8]=" Checkin>='"+ui->dateEdit_2->date().toString("yyyy-MM-dd")+"'&&Checkin<='"+ui->dateEdit_3->date().toString("yyyy-MM-dd")+"' ";

    ui->groupBox_4->show();

    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(ui->lineEdit_9,SIGNAL(textChanged(QString)),signalMapper,SLOT(map()));
    connect(ui->lineEdit_10,SIGNAL(textChanged(QString)),signalMapper,SLOT(map()));
    connect(ui->lineEdit_11,SIGNAL(textChanged(QString)),signalMapper,SLOT(map()));
    connect(ui->lineEdit_12,SIGNAL(textChanged(QString)),signalMapper,SLOT(map()));
    connect(ui->comboBox_2,SIGNAL(currentTextChanged(QString)),signalMapper,SLOT(map()));
    connect(ui->doubleSpinBox_2,SIGNAL(valueChanged(double)),signalMapper,SLOT(map()));
    connect(ui->checkBox_8,SIGNAL(stateChanged(int)),signalMapper,SLOT(map()));
    connect(ui->checkBox_10,SIGNAL(stateChanged(int)),signalMapper,SLOT(map()));
    connect(ui->checkBox_9,SIGNAL(stateChanged(int)),signalMapper,SLOT(map()));
    connect(ui->checkBox_11,SIGNAL(stateChanged(int)),signalMapper,SLOT(map()));
    connect(ui->dateEdit_2,SIGNAL(dateChanged(QDate)),signalMapper,SLOT(map()));
    connect(ui->dateEdit_3,SIGNAL(dateChanged(QDate)),signalMapper,SLOT(map()));
    signalMapper->setMapping(ui->lineEdit_9,9);
    signalMapper->setMapping(ui->lineEdit_10,10);
    signalMapper->setMapping(ui->lineEdit_11,11);
    signalMapper->setMapping(ui->lineEdit_12,12);
    signalMapper->setMapping(ui->comboBox_2,0);//teach
    signalMapper->setMapping(ui->doubleSpinBox_2,1);//xuefen
    signalMapper->setMapping(ui->checkBox_8,2);//xuan bi
    signalMapper->setMapping(ui->checkBox_10,3);//shi cha
    signalMapper->setMapping(ui->checkBox_9,2);//xuan bi
    signalMapper->setMapping(ui->checkBox_11,3);//shi cha
    signalMapper->setMapping(ui->dateEdit_2,4);
    signalMapper->setMapping(ui->dateEdit_3,4);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(screen(int)));
}

void MainWindow::screen(int index)
{
    //qDebug()<<index;
    QSqlQuery res;
    switch(index)
    {
    case 9:
    {
        sql[0]=" name like '%"+ui->lineEdit_9->text()+"%' ";
        break;
    }
    case 10:
    {
        sql[1]=" time like '%"+ui->lineEdit_10->text()+"%' ";
        break;
    }
    case 11:
    {
        sql[2]=" room like '%"+ui->lineEdit_11->text()+"%' ";
        break;
    }
    case 12:
    {
        sql[3]=" cast(no as char) like '%"+ui->lineEdit_12->text()+"%' ";
        break;
    }
    case 0:
    {
        sql[4]=" teach="+ui->comboBox_2->currentText().left(7)+" ";
        break;
    }
    case 1:
    {
        sql[5]=" Credit>="+QString::number(ui->doubleSpinBox_2->value())+"&& Credit<="+QString::number(ui->doubleSpinBox_3->value())+" ";
        break;
    }
    case 2:
    {
        QString tempxb=ui->checkBox_8->isChecked()?"选修":"必修";
        sql[6]=" Cchar='"+tempxb+"' ";
        break;
    }
    case 3:
    {
        QString tempxb=ui->checkBox_10->isChecked()?"考试":"考查";
        sql[7]=" Ctest='"+tempxb+"' ";
        break;
    }
    case 4:
    {
        sql[8]=" Checkin>='"+ui->dateEdit_2->date().toString("yyyy-MM-dd")+"'&&Checkin<='"+ui->dateEdit_3->date().toString("yyyy-MM-dd")+"' ";
        break;
    }
    }
    //qDebug()<<sql;
    QString allsql="select * from course where ";
    for(int k=0;k<8;k++)
    {
        allsql.append(sql[k]);
        allsql.append(" && ");
    }
    allsql.append(sql[8]);
    //qDebug()<<allsql;

    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->verticalHeader()->setVisible(true);
    ui->tableView->setShowGrid(true);

    if(log_type==0)
    {
        QString a[9+2]={"课号","课程名称","上课时间","授课老师","教室","学分","课程性质","考核形式","开课时间","删除","修改"};
        mod=new QStandardItemModel;
        ui->tableView->setModel(mod);
        for(int i=0;i<9+2;i++)
        {
            mod->setHorizontalHeaderItem(i,new QStandardItem(a[i]));
        }
        ui->tableView->setModel(mod);
    }
    if(log_type==1)
    {
        QString a[9+1]={"课号","课程名称","上课时间","授课老师","教室","学分","课程性质","考核形式","开课时间","选课"};
        mod=new QStandardItemModel;
        ui->tableView->setModel(mod);
        for(int i=0;i<9+1;i++)
        {
            mod->setHorizontalHeaderItem(i,new QStandardItem(a[i]));
        }
        ui->tableView->setModel(mod);
    }

    ui->tableView->setModel(mod);
    res=db.exec(allsql);
    int i=0;
    if(log_type==0)
    {
        while(res.next())
        {
            mod->setItem(i,0,new QStandardItem(res.value("no").toString()));
            mod->setItem(i,1,new QStandardItem(res.value("name").toString()));
            mod->setItem(i,2,new QStandardItem(res.value("time").toString()));
            QSqlQuery temp;
            temp.exec("select a.name as tttt from teacher as a,course as b where a.no="+res.value("teach").toString());
            temp.next();
            mod->setItem(i,3,new QStandardItem(temp.value("tttt").toString()));
            mod->setItem(i,4,new QStandardItem(res.value("room").toString()));
            mod->setItem(i,5,new QStandardItem(res.value("credit").toString()));
            mod->setItem(i,6,new QStandardItem(res.value("cchar").toString()));
            mod->setItem(i,7,new QStandardItem(res.value("ctest").toString()));
            mod->setItem(i,8,new QStandardItem(res.value("checkin").toString()));

            mod->setItem(i,9,new QStandardItem(""));
            mod->setItem(i,10,new QStandardItem(""));
            /*创建按键*/
            QPushButton *button = new QPushButton("Delete");
            button->setStyleSheet(button_style);
            button->setFont(button_font);
            connect(button, SIGNAL(clicked()), this, SLOT(delete_course()));
            ui->tableView->setIndexWidget(mod->index(i, 9), button);

            QPushButton *button1 = new QPushButton("Modify");
            button1->setStyleSheet(button_style);
            button1->setFont(button_font);
            connect(button1, SIGNAL(clicked()), this, SLOT(modify_course()));
            ui->tableView->setIndexWidget(mod->index(i, 10), button1);

            i++;
        }
    }
    if(log_type==1)
    {
        while(res.next())
        {
            mod->setItem(i,0,new QStandardItem(res.value("no").toString()));
            mod->setItem(i,1,new QStandardItem(res.value("name").toString()));
            mod->setItem(i,2,new QStandardItem(res.value("time").toString()));
            QSqlQuery temp;
            temp.exec("select a.name as tttt from teacher as a,course as b where a.no="+res.value("teach").toString());
            temp.next();
            mod->setItem(i,3,new QStandardItem(temp.value("tttt").toString()));
            mod->setItem(i,4,new QStandardItem(res.value("room").toString()));
            mod->setItem(i,5,new QStandardItem(res.value("credit").toString()));
            mod->setItem(i,6,new QStandardItem(res.value("cchar").toString()));
            mod->setItem(i,7,new QStandardItem(res.value("ctest").toString()));
            mod->setItem(i,8,new QStandardItem(res.value("checkin").toString()));

            mod->setItem(i,9,new QStandardItem(""));
            /*创建按键*/
            QPushButton *button = new QPushButton("Choose");
            button->setStyleSheet(button_style);
            button->setFont(button_font);
            connect(button, SIGNAL(clicked()), this, SLOT(choose_course()));
            ui->tableView->setIndexWidget(mod->index(i, 9), button);

            i++;
        }
    }

}

void MainWindow::on_checkBox_8_stateChanged(int arg1)
{
    if(arg1==Qt::CheckState::Checked)
    {
        ui->checkBox_9->blockSignals(true);
        ui->checkBox_9->setCheckState(Qt::CheckState::Unchecked);
        ui->checkBox_9->blockSignals(false);
    }
    if(arg1==Qt::CheckState::Unchecked)
    {
        ui->checkBox_9->blockSignals(true);
        ui->checkBox_9->setCheckState(Qt::CheckState::Checked);
        ui->checkBox_9->blockSignals(false);
    }
}

void MainWindow::on_checkBox_9_stateChanged(int arg1)
{
    if(arg1==Qt::CheckState::Checked)
    {
        ui->checkBox_8->blockSignals(true);
        ui->checkBox_8->setCheckState(Qt::CheckState::Unchecked);
        ui->checkBox_8->blockSignals(false);
    }
    if(arg1==Qt::CheckState::Unchecked)
    {
        ui->checkBox_8->blockSignals(true);
        ui->checkBox_8->setCheckState(Qt::CheckState::Checked);
        ui->checkBox_8->blockSignals(false);
    }
}

void MainWindow::on_checkBox_10_stateChanged(int arg1)
{
    if(arg1==Qt::CheckState::Checked)
    {
        ui->checkBox_11->blockSignals(true);
        ui->checkBox_11->setCheckState(Qt::CheckState::Unchecked);
        ui->checkBox_11->blockSignals(false);
    }
    if(arg1==Qt::CheckState::Unchecked)
    {
        ui->checkBox_11->blockSignals(true);
        ui->checkBox_11->setCheckState(Qt::CheckState::Checked);
        ui->checkBox_11->blockSignals(false);
    }
}

void MainWindow::on_checkBox_11_stateChanged(int arg1)
{
    if(arg1==Qt::CheckState::Checked)
    {
        ui->checkBox_10->blockSignals(true);
        ui->checkBox_10->setCheckState(Qt::CheckState::Unchecked);
        ui->checkBox_10->blockSignals(false);
    }
    if(arg1==Qt::CheckState::Unchecked)
    {
        ui->checkBox_10->blockSignals(true);
        ui->checkBox_10->setCheckState(Qt::CheckState::Checked);
        ui->checkBox_10->blockSignals(false);
    }
}

void MainWindow::on_pushButton_7_clicked()//guan screen
{
    ui->groupBox_4->hide();

    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableView->setEnabled(true);
    ui->toolBox->setEnabled(true);
}

void MainWindow::on_buttonBox_5_accepted()//xuanke
{
    int temp_row=ui->tableView->currentIndex().row();
    QModelIndex temp=mod->index(temp_row,0,QModelIndex());
    QModelIndex temp1=mod->index(temp_row,1,QModelIndex());
    ui->groupBox_5->hide();
    QSqlQuery r;
    bool t=true;
    if(log_type==1)
    {
        //t=r.exec("delete from select_course where stu_no="+QString::number(log_id)+"&&cou_no="+temp.data().toString());
        t=r.exec("insert into select_course values("+QString::number(log_id)+","+temp.data().toString()+")");
    }
    if(t)
    {
        ui->label_7->setText("Successfully chose course :"+temp.data().toString()+" "+temp1.data().toString());
        //qDebug()<<ui->tableView->currentIndex().row();
    }
    else
    {
        ui->label_7->setText("You have already chosen this course !");
    }
    ui->label_7->show();
    QTimer::singleShot(1000,ui->label_7,SLOT(hide()));

    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEnabled(true);
    ui->toolBox->setEnabled(true);
}

void MainWindow::on_buttonBox_5_rejected()
{
    ui->groupBox_5->hide();
    ui->label_7->setText("Unchoose !");
    ui->label_7->show();
    QTimer::singleShot(1000,ui->label_7,SLOT(hide()));

    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEnabled(true);
    ui->toolBox->setEnabled(true);
}

void MainWindow::on_pushButton_8_clicked()//all teacher
{
    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->verticalHeader()->setVisible(true);
    ui->tableView->setShowGrid(true);

    if(log_type==0)
    {
        QString a[15]={"教师号","姓名","年龄","性别","入职时间","部门","邮箱","电话","身高","体重","政治面貌","职位","住址","删除","修改"};
        mod=new QStandardItemModel;
        ui->tableView->setModel(mod);
        for(int i=0;i<15;i++)
        {
            mod->setHorizontalHeaderItem(i,new QStandardItem(a[i]));
        }
        ui->tableView->setModel(mod);
    }
    if(log_type==1)
    {
        QString a[14]={"教师号","姓名","年龄","性别","入职时间","部门","邮箱","电话","身高","体重","政治面貌","职位","住址","选择导师"};
        mod=new QStandardItemModel;
        ui->tableView->setModel(mod);
        for(int i=0;i<14;i++)
        {
            mod->setHorizontalHeaderItem(i,new QStandardItem(a[i]));
        }
        ui->tableView->setModel(mod);
    }
    if(log_type==2)
    {
        QString a[13]={"教师号","姓名","年龄","性别","入职时间","部门","邮箱","电话","身高","体重","政治面貌","职位","住址"};
        mod=new QStandardItemModel;
        ui->tableView->setModel(mod);
        for(int i=0;i<13;i++)
        {
            mod->setHorizontalHeaderItem(i,new QStandardItem(a[i]));
        }
        ui->tableView->setModel(mod);
    }

    QSqlQuery res;

    if(log_type==0)
    {
        int i=0;
        res=db.exec("select * from teacher");
        while(res.next())
        {
            mod->setItem(i,0,new QStandardItem(res.value("no").toString()));
            mod->setItem(i,1,new QStandardItem(res.value("name").toString()));
            mod->setItem(i,2,new QStandardItem(res.value("age").toString()));
            mod->setItem(i,3,new QStandardItem(res.value("gender").toString()));
            mod->setItem(i,4,new QStandardItem(res.value("checkin").toString()));
            QSqlQuery temp;
            temp.exec("select a.dname as tttt from department as a,teacher as b where a.dno="+res.value("Dept").toString());
            temp.next();
            mod->setItem(i,5,new QStandardItem(temp.value("tttt").toString()));
            mod->setItem(i,6,new QStandardItem(res.value("email").toString()));
            mod->setItem(i,7,new QStandardItem(res.value("Phonenumber").toString()));
            mod->setItem(i,8,new QStandardItem(res.value("Height").toString()+" cm"));
            mod->setItem(i,9,new QStandardItem(res.value("Weight").toString()+" kg"));
            mod->setItem(i,10,new QStandardItem(res.value("politics_status").toString()));
            mod->setItem(i,11,new QStandardItem(res.value("position").toString()));
            mod->setItem(i,12,new QStandardItem(res.value("address").toString()));

            mod->setItem(i,13,new QStandardItem(""));
            mod->setItem(i,14,new QStandardItem(""));
            /*创建按键*/
            QPushButton *button = new QPushButton("Delete");
            button->setStyleSheet(button_style);
            button->setFont(button_font);
            connect(button, SIGNAL(clicked()), this, SLOT(delete_teacher()));
            ui->tableView->setIndexWidget(mod->index(i, 13), button);

            QPushButton *button1 = new QPushButton("Modify");
            button1->setStyleSheet(button_style);
            button1->setFont(button_font);
            connect(button1, SIGNAL(clicked()), this, SLOT(modify_teacher()));
            ui->tableView->setIndexWidget(mod->index(i, 14), button1);

            i++;
        }
    }
    if(log_type==1)
    {
        int i=0;
        res=db.exec("select * from teacher");
        while(res.next())
        {
            mod->setItem(i,0,new QStandardItem(res.value("no").toString()));
            mod->setItem(i,1,new QStandardItem(res.value("name").toString()));
            mod->setItem(i,2,new QStandardItem(res.value("age").toString()));
            mod->setItem(i,3,new QStandardItem(res.value("gender").toString()));
            mod->setItem(i,4,new QStandardItem(res.value("checkin").toString()));
            QSqlQuery temp;
            temp.exec("select a.dname as tttt from department as a,teacher as b where a.dno="+res.value("Dept").toString());
            temp.next();
            mod->setItem(i,5,new QStandardItem(temp.value("tttt").toString()));
            mod->setItem(i,6,new QStandardItem(res.value("email").toString()));
            mod->setItem(i,7,new QStandardItem(res.value("Phonenumber").toString()));
            mod->setItem(i,8,new QStandardItem(res.value("Height").toString()));
            mod->setItem(i,9,new QStandardItem(res.value("Weight").toString()));
            mod->setItem(i,10,new QStandardItem(res.value("politics_status").toString()));
            mod->setItem(i,11,new QStandardItem(res.value("position").toString()));
            mod->setItem(i,12,new QStandardItem(res.value("address").toString()));

            mod->setItem(i,13,new QStandardItem(""));
            /*创建按键*/
            QPushButton *button = new QPushButton("Choose");
            button->setStyleSheet(button_style);
            button->setFont(button_font);
            connect(button, SIGNAL(clicked()), this, SLOT(choose_teacher()));
            ui->tableView->setIndexWidget(mod->index(i, 13), button);

            i++;
        }
    }
    if(log_type==2)
    {
        int i=0;
        res=db.exec("select * from teacher");
        while(res.next())
        {
            mod->setItem(i,0,new QStandardItem(res.value("no").toString()));
            mod->setItem(i,1,new QStandardItem(res.value("name").toString()));
            mod->setItem(i,2,new QStandardItem(res.value("age").toString()));
            mod->setItem(i,3,new QStandardItem(res.value("gender").toString()));
            mod->setItem(i,4,new QStandardItem(res.value("checkin").toString()));
            QSqlQuery temp;
            temp.exec("select a.dname as tttt from department as a,teacher as b where a.dno="+res.value("Dept").toString());
            temp.next();
            mod->setItem(i,5,new QStandardItem(temp.value("tttt").toString()));
            mod->setItem(i,6,new QStandardItem(res.value("email").toString()));
            mod->setItem(i,7,new QStandardItem(res.value("Phonenumber").toString()));
            mod->setItem(i,8,new QStandardItem(res.value("Height").toString()));
            mod->setItem(i,9,new QStandardItem(res.value("Weight").toString()));
            mod->setItem(i,10,new QStandardItem(res.value("politics_status").toString()));
            mod->setItem(i,11,new QStandardItem(res.value("position").toString()));
            mod->setItem(i,12,new QStandardItem(res.value("address").toString()));

            i++;
        }
    }
    ui->tableView->show();
}

void MainWindow::delete_teacher()
{
    //qDebug()<<ui->tableView->currentIndex().row();
    ui->groupBox_6->show();
    //ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);//无法选中，防止row变化
    ui->tableView->setEnabled(false);//防止row变化
    ui->toolBox->setEnabled(false);
}

void MainWindow::modify_teacher()
{

}

void MainWindow::choose_teacher()//xuan dao shi
{
    //qDebug()<<ui->tableView->currentIndex().row();
    ui->groupBox_7->show();
    //ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);//无法选中，防止row变化
    ui->tableView->setEnabled(false);//防止row变化
    ui->toolBox->setEnabled(false);
}

void MainWindow::on_buttonBox_6_accepted()//del tea
{
    int temp_row=ui->tableView->currentIndex().row();
    QModelIndex temp=mod->index(temp_row,0,QModelIndex());
    QModelIndex temp1=mod->index(temp_row,1,QModelIndex());
    ui->groupBox_6->hide();
    QSqlQuery r;
    bool t=false;
    if(log_type==0)
        t=r.exec("delete from teacher where no="+temp.data().toString());
    if(log_type==1)
    {
        QSqlQuery res;
        res=db.exec("select * from select_teacher where stu_no="+QString::number(log_id));
        if(res.next())
        {
            QString tea_no=res.value("tea_no").toString();
            t=r.exec("delete from select_teacher where stu_no="+QString::number(log_id)+"&&tea_no="+tea_no);
            //qDebug()<<"delete from select_course where stu_no="+QString::number(log_id)+"&&cou_no="+temp.data().toString();
            on_pushButton_9_clicked();
        }
        else
        {
            ui->label_7->setText("You don't have a mentor !");
        }
    }
    if(t)
    {
        ui->label_7->setText("Successfully deleted teacher :"+temp.data().toString()+" "+temp1.data().toString());
        //qDebug()<<ui->tableView->currentIndex().row();
        mod->removeRow(temp_row);
    }
    else
    {
        ui->label_7->setText("Delete failed !");
    }
    ui->label_7->show();
    QTimer::singleShot(1000,ui->label_7,SLOT(hide()));

    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEnabled(true);
    ui->toolBox->setEnabled(true);
}

void MainWindow::on_buttonBox_6_rejected()
{
    ui->groupBox_6->hide();
    ui->label_7->setText("Undelete !");
    ui->label_7->show();
    QTimer::singleShot(1000,ui->label_7,SLOT(hide()));

    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEnabled(true);
    ui->toolBox->setEnabled(true);
}

void MainWindow::on_pushButton_9_clicked()//wo de dao shi
{
    mod=new QStandardItemModel;
    ui->tableView->setModel(mod);
    /*隐藏窗口*/
    ui->groupBox->hide();

    ui->tableView->horizontalHeader()->setVisible(false);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setShowGrid(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    QSqlQuery res;
    res=db.exec("select * from select_teacher where stu_no="+QString::number(log_id));
    if(res.next())
    {
        QString tea_no=res.value("tea_no").toString();
        res.clear();
        res=db.exec("select * from teacher where no="+tea_no);
        res.next();

            int from=2;
            QString a[13]={"教师号","姓名","年龄","性别","入职时间","部门","邮箱","电话","身高","体重","政治面貌","职位","住址"};

            mod->setItem(1,from+2,new QStandardItem(res.value("no").toString()));
            mod->setItem(2,from+2,new QStandardItem(res.value("name").toString()));
            mod->setItem(3,from+2,new QStandardItem(res.value("age").toString()));
            mod->setItem(4,from+2,new QStandardItem(res.value("gender").toString()));
            mod->setItem(5,from+2,new QStandardItem(res.value("checkin").toString()));
            QSqlQuery temp;
            temp.exec("select a.dname as tttt from department as a,teacher as b where a.dno="+res.value("Dept").toString());
            temp.next();
            mod->setItem(6,from+2,new QStandardItem(temp.value("tttt").toString()));
            mod->setItem(7,from+2,new QStandardItem(res.value("email").toString()));
            mod->setItem(8,from+2,new QStandardItem(res.value("Phonenumber").toString()));
            mod->setItem(9,from+2,new QStandardItem(res.value("Height").toString()+" cm"));
            mod->setItem(10,from+2,new QStandardItem(res.value("Weight").toString()+" kg"));
            mod->setItem(11,from+2,new QStandardItem(res.value("politics_status").toString()));
            mod->setItem(12,from+2,new QStandardItem(res.value("position").toString()));
            mod->setItem(13,from+2,new QStandardItem(res.value("address").toString()));


            for(int i=0;i<13;i++)
            {
                mod->setItem(i+1,from,new QStandardItem(a[i]));
                mod->item(i+1,from)->setTextAlignment(Qt::AlignRight);
                mod->item(i+1,from+2)->setTextAlignment(Qt::AlignLeft);
            }
    }
    else
    {
        ui->label_27->show();
        QTimer::singleShot(1000,ui->label_27,SLOT(hide()));
    }
    ui->tableView->show();
}

void MainWindow::on_pushButton_9_customContextMenuRequested(const QPoint &/*pos*/)//删除导师
{
    //qDebug()<<11111;
    QMenu *cmenu = new QMenu(ui->pushButton);
    QAction *action1 = new QAction(tr("Delete mentor"), this);
    cmenu->addAction(action1);
    // 下面这个on_menu_click(bool)槽函数做自己想做的事
    connect(action1, SIGNAL(triggered(bool)), this, SLOT(Delete_mentor()));
    cmenu->exec(QCursor::pos());
}

void MainWindow::Delete_mentor()
{
    //qDebug()<<ui->tableView->currentIndex().row();
    ui->groupBox_6->show();
    //ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);//无法选中，防止row变化
    ui->tableView->setEnabled(false);//防止row变化
    ui->toolBox->setEnabled(false);
}

void MainWindow::on_buttonBox_7_accepted()//xuan dao shi
{
    int temp_row=ui->tableView->currentIndex().row();
    QModelIndex temp=mod->index(temp_row,0,QModelIndex());
    QModelIndex temp1=mod->index(temp_row,1,QModelIndex());
    ui->groupBox_7->hide();
    QSqlQuery r;
    bool t=true;

    QSqlQuery res;
    res=db.exec("select * from select_teacher where stu_no="+QString::number(log_id));
    if(res.next())
    {
        ui->label_7->setText("You have already chosen a mentor !");
    }
    else
    {
        if(log_type==1)
        {
            t=r.exec("insert into select_teacher values("+QString::number(log_id)+","+temp.data().toString()+")");
        }
        if(t)
        {
            ui->label_7->setText("Successfully chose course :"+temp.data().toString()+" "+temp1.data().toString());
            //qDebug()<<ui->tableView->currentIndex().row();
        }
        else
        {
            ui->label_7->setText("choose this mentor failed !");
        }
    }
    ui->label_7->show();
    QTimer::singleShot(1000,ui->label_7,SLOT(hide()));

    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEnabled(true);
    ui->toolBox->setEnabled(true);
}

void MainWindow::on_buttonBox_7_rejected()
{
    ui->groupBox_7->hide();
    ui->label_7->setText("Unchoose !");
    ui->label_7->show();
    QTimer::singleShot(1000,ui->label_7,SLOT(hide()));

    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEnabled(true);
    ui->toolBox->setEnabled(true);
}

void MainWindow::on_pushButton_8_customContextMenuRequested(const QPoint &/*pos*/)//all teacher menu
{
    QMenu *cmenu = new QMenu(ui->pushButton);
    QAction *action2 = new QAction(tr("Screen"), this);
    cmenu->addAction(action2);
    // 下面这个on_menu_click(bool)槽函数做自己想做的事
    connect(action2, SIGNAL(triggered(bool)), this, SLOT(Screen_teacher()));
    if(log_type==0)
    {
        QAction *action1 = new QAction(tr("Increase"), this);
        cmenu->addAction(action1);
        connect(action1, SIGNAL(triggered(bool)), this, SLOT(Increase_teacher()));
    }
    cmenu->exec(QCursor::pos());
}

void MainWindow::Increase_teacher()
{

}

void MainWindow::Screen_teacher()
{

}

void MainWindow::on_pushButton_10_clicked()//my students
{
    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->verticalHeader()->setVisible(true);
    ui->tableView->setShowGrid(true);

    if(log_type==2)
    {
        QString a[14]={"学号","姓名","年龄","性别","身高","体重","入学时间","学院","政治面貌","职位","电话","邮箱","住址","删除"};
        mod=new QStandardItemModel;
        ui->tableView->setModel(mod);
        for(int i=0;i<14;i++)
        {
            mod->setHorizontalHeaderItem(i,new QStandardItem(a[i]));
        }
        ui->tableView->setModel(mod);
    }

    QSqlQuery res;


    if(log_type==2)
    {
        int i=0;
        res=db.exec("select * from student,select_teacher where tea_no="+QString::number(log_id)+"&& student.sno=select_teacher.stu_no");
        while(res.next())
        {
            mod->setItem(i,0,new QStandardItem(res.value(0).toString()));
            mod->setItem(i,1,new QStandardItem(res.value(1).toString()));
            mod->setItem(i,2,new QStandardItem(res.value(2).toString()));
            mod->setItem(i,3,new QStandardItem(res.value(3).toString()));
            mod->setItem(i,4,new QStandardItem(res.value(9).toString()+" cm"));
            mod->setItem(i,5,new QStandardItem(res.value(10).toString()+" kg"));
            mod->setItem(i,6,new QStandardItem(res.value(4).toString()));
            QSqlQuery temp=db.exec("select * from department where dno="+res.value(5).toString());
            temp.next();
            mod->setItem(i,7,new QStandardItem(temp.value(1).toString()));
            mod->setItem(i,8,new QStandardItem(res.value(11).toString()));
            mod->setItem(i,9,new QStandardItem(res.value(12).toString()));
            mod->setItem(i,10,new QStandardItem(res.value(8).toString()));
            mod->setItem(i,11,new QStandardItem(res.value(7).toString()));
            mod->setItem(i,12,new QStandardItem(res.value(13).toString()));

            mod->setItem(i,13,new QStandardItem(""));
            /*创建按键*/
            QPushButton *button = new QPushButton("Delete");
            button->setStyleSheet(button_style);
            button->setFont(button_font);
            connect(button, SIGNAL(clicked()), this, SLOT(delete_student()));
            ui->tableView->setIndexWidget(mod->index(i, 13), button);

            i++;
        }
    }
    ui->tableView->show();
}

void MainWindow::delete_student()
{
    //qDebug()<<ui->tableView->currentIndex().row();
    ui->groupBox_8->show();
    //ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);//无法选中，防止row变化
    ui->tableView->setEnabled(false);//防止row变化
    ui->toolBox->setEnabled(false);
}

void MainWindow::on_buttonBox_8_accepted()//删学生
{
    int temp_row=ui->tableView->currentIndex().row();
    QModelIndex temp=mod->index(temp_row,0,QModelIndex());
    QModelIndex temp1=mod->index(temp_row,1,QModelIndex());
    ui->groupBox_8->hide();
    QSqlQuery r;
    bool t=false;
    if(log_type==0)
        t=r.exec("delete from student where sno="+temp.data().toString());
    if(log_type==2)
    {
        t=r.exec("delete from select_teacher where stu_no="+temp.data().toString());
    }
    if(t)
    {
        ui->label_7->setText("Successfully deleted student :"+temp.data().toString()+" "+temp1.data().toString());
        //qDebug()<<ui->tableView->currentIndex().row();
        mod->removeRow(temp_row);
    }
    else
    {
        ui->label_7->setText("Delete failed !");
    }
    ui->label_7->show();
    QTimer::singleShot(1000,ui->label_7,SLOT(hide()));

    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEnabled(true);
    ui->toolBox->setEnabled(true);
}

void MainWindow::on_buttonBox_8_rejected()
{
    ui->groupBox_8->hide();
    ui->label_7->setText("Undelete !");
    ui->label_7->show();
    QTimer::singleShot(1000,ui->label_7,SLOT(hide()));

    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEnabled(true);
    ui->toolBox->setEnabled(true);
}

void MainWindow::on_pushButton_11_clicked()//all depart
{
    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->verticalHeader()->setVisible(true);
    ui->tableView->setShowGrid(true);

    if(log_type==0)
    {
        QString a[4]={"部门号","部门名称","删除","修改"};
        mod=new QStandardItemModel;
        ui->tableView->setModel(mod);
        for(int i=0;i<4;i++)
        {
            mod->setHorizontalHeaderItem(i,new QStandardItem(a[i]));
        }
        ui->tableView->setModel(mod);
    }
    if(log_type==1||log_type==2)
    {
        QString a[2]={"部门号","部门名称"};
        mod=new QStandardItemModel;
        ui->tableView->setModel(mod);
        for(int i=0;i<2;i++)
        {
            mod->setHorizontalHeaderItem(i,new QStandardItem(a[i]));
        }
        ui->tableView->setModel(mod);
    }

    QSqlQuery res;

    if(log_type==0)
    {
        int i=0;
        res=db.exec("select * from department");
        while(res.next())
        {
            mod->setItem(i,0,new QStandardItem(res.value("dno").toString()));
            mod->setItem(i,1,new QStandardItem(res.value("dname").toString()));

            mod->setItem(i,2,new QStandardItem(""));
            mod->setItem(i,3,new QStandardItem(""));
            /*创建按键*/
            QPushButton *button = new QPushButton("Delete");
            button->setStyleSheet(button_style);
            button->setFont(button_font);
            connect(button, SIGNAL(clicked()), this, SLOT(delete_department()));
            ui->tableView->setIndexWidget(mod->index(i, 2), button);

            QPushButton *button1 = new QPushButton("Modify");
            button1->setStyleSheet(button_style);
            button1->setFont(button_font);
            connect(button1, SIGNAL(clicked()), this, SLOT(modify_department()));
            ui->tableView->setIndexWidget(mod->index(i, 3), button1);

            i++;
        }
    }
    if(log_type==1||log_type==2)
    {
        int i=0;
        res=db.exec("select * from department");
        while(res.next())
        {
            mod->setItem(i,0,new QStandardItem(res.value("dno").toString()));
            mod->setItem(i,1,new QStandardItem(res.value("dname").toString()));

            i++;
        }
    }

    ui->tableView->show();
}

void MainWindow::on_pushButton_11_customContextMenuRequested(const QPoint &/*pos*/)//depart menu
{
    QMenu *cmenu = new QMenu(ui->pushButton);
    QAction *action2 = new QAction(tr("Screen"), this);
    cmenu->addAction(action2);
    // 下面这个on_menu_click(bool)槽函数做自己想做的事
    connect(action2, SIGNAL(triggered(bool)), this, SLOT(Screen_department()));
    if(log_type==0)
    {
        QAction *action1 = new QAction(tr("Increase"), this);
        cmenu->addAction(action1);
        connect(action1, SIGNAL(triggered(bool)), this, SLOT(Increase_department()));
    }
    cmenu->exec(QCursor::pos());
}

void MainWindow::delete_department()
{

}

void MainWindow::modify_department()
{

}

void MainWindow::Screen_department()
{

}

void MainWindow::Increase_department()
{

}

void MainWindow::on_pushButton_12_clicked()//all student
{
    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->verticalHeader()->setVisible(true);
    ui->tableView->setShowGrid(true);


    if(log_type==0)
    {
        QString a[13+2]={"学号","姓名","年龄","性别","身高","体重","入学时间","学院","政治面貌","职位","电话","邮箱","住址","删除","修改"};
        mod=new QStandardItemModel;
        ui->tableView->setModel(mod);
        for(int i=0;i<13+2;i++)
        {
            mod->setHorizontalHeaderItem(i,new QStandardItem(a[i]));
        }
        ui->tableView->setModel(mod);
    }
    if(log_type==2||log_type==1)
    {
        QString a[13]={"学号","姓名","年龄","性别","身高","体重","入学时间","学院","政治面貌","职位","电话","邮箱","住址"};
        mod=new QStandardItemModel;
        ui->tableView->setModel(mod);
        for(int i=0;i<13;i++)
        {
            mod->setHorizontalHeaderItem(i,new QStandardItem(a[i]));
        }
        ui->tableView->setModel(mod);
    }

    QSqlQuery res;


    if(log_type==0)
    {
        int i=0;
        res=db.exec("select * from student");
        while(res.next())
        {
            mod->setItem(i,0,new QStandardItem(res.value(0).toString()));
            mod->setItem(i,1,new QStandardItem(res.value(1).toString()));
            mod->setItem(i,2,new QStandardItem(res.value(2).toString()));
            mod->setItem(i,3,new QStandardItem(res.value(3).toString()));
            mod->setItem(i,4,new QStandardItem(res.value(9).toString()+" cm"));
            mod->setItem(i,5,new QStandardItem(res.value(10).toString()+" kg"));
            mod->setItem(i,6,new QStandardItem(res.value(4).toString()));
            QSqlQuery temp=db.exec("select * from department where dno="+res.value(5).toString());
            temp.next();
            mod->setItem(i,7,new QStandardItem(temp.value(1).toString()));
            mod->setItem(i,8,new QStandardItem(res.value(11).toString()));
            mod->setItem(i,9,new QStandardItem(res.value(12).toString()));
            mod->setItem(i,10,new QStandardItem(res.value(8).toString()));
            mod->setItem(i,11,new QStandardItem(res.value(7).toString()));
            mod->setItem(i,12,new QStandardItem(res.value(13).toString()));

            mod->setItem(i,13,new QStandardItem(""));
            mod->setItem(i,14,new QStandardItem(""));
            /*创建按键*/
            QPushButton *button = new QPushButton("Delete");
            button->setStyleSheet(button_style);
            button->setFont(button_font);
            connect(button, SIGNAL(clicked()), this, SLOT(delete_student()));
            ui->tableView->setIndexWidget(mod->index(i, 13), button);

            QPushButton *button1 = new QPushButton("Modify");
            button1->setStyleSheet(button_style);
            button1->setFont(button_font);
            connect(button1, SIGNAL(clicked()), this, SLOT(modify_student()));
            ui->tableView->setIndexWidget(mod->index(i, 14), button1);


            i++;
        }
    }
    if(log_type==2||log_type==1)
    {
        int i=0;
        res=db.exec("select * from student");
        while(res.next())
        {
            mod->setItem(i,0,new QStandardItem(res.value(0).toString()));
            mod->setItem(i,1,new QStandardItem(res.value(1).toString()));
            mod->setItem(i,2,new QStandardItem(res.value(2).toString()));
            mod->setItem(i,3,new QStandardItem(res.value(3).toString()));
            mod->setItem(i,4,new QStandardItem(res.value(9).toString()+" cm"));
            mod->setItem(i,5,new QStandardItem(res.value(10).toString()+" kg"));
            mod->setItem(i,6,new QStandardItem(res.value(4).toString()));
            QSqlQuery temp=db.exec("select * from department where dno="+res.value(5).toString());
            temp.next();
            mod->setItem(i,7,new QStandardItem(temp.value(1).toString()));
            mod->setItem(i,8,new QStandardItem(res.value(11).toString()));
            mod->setItem(i,9,new QStandardItem(res.value(12).toString()));
            mod->setItem(i,10,new QStandardItem(res.value(8).toString()));
            mod->setItem(i,11,new QStandardItem(res.value(7).toString()));
            mod->setItem(i,12,new QStandardItem(res.value(13).toString()));

            i++;
        }
    }
    ui->tableView->show();
}

void MainWindow::modify_student()
{

}
void MainWindow::on_pushButton_12_customContextMenuRequested(const QPoint &/*pos*/)//all student menu
{
    QMenu *cmenu = new QMenu(ui->pushButton);
    QAction *action2 = new QAction(tr("Screen"), this);
    cmenu->addAction(action2);
    // 下面这个on_menu_click(bool)槽函数做自己想做的事
    connect(action2, SIGNAL(triggered(bool)), this, SLOT(Screen_student()));
    if(log_type==0)
    {
        QAction *action1 = new QAction(tr("Increase"), this);
        cmenu->addAction(action1);
        connect(action1, SIGNAL(triggered(bool)), this, SLOT(Increase_student()));
    }
    cmenu->exec(QCursor::pos());
}

void MainWindow::Screen_student()
{

}

void MainWindow::Increase_student()
{

}

void MainWindow::on_pushButton_3_customContextMenuRequested(const QPoint &/*pos*/)//修改基本信息
{
    QMenu *cmenu = new QMenu(ui->pushButton);
    if(log_type==1)
    {
        QAction *action1 = new QAction(tr("Modify"), this);
        cmenu->addAction(action1);
        connect(action1, SIGNAL(triggered(bool)), this, SLOT(modify_student()));
    }
    if(log_type==2)
    {
        QAction *action1 = new QAction(tr("Modify"), this);
        cmenu->addAction(action1);
        connect(action1, SIGNAL(triggered(bool)), this, SLOT(modify_teacher()));
    }
    cmenu->exec(QCursor::pos());
}
