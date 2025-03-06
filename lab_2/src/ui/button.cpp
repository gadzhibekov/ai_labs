#include "button.h"

#include <QObject>

Button::Button(std::function<void()> slot, QWidget* parent, QString text) : QPushButton(parent), parent(parent), slot(slot)
{
    set_text(text);
    QObject::connect(this, &Button::clicked, this, &Button::click_slot);
}

Button::~Button()
{
    ;
}

void Button::click_slot()
{
    slot();
}

void Button::set_text(QString text)
{
    this->setText(text);
}