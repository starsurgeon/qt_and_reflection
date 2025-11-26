#include <QCoreApplication>
#include <QDebug>

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
    return 0;
}
