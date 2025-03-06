#pragma once

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#define FIELD_BUTTON_SIZE 50

#include "ui/item.h"
#include "second_window.h"

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>

#include <vector>

struct Item;

typedef std::vector<Item *>                                 IVector;
typedef std::vector<std::pair<int, int>>                    PVector;
typedef std::vector<std::vector<int>>                       IVVector;
typedef std::vector<std::vector<std::pair<int, int>>>       PVVector;

struct MainWindow : QMainWindow
{
    MainWindow(QWidget* parent, int size);
    ~MainWindow();

    static void         draw_path_on_map(PVector pair_vector);
    static void         draw_map(IVVector maze, int size);
    static void         show_initial_maze(IVVector maze, int size);
    static int          size_of_map;
    static IVector      map;
    static PVVector     solutions;
    static IVVector     map_2d;

private:
    SecondWindow*       second_window;
    static QWidget*     central_widget;


    void                generate_map(int size, IVVector& maze);
};

#endif // MAIN_WINDOW_H