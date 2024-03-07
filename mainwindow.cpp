#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextStream>
#include <QTableWidgetItem>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_StopWatcher = new StopWatch(ui->stopWatch);
    m_widgetStacks = new QStackedWidget(ui->widget);
    m_widgetStacks->resize(ui->widget->size());
    m_timer = new Timer(ui->widget_2);
    m_timer->resize(ui->widget_2->size());
    m_timer-> start();

    connect(this, &MainWindow::taskChanged,
            this, &MainWindow::onTaskChanged);
    connect(m_StopWatcher, &StopWatch::timeStopped,
            this, &MainWindow::onStopWatcherStopped);
}

bool MainWindow::init()
{
    QFile file("taskList.csv");
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug("failed");
        return false;
    }

    QTextStream in(&file);
    QList< QStringList > lists;
    QString line;
    do {
        line = in.readLine();
        lists << line.split(";");
    } while(!line.isNull());
    qDebug()<< lists;
    for ( int row = 0; row < lists.size()-1; ++row )
    {
        taskWidget *item = new taskWidget();
        item->setNumber(lists[row][0]);
        item->setTask(lists[row][1]);
        item->setTime(lists[row][2]);
        m_widgetStacks->addWidget(item);
        connect(item, &taskWidget::noteChanged,
                this, &MainWindow::onTextChanged);
    }
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_widgetStacks);
    setLayout(layout);
    m_data.taskId = "1";
    m_data.executionTime = m_timer->getActualTime();

    ui->tableWidget->setRowCount(lists.size() );
    ui->tableWidget->setColumnCount(5);
    return true;
}

void MainWindow::on_pushButton_3_clicked()
{
   QString savedTime = m_timer->getActualTime();
   m_data.markedTime += (" " + savedTime);
}

void MainWindow::on_pushButtonPrev_clicked()
{
    int currentIdx = m_widgetStacks->currentIndex();
    if(currentIdx -1 >= 0)
       m_widgetStacks->setCurrentIndex(currentIdx - 1);
}

void MainWindow::on_pushButtonNext_clicked()
{
    int currentIdx = m_widgetStacks->currentIndex();
    if(currentIdx +1 <= m_widgetStacks->count())
        m_widgetStacks->setCurrentIndex(currentIdx + 1);

    emit taskChanged();
}

void MainWindow::onTaskChanged()
{
    if(m_StopWatcher->stoppedStatus() == false)
        m_data.executionTime = m_StopWatcher->getTime();

   m_list.append(m_data);
   m_data.textEditor = "";
   m_data.markedTime = "";

   m_data.executionTime = "";

   taskWidget *item = static_cast<taskWidget*>( m_widgetStacks->currentWidget());
   m_data.taskId = item->getTaskID();
   m_data.recTime = m_timer->getActualTime();
   int idx = m_widgetStacks->currentIndex();
   ui->tableWidget->setItem(idx, 0, new QTableWidgetItem(m_list[idx-1].taskId));
   ui->tableWidget->setItem(idx, 1, new QTableWidgetItem(m_list[idx-1].textEditor));
   ui->tableWidget->setItem(idx, 2, new QTableWidgetItem(m_list[idx-1].executionTime));
   ui->tableWidget->setItem(idx, 3, new QTableWidgetItem(m_list[idx-1].recTime));
   ui->tableWidget->setItem(idx, 4, new QTableWidgetItem(m_list[idx-1].markedTime));
}

void MainWindow::onTextChanged(QString text)
{
    m_data.textEditor = text;
}

void MainWindow::on_pushButton_clicked()
{
    writeCsv();
}

void MainWindow::writeCsv()
{
    QList<QString> output;
    for (int i = 0; i < m_list.size(); ++i)
    {
        QString item = m_list.at(i).taskId;
        QString item2 = m_list.at(i).textEditor;
        QString item3 = m_list.at(i).executionTime;
        QString item4 = m_list.at(i).recTime;
        QString item5 = m_list.at(i).markedTime;
        QString task = item + ";"+item2+ ";"+item3+ ";"+item4 + ";" + item5;
        output.append(task);
    }

//    QList<QString> output;
//    for (int i = 0; i < ui->tableWidget->columnCount(); ++i)
//    {
//        QString item = ui->tableWidget->itemAt(i,0)->text();
//        QString item2 = ui->tableWidget->itemAt(i,1)->text();
//        QString item3 = ui->tableWidget->itemAt(i,2)->text();
//        QString item4 = ui->tableWidget->itemAt(i,3)->text();
//        QString item5 = ui->tableWidget->itemAt(i,4)->text();

//        QString task = item + ";"+item2+ ";"+item3+ ";"+item4 + ";" + item5;
//        output.append(task);
//    }

    // Open csv-file
    QFile file("Tester1.csv");
    file.open(QIODevice::Append | QIODevice::Text);

    // Write data to file
    QTextStream stream(&file);
    QString separator(",");
    for (int i = 0; i < output.size(); ++i)
    {
        stream << output.at(i)<< endl;
    }

    stream.flush();
    file.close();
}

void MainWindow::onStopWatcherStopped(QString exTime)
{
    m_data.executionTime = exTime;
}

MainWindow::~MainWindow()
{
    delete ui;
}


