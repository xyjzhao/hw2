#include "mydatastore.h"
#include <iostream>
#include <sstream>

MyDataStore::MyDataStore()
{
}

MyDataStore::~MyDataStore()
{
    // Delete products
    for(Product* p : products_) {
        delete p;
    }
    // Delete users
    for(auto& u : users_) {
        delete u.second;
    }
}


void MyDataStore::addProduct(Product* p)
{
    products_.push_back(p);

    std::set<std::string> keys = p->keywords();

    for(const auto& k : keys) {
        std::string lowerKey = convToLower(k);
        keywordMap_[lowerKey].insert(p);
    }
}

void MyDataStore::addUser(User* u)
{
    std::string uname = convToLower(u->getName());

    users_[uname] = u;

    carts_[uname] = std::vector<Product*>();
}


std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    for(auto& t : terms) {
        t = convToLower(t);
    }

    std::set<Product*> resultSet;

    if(terms.empty()) {
        return {};
    }

    if(type == 0) { 
        resultSet = keywordMap_[terms[0]];
        for(size_t i = 1; i < terms.size(); i++) {
            std::set<Product*> temp = keywordMap_[terms[i]];
            resultSet = setIntersection(resultSet, temp);
        }
    }
    else {
        for(const auto& term : terms) {
            std::set<Product*> temp = keywordMap_[term];
            resultSet = setUnion(resultSet, temp);
        }
    }
    std::vector<Product*> results(resultSet.begin(), resultSet.end());
    return results;
}

void MyDataStore::dump(std::ostream& ofile)
{
    // Products
    ofile << "<products>" << std::endl;
    for(Product* p : products_) {
        p->dump(ofile);
    }
    ofile << "</products>" << std::endl;

    // dump
    ofile << "<users>" << std::endl;
    for(std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it)
    {
        User* u = it->second;
        u->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}


// OPTIONAL EXTRA METHODS

bool MyDataStore::addToCart(const std::string& username, 
                            const std::vector<Product*>& hits, 
                            int hitIndex)
{
    std::string uname = convToLower(username);

    if(users_.find(uname) == users_.end()) {
        return false;
    }

    if(hitIndex < 1 || hitIndex > (int)hits.size()) {
        return false;
    }

    Product* toAdd = hits[hitIndex - 1]; 
    carts_[uname].push_back(toAdd);

    return true;
}

void MyDataStore::viewCart(const std::string& username) const
{
    std::string uname = convToLower(username);

    auto it = users_.find(uname);
    if(it == users_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    auto cartIt = carts_.find(uname);
    if(cartIt == carts_.end()) {
        std::cout << "Cart is empty!" << std::endl;
        return;
    }

    const std::vector<Product*>& cart = cartIt->second;
    if(cart.empty()) {
        std::cout << "Cart is empty!" << std::endl;
        return;
    }

    for(size_t i = 0; i < cart.size(); i++) {
        std::cout << "Item " << (i + 1) << std::endl;
        std::cout << cart[i]->displayString() << std::endl;
        std::cout << std::endl;
    }
}

void MyDataStore::buyCart(const std::string& username)
{
    std::string uname = convToLower(username);

    auto userIt = users_.find(uname);
    if(userIt == users_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    User* u = userIt->second;

    auto cartIt = carts_.find(uname);
    if(cartIt == carts_.end()) {
        return;
    }

    std::vector<Product*>& cart = cartIt->second;
    size_t i = 0;
    while(i < cart.size()) {
        Product* p = cart[i];
        if(p->getQty() > 0 && u->getBalance() >= p->getPrice()) {
            p->subtractQty(1);
            u->deductAmount(p->getPrice());
            cart.erase(cart.begin() + i);
        }
        else {
            i++;
        }
    }
}
