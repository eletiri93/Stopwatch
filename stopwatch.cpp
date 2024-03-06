
#include "stopwatch.h"


StopWatch::StopWatch(QWidget * parent)
    : QWidget(parent),
     m_running(false),
     m_stopped(false),
     m_totMs(0),
     m_label(new QLabel("0:0:0:0"))
{
   // QVBoxLayout * vBoxLayout = new QVBoxLayout(this);
    m_playBtn = new QPushButton("Start");
    m_stopBtn = new QPushButton("Stop");
    m_pauseBtn = new QPushButton("Pause");
    m_resetBtn = new QPushButton("Reset");
    const QSize BUTTON_SIZE = QSize(70, 30);
    m_playBtn->setFixedSize(BUTTON_SIZE);
    m_stopBtn->setFixedSize(BUTTON_SIZE);
    m_pauseBtn->setFixedSize(BUTTON_SIZE);
    m_resetBtn->setFixedSize(BUTTON_SIZE);


    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget (m_resetBtn, 0, 0);
    layout->addWidget (m_playBtn, 0, 1);
    layout->addWidget (m_stopBtn, 1, 1);
    layout->addWidget (m_pauseBtn, 1, 0);
    layout->addWidget (m_label, 2, 1);
    QLine *line = new QLine();

//    vBoxLayout->addWidget(m_resetBtn);
//    vBoxLayout->addWidget(m_pauseBtn);
//    vBoxLayout->addWidget(m_playBtn);
//    vBoxLayout->addWidget(m_stopBtn);
//    vBoxLayout->addWidget(m_label);

    //connect(m_playPauseBtn, SIGNAL(toggled(bool)), SLOT(playPause(bool)));
    connect(m_playBtn, SIGNAL(clicked()), SLOT(play()));
    connect(m_pauseBtn, SIGNAL(clicked()), SLOT(pause()));
    connect(m_stopBtn, SIGNAL(clicked()), SLOT(stop()));
    connect(m_resetBtn, SIGNAL(clicked()), SLOT(reset()));
    startTimer(1);
}

void StopWatch::reset()
{
   m_totMs = 0;
}

void StopWatch::pause()
{
    m_running = false;
}

void StopWatch::play()
{
    m_running = true;
    if(m_stopped)
    {
        m_totMs = 0;
        m_stopped = false;
    }
}

void StopWatch::stop()
{
    m_running = false;
    m_stopped = true;
    QString exTime = m_label->text();
    emit timeStopped(exTime);
}

void StopWatch::timerEvent(QTimerEvent *)
{
    if(m_running)
        m_totMs += 1;

    qint64 ms = m_totMs;
    int h = ms / 1000 / 60 / 60;
    int m = (ms / 1000 / 60) - (h * 60);
    int s = (ms / 1000) - (m * 60);
    ms = ms - (s * 1000);
    QString diff = QString("%1:%2:%3:%4").arg(h).arg(m).arg(s).arg(ms);
    m_label->setText(diff);
}
bool StopWatch::stoppedStatus()
{
    return m_stopped;
}

QString StopWatch::getTime()
{
    return m_label->text();
}





