#include "text.h"

Text::Text(QString text, QWidget* parent) : QLabel(parent)
{
    set_text(text);
}

Text::~Text()
{
    ;
}

void Text::set_text(QString text)
{
    this->setText(text);
}

QString Text::get_text()
{
    return text;
}