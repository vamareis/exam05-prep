#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() : tree_bag() {}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& other) : tree_bag(other) {}

searchable_tree_bag&    searchable_tree_bag::operator=(const searchable_tree_bag& other)
{
    tree_bag::operator=(other);
    return (*this);
}

searchable_tree_bag::~searchable_tree_bag() {}

bool    searchable_tree_bag::has(int value) const
{
    return (search_node(value, this->tree));
}

bool    searchable_tree_bag::search_node(int value, node *n) const
{
    if (!n)
        return (false);
    if (value == n->value)
        return (true);
    if (value < n->value)
        return (search_node(value, n->l));
    return (search_node(value, n->r));
}