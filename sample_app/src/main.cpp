#include <QCoreApplication>
#include <QDebug>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    qDebug() << "Qt version:" << qVersion();
    return 0;
}
