#include <QCoreApplication>
#include <QDebug>
#include <vector>
#include <print>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    qDebug() << "Qt version:" << qVersion();
    std::vector< int > data;
    data.push_back(2);
    data.push_back(3);
    for (const auto &value : data) {
        qDebug() << "Value:" << value;
    }
    std::println("Hello from print!");
    return 0;
}
