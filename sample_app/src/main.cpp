#include <QCoreApplication>
#include <QDebug>
#include <cstddef>
#include <meta>
#include <print>
#include <vector>
#include <array>
#include <string_view>

enum class lineType : unsigned short { None, Solid, Dashed, Dotted };

template <typename E>
  requires std::is_enum_v<E>
consteval std::string enum_to_string(E value) 
{
  for ( const auto &e : std::meta::enumerators_of(^^E)) 
  {
    if (value == std::meta::extract<E>(e)) 
    {
      return std::string(std::meta::identifier_of(e));
    }
  }

  return "<unnamed>";
}


static_assert(enum_to_string(lineType::None) == "None");
static_assert(enum_to_string(lineType(42)) == "<unnamed>");

template<typename E> requires std::is_enum_v<E> struct enumItem
{ 
  std::string_view name; 
  E value;
};

template<typename E>  requires std::is_enum_v<E>
consteval auto getEnumData() 
{
  std::array<enumItem<E>, std::meta::enumerators_of(^^E).size()> result;
  int k = 0;
  for (auto mem: std::meta::enumerators_of(^^E))
  {
    result[k++] = enumItem<E>{ std::meta::identifier_of(mem), std::meta::extract<E>(mem) };
  }
  return result;
}


int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);
  qDebug() << "Qt version:" << qVersion();
  std::vector<int> data;
  data.push_back(2);
  data.push_back(3);
  // for (const auto &value : data) {
  //     qDebug() << "Value:" << value;
  // }
  std::println("Hello from print!");

  int x = 42;
  constexpr auto r = ^^int;
  [:r:] y = 42;
  [:^^char:] str = '*';
  
  constexpr auto enum_data = getEnumData<lineType>();
  for (const auto &item : enum_data)
  {
    std::println("Name: {}, Value: {}", item.name, static_cast<int>(item.value));
  }
  
  std::array<QString, enum_data.size()> enumNames;
  size_t index = 0;
  for( const auto &item :enum_data)
  {
    enumNames[index++] = QCoreApplication::tr(item.name.data());
  }

  for( const auto &name : enumNames)
  {
    qDebug() << "Translated Name:" << name;
  }


  return 0;
}
