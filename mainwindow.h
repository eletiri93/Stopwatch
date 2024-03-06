#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>
#include <QFile>
#include <QStackedWidget>
#include "stopwatch.h"
#include "taskwidget.h"
#include "timer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool init();

private slots:
//    void on_pushButton_3_clicked();
    void on_pushButton_3_clicked();
    void on_pushButtonPrev_clicked();
    void on_pushButtonNext_clicked();
    void onTaskChanged();
    void onStopWatcherStopped(QString exTime);
    void onTextChanged(QString text);
    void on_pushButton_clicked();
    void writeCsv();

signals:
    void taskChanged();

private:
    Ui::MainWindow *ui;
    StopWatch *m_StopWatcher;
    QStackedWidget *m_widgetStacks;
    Timer *m_timer;
    struct Data{
        QString taskId;
        QString textEditor;
        QString executionTime;
        QString recTime;
        QString markedTime;
    } m_data;

    QList <Data> m_list;
};
#endif // MAINWINDOW_H


