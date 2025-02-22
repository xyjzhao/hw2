#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>

Movie::Movie(const std::string& category,
             const std::string& name,
             double price,
             int qty,
             const std::string& genre,
             const std::string& rating)
    : Product(category, name, price, qty),
      genre_(genre),
      rating_(rating)
{
}

std::set<std::string> Movie::keywords() const
{
    std::set<std::string> nameKeys = parseStringToWords(name_);

    nameKeys.insert(convToLower(genre_));

    return nameKeys;
}

std::string Movie::displayString() const
{
    std::stringstream ss;
    ss << name_ << "\n"
       << "Genre: " << genre_ << "  "
       << "Rating: " << rating_ << "\n"
       << std::fixed << std::setprecision(2) << price_
       << " " << qty_ << " left.";
    return ss.str();
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n"
       << name_ << "\n"
       << price_ << "\n"
       << qty_ << "\n"
       << genre_ << "\n"
       << rating_ << "\n";
}
