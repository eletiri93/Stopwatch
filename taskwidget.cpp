#include "taskwidget.h"
#include "ui_taskwidget.h"
#include <QDebug>

taskWidget::taskWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::taskWidget)
{
    ui->setupUi(this);
    ui->labelTask->setWordWrap(true);

    QFont font = ui->labelTask->font();
    font.setPointSize(11);
    ui->labelTask->setFont(font);
    ui->labelNo->setFont(font);
}

taskWidget::~taskWidget()
{
    delete ui;
}

void taskWidget::setNumber(QString number)
{
    ui->labelNo->setText(number);
}

void taskWidget::setTime(QString time)
{
    ui->labelTime->setText(time);
}

void taskWidget::setTask(QString task)
{
    ui->labelTask->setText(task);
}

QString taskWidget::getNote()
{
    qDebug() << ui->textEdit->toPlainText();
    return ui->textEdit->toPlainText();
}

QString taskWidget::getTaskID()
{
    qDebug() <<ui->labelNo->text();
    return ui->labelNo->text();
}

void taskWidget::on_textEdit_textChanged()
{
     qDebug() << ui->textEdit->toPlainText();
     emit noteChanged(ui->textEdit->toPlainText());
}
