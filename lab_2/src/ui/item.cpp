#include "item.h"

#include <QString>
#include <QObject>
#include <QPalette>

#include <iostream>

Item::Item(QWidget* parent, Coords coords, int value, int index)
: QPushButton(parent), parent(parent), coords(coords), value(value), index(index)
{
    // set_value(value);

    if (value == 7) set_color(Color(128, 0, 128));
    if (value == 9) set_color(Color(0, 0, 255));
    if (value == 1) set_color(Color(0, 255, 0));
    if (value == 0) set_color(Color(255, 0, 0));

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

void Item::set_color(Color color)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Button, QColor(color.get_rgb()[0], color.get_rgb()[1], color.get_rgb()[2]));
    this->setPalette(palette);
    this->update();
}