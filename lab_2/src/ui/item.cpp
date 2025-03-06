#include "item.h"

#include <QString>
#include <QObject>

#include <iostream>

Item::Item(QWidget* parent, Coords coords, int value, int index)
: QPushButton(parent), parent(parent), coords(coords), value(value), index(index)
{
    set_value(value);
    QObject::connect(this, &Item::clicked, this, &Item::click_slot);
}

Item::~Item()
{
    ;
}

void Item::click_slot()
{
#ifdef WITH_LOG
    std::cout << "Пара: (" << coords.first << ", " << coords.second << ")" << std::endl;
    std::cout << "Значение: " << value << std::endl;
    std::cout << "Индекс: " << index << std::endl;
    std::cout << std::endl;
#endif // WITH_LOG
}

void Item::clear()
{
    this->setText("");
}

void Item::show_value()
{
    this->setText(QString::number(value));
}

void Item::set_value(int value)
{
    this->value = value;

    this->setText(QString::number(value));
}

void Item::set_coords(Coords coords)
{
    this->coords = coords;
}

void Item::set_index(int index)
{
    this->index = index;
}