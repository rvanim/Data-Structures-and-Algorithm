#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cstdlib>
#include <iostream>
#include <QPixmap>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setBackground("C:/Users/Acer/Documents/dsa/Group 87.png");

    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::onGenerateOrderClicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::onServeOrderClicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::onSeeQueueClicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::onSeeRecentOrderClicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::popOrder);
}

void MainWindow::setBackground(const QString &imagePath){
    QPixmap pixmap(imagePath);
    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(pixmap);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(0, 0, width(), height());
    backgroundLabel->lower();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onGenerateOrderClicked(){
    generateOrders();
}

void MainWindow::onServeOrderClicked(){
    serveOrder();
}

void MainWindow::onSeeQueueClicked(){
    displayQueue();
}

void MainWindow::onSeeRecentOrderClicked(){
    displayRecentOrder();
}

void MainWindow::generateOrders(){
    static const string filipinoNames[] = {"Juan", "Maria", "Jose", "Ana", "Pedro", "Luisa", "Fernando", "Isabel", "Ramon", "Anakin", "Mina", "Sheree"};
    static const string orderList[] = {"Regular Burger", "Chicken Burger", "Cheeseburger", "Chicken Cheeseburger", "Bacon Burger", "Mushroom Burger", "Ultimate Burger", "Small Fries", "Medium Fries", "Large Fries", "Softdrink"};

    int amountGenerated = rand() % 5 + 1;
    for (int i = 0; i < amountGenerated; ++i){
        Order order;
        order.name = filipinoNames[rand() % 5];
        order.orderQuantity = rand() % 3 + 1;
        for (int j = 0; j < order.orderQuantity; ++j){
            order.items[j] = orderList[rand() % 3];
        }
        orderQueue.push(order);
    }
    ui->statusbar->showMessage("Orders Generated!", 2000);
}

void MainWindow::serveOrder(){
    if (orderQueue.empty()){
        ui->serve->setText("Queue is empty!");
        return;
    }

    Order servedOrder = orderQueue.front();
    orderQueue.pop();
    completedOrders.push(servedOrder);

    updateServeOrderDetails(servedOrder);
}

void MainWindow::updateServeOrderDetails(const Order &order){
    QString details = QString("Serving Order:\nName: %1\nItems: ").arg(QString::fromStdString(order.name));
    for (int i = 0; i < order.orderQuantity; ++i){
        details += QString::fromStdString(order.items[i]) + ", ";
    }
    details.chop(2);
    ui->serve->setText(details);
}

void MainWindow::displayQueue(){
    if (orderQueue.empty()){
        ui->queue->setText("Queue is empty!");
        return;
    }

    updateQueueDetails();
}

void MainWindow::updateQueueDetails(){
    QString details;
    queue<Order> tempQueue = orderQueue;

    while (!tempQueue.empty()){
        Order frontOrder = tempQueue.front();
        tempQueue.pop();

        details += QString("Name: %1\nItems: ").arg(QString::fromStdString(frontOrder.name));
        for (int i = 0; i < frontOrder.orderQuantity; ++i){
            details += QString::fromStdString(frontOrder.items[i]) + ", ";
        }
        details.chop(2);
        details +="\n\n";
    }
    ui->queue->setText(details);
}


void MainWindow::displayRecentOrder(){
    if (completedOrders.empty()){
        ui->recent->setText("No recent orders!");
        return;
    }
    updateRecentOrderDetails();
}

void MainWindow::updateRecentOrderDetails(){
    QString details;
    stack<Order>tempStack = completedOrders;

    while (!tempStack.empty()) {
        Order recentOrder = tempStack.top();
        tempStack.pop();

        details += QString("Name: %1\nItems: ").arg(QString::fromStdString(recentOrder.name));
        for (int i = 0; i < recentOrder.orderQuantity; ++i){
            details += QString::fromStdString(recentOrder.items[i]) + ", ";
        }
        details.chop(2);
        details += "\n\n";
    }
    ui->recent->setText(details);
}

void MainWindow::popOrder() {
    QString nameToRemove = ui->lineEdit->text();
    if (nameToRemove.isEmpty()) {
        ui->statusbar->showMessage("Enter a name.", 2000);
        return;
    }

    if (orderQueue.empty()) {
        ui->statusbar->showMessage("Queue is empty.", 2000);
        return;
    }

    queue<Order> tempQueue;
    bool found = false;

    while (!orderQueue.empty()){
        Order frontOrder = orderQueue.front();
        orderQueue.pop();

        if (QString::fromStdString(frontOrder.name) == nameToRemove) {
            found = true;
        } else {
            tempQueue.push(frontOrder);
        }
    }
    orderQueue = tempQueue;

    if (found) {
        ui->statusbar->showMessage("Name and Order removed.", 2000);
    } else {
        ui->statusbar->showMessage("Invalid name.", 2000);
    }
    displayQueue();
}
