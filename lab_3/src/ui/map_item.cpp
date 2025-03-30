#include "map_item.h"

MapItem::MapItem(QWidget* parent, int id, std::pair<int, int> pair) 
: Button(parent), id(id), pair(pair)
{
    ;
}