#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QString>

#include <functional>

struct Button : QPushButton
{
    Button(std::function<void()> slot, QWidget* parent, QString text);
    ~Button();

private:
    QWidget*                parent;

    void                    click_slot();
    void                    set_text(QString text);
    std::function<void()>   slot;
};

#endif // BUTTON_H