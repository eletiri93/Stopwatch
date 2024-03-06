#include "timer.h"
#include "ui_timer.h"

Timer::Timer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Timer),
    m_running(true)
{
    ui->setupUi(this);
    startTimer(1);
    m_totMs = 0;

}

void Timer::start()
{
    m_running = true;
}

QString Timer:: getActualTime()
{
    return(ui->label->text());
}

Timer::~Timer()
{
    delete ui;
}


void Timer::timerEvent(QTimerEvent *)
{
    if(m_running)
        m_totMs += 1;

    qint64 ms = m_totMs;
    int h = ms / 1000 / 60 / 60;
    int m = (ms / 1000 / 60) - (h * 60);
    int s = (ms / 1000) - (m * 60);
    //ms = ms - (s * 1000);
    QString diff = QString("%1:%2:%3").arg(h).arg(m).arg(s);
    ui->label->setText(diff);
}
