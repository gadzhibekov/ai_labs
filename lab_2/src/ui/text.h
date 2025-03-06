#pragma once

#ifndef TEXT_H
#define TEXT_H

#include <QLabel>
#include <QString>
#include <QWidget>

struct Text : QLabel
{
    Text(QString text, QWidget* parent);
    ~Text();

    void    set_text(QString text);
    QString get_text();
    
private:
    QString text;
};

#endif // TEXT_H