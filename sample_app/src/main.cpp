#include <QCoreApplication>
#include <QDebug>
#include <vector>
#include <print>
#include <meta>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    qDebug() << "Qt version:" << qVersion();
    std::vector< int > data;
    data.push_back(2);
    data.push_back(3);
    // for (const auto &value : data) {
    //     qDebug() << "Value:" << value;
    // }
    std::println("Hello from print!");

    int x = 42;
    constexpr auto r = ^^int;
    [:r:] y =42;
    [:^^char:] str = '*';


    // std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
    // for( const auto&[idx, val] : numbers | std::views::enumerate ) 
    // {
    //     std::println("Index: {}, Value: {}", idx, val);
    // }

    return 0;
}
