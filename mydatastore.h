#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <map>
#include <set>
#include <vector>
#include <string>
#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"  
class MyDataStore : public DataStore {
public:
    MyDataStore();
    virtual ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p) override;

    /**
     * Adds a user to the data store
     */
    void addUser(User* u) override;

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) 
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile) override;

    /**
     * Adds the product (from hits vector) at position hitIndex (1-based)
     *  to the user's cart (case-insensitive username). 
     * Returns true if successful, false if invalid user or out-of-range hitIndex.
     */
    bool addToCart(const std::string& username, 
                   const std::vector<Product*>& hits, 
                   int hitIndex);

    /**
     * Displays items in the given user’s cart (case-insensitive).
     * Prints "Invalid username" if user doesn’t exist.
     */
    void viewCart(const std::string& username) const;

    /**
     * Buys as many items in the user’s cart (in FIFO order) as possible 
     * (i.e. if enough stock and the user has enough balance).
     * Remaining items remain in the cart.
     */
    void buyCart(const std::string& username);

private:
    // Users keyed by lowercase username
    std::map<std::string, User*> users_;

    // Keep a list of all products (for dumping at the end)
    std::vector<Product*> products_;

    // Keyword map: each keyword maps to the set of products that have it
    std::map<std::string, std::set<Product*>> keywordMap_;

    // Carts keyed by lowercase username
    // Each cart is a FIFO list (vector) of Product* 
    std::map<std::string, std::vector<Product*>> carts_;
};

#endif
