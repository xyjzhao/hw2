#include "book.h"
#include "util.h"
#include <sstream>
#include <iomanip>

Book::Book(const std::string& category,
           const std::string& name,
           double price,
           int qty,
           const std::string& isbn,
           const std::string& author)
    : Product(category, name, price, qty),
      isbn_(isbn),
      author_(author)
{
}

std::set<std::string> Book::keywords() const
{
    std::set<std::string> keys;
    std::set<std::string> nameKeys = parseStringToWords(name_);
    std::set<std::string> authorKeys = parseStringToWords(author_);

    keys = setUnion(nameKeys, authorKeys);

    keys.insert(convToLower(isbn_));

    return keys;
}

std::string Book::displayString() const
{
    std::stringstream ss;
    ss << name_ << "\n"
       << "Author: " << author_ << "  "
       << "ISBN: " << isbn_ << "\n"
       << std::fixed << std::setprecision(2) << price_ 
       << " " << qty_ << " left.";
    return ss.str();
}

void Book::dump(std::ostream& os) const
{
    os << category_ << "\n"
       << name_ << "\n"
       << price_ << "\n"
       << qty_ << "\n"
       << isbn_ << "\n"
       << author_ << "\n";
}
