#ifndef TIMER_H
#define TIMER_H

#include <QWidget>

namespace Ui {
class Timer;
}

class Timer : public QWidget
{
    Q_OBJECT

public:
    explicit Timer(QWidget *parent = nullptr);
    ~Timer();
    void start();
    QString getActualTime();

protected:
    void timerEvent(QTimerEvent *);


private:
    Ui::Timer *ui;

    bool m_running;
    qint64 m_totMs;
};

#endif // TIMER_H
