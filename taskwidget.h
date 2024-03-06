#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>

namespace Ui {
class taskWidget;
}

class taskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit taskWidget(QWidget *parent = nullptr);
    ~taskWidget();
    void setNumber(QString number);
    void setTime(QString time);
    void setTask(QString task);

    QString getNote();
    QString getTaskID();

private slots:
    void on_textEdit_textChanged();

signals:
    void noteChanged(QString text);


private:
    Ui::taskWidget *ui;
};

#endif // TASKWIDGET_H
