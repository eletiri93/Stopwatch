#ifndef STOPWATCH_H
#define STOPWATCH_H


#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QDateTime>

class StopWatch : public QWidget
{
    Q_OBJECT
public:
    StopWatch(QWidget * parent = 0);

public slots:
    void stop();
    void play();
    void pause();
    void reset();
    bool stoppedStatus();
    QString getTime();

signals:
    void timeStopped(QString exTime);

protected:
    void timerEvent(QTimerEvent *);

private:
    bool m_running;
    bool m_stopped;
    qint64 m_totMs;

    QLabel * m_label;
    QPushButton * m_playBtn;
    QPushButton * m_stopBtn;
    QPushButton * m_pauseBtn;
    QPushButton * m_resetBtn;
};



#endif // STOPWATCH_H
