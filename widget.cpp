
#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Initially disable drink buttons
    ui->pbCoffee->setEnabled(false);
    ui->pbTea->setEnabled(false);
    ui->pbMilk->setEnabled(false);
}

Widget::~Widget(){
    delete ui;
}

void Widget::changeMoney(int diff){
    if (money + diff < 0) {
        return;
    }
    money += diff;
    ui->lcdNumber->display(money);

    if (money >= 100) {
        ui->pbCoffee->setEnabled(true);
    } else {
        ui->pbCoffee->setEnabled(false);
        ui->pbTea->setEnabled(false);
        ui->pbMilk->setEnabled(false);
    }

    if (money >= 150) {
        ui->pbTea->setEnabled(true);
    }

    if (money >= 200) {
        ui->pbMilk->setEnabled(true);
    }
}

void Widget::on_pb10_clicked(){
    changeMoney(10);
}

void Widget::on_pb50_clicked(){
    changeMoney(50);
}

void Widget::on_pb100_clicked(){
    changeMoney(100);
}

void Widget::on_pb500_clicked(){
    changeMoney(500);
}

void Widget::on_pbCoffee_clicked(){
    if (money >= 100) {
        changeMoney(-100);
    }
}

void Widget::on_pbTea_clicked(){
    changeMoney(-150);
}


void Widget::on_pbMilk_clicked(){
    changeMoney(-200);
}

// Function to calculate the number of coins to return based on the money
std::tuple<int, int, int, int> Widget::calculateChange(int amount)
{
    int num500 = amount / 500;
    amount %= 500;

    int num100 = amount / 100;
    amount %= 100;

    int num50 = amount / 50;
    amount %= 50;

    int num10 = amount / 10;

    return std::make_tuple(num500, num100, num50, num10);
}

void Widget::on_pbRst_clicked(){
    if (money <= 0) {
        QMessageBox::warning(this, "Error", "잔돈이 없습니다!");
        return;
    }

    else {
    std::tuple<int, int, int, int> changeCoins = calculateChange(money);

    int num500 = std::get<0>(changeCoins);
    int num100 = std::get<1>(changeCoins);
    int num50 = std::get<2>(changeCoins);
    int num10 = std::get<3>(changeCoins);

    QString message = "Money:\n";
    message += QString("500원: %1 개\n").arg(num500);
    message += QString("100원: %1 개\n").arg(num100);
    message += QString("50원: %1 개\n").arg(num50);
    message += QString("10원: %1 개").arg(num10);

    QMessageBox::information(this, "Change Details", message);

    money = 0;
    ui->lcdNumber->display(money);
        }

    }



