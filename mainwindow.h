#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stack>
#include <queue>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct Order {
    std::string name;
    std::string items[10];
    int orderQuantity;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onGenerateOrderClicked();
    void onServeOrderClicked();
    void onSeeQueueClicked();
    void onSeeRecentOrderClicked();
    void popOrder();

private:
    Ui::MainWindow *ui;

    std::stack<Order>completedOrders;
    std::queue<Order>orderQueue;

    void generateOrders();
    void serveOrder();
    void displayQueue();
    void displayRecentOrder();
    void updateServeOrderDetails(const Order &order);
    void updateQueueDetails();
    void updateRecentOrderDetails();

    void setBackground(const QString &imagePath);
};
#endif // MAINWINDOW_H
