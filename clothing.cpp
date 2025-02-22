#include "clothing.h"
#include "util.h"
#include <sstream>
#include <iomanip>

Clothing::Clothing(const std::string& category,
                   const std::string& name,
                   double price,
                   int qty,
                   const std::string& size,
                   const std::string& brand)
    : Product(category, name, price, qty),
      size_(size),
      brand_(brand)
{
}

std::set<std::string> Clothing::keywords() const
{
    std::set<std::string> nameKeys = parseStringToWords(name_);

    std::set<std::string> brandKeys = parseStringToWords(brand_);

    std::set<std::string> allKeys = setUnion(nameKeys, brandKeys);

    return allKeys;
}

std::string Clothing::displayString() const
{
    std::stringstream ss;
    ss << name_ << "\n"
       << "Size: " << size_ << "  "
       << "Brand: " << brand_ << "\n"
       << std::fixed << std::setprecision(2) << price_
       << " " << qty_ << " left.";
    return ss.str();
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n"
       << name_ << "\n"
       << price_ << "\n"
       << qty_ << "\n"
       << size_ << "\n"
       << brand_ << "\n";
}
