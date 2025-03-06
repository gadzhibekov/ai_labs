#include "main_window.h"
#include "game.h"
#include "ui/color.h"
#include "log/log.h"

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

IVector         MainWindow::map;
PVVector        MainWindow::solutions;
IVVector        MainWindow::map_2d;
QWidget*        MainWindow::central_widget;
int             MainWindow::size_of_map;

MainWindow::MainWindow(QWidget* parent, int size) : QMainWindow(parent)
{
    srand(time(0));
    
    central_widget = new QWidget(this);
    this->setCentralWidget(central_widget);
    this->setMinimumSize(FIELD_BUTTON_SIZE * (size + 2), FIELD_BUTTON_SIZE * (size + 2));
    this->setMaximumSize(FIELD_BUTTON_SIZE * (size + 2), FIELD_BUTTON_SIZE * (size + 2));
    this->setWindowTitle("Лабораторная работа 2");

    MainWindow::size_of_map = size;

    IVVector maze(size, vector<int>(size));

    generate_map(size, maze);
    MainWindow::map_2d = maze;
    solutions = Game::find_all_paths(maze, size);


    std::vector<int> pathes_size;
    for (auto path : solutions)
    {
        pathes_size.push_back(path.size());
    }

    auto min_it = std::min_element(pathes_size.begin(), pathes_size.end());
    PVector short_path;

    for (auto vector_pair : solutions)
    {
        if (vector_pair.size() == *min_it)
        {
            short_path = vector_pair;
            break;
        }
    }

    draw_path_on_map(short_path);

#ifdef WITH_LOG
    std::cout << "Общее количество решений: " << solutions.size() << std::endl;

    if (solutions.size() != 0)
    {
        std::cout << "Самое короткое решение: "   << *min_it << std::endl;
    }
#endif // WITH_LOG


    if (solutions.size() != 0)
    {
        second_window = new SecondWindow(1, solutions.size(), *min_it);
    }
    else
    {
        second_window = new SecondWindow(0, 0, 0);
    }

    second_window->show();
}

MainWindow::~MainWindow()
{
    delete second_window;
}

void MainWindow::draw_path_on_map(PVector pair_vector)
{
    std::vector<int> result;

    for (int i = 0; i < map.size(); ++i)
    {
        for (int j = 0; j < pair_vector.size(); ++j)
        {
            if ((pair_vector[j].first + 1 == map[i]->get_coords().second && pair_vector[j].second + 1 == map[i]->get_coords().first))
            {
                result.push_back(map[i]->get_index());
            }

            // map[i]->clear();
            map[i]->set_color(Color(255, 255, 255));
        }
    }

    for (int i = 0; i < result.size(); ++i)
    {
        for (int j = 0; j < map.size(); ++j)
        {
            if (map[j]->get_index() == result[i])
            {
                // map[j]->show_value();

                if (map[j]->get_value() == 7) map[j]->set_color(Color(128, 0, 128));
                if (map[j]->get_value() == 9) map[j]->set_color(Color(0, 0, 255));
                if (map[j]->get_value() == 1) map[j]->set_color(Color(0, 255, 0));
                if (map[j]->get_value() == 0) map[j]->set_color(Color(255, 0, 0));
            }
        }
    }
}

void MainWindow::generate_map(int size, IVVector& maze)
{
    Game::generate_map(maze, size);
    MainWindow::draw_map(maze, size);

#ifdef WITH_LOG
    Game::print_map(maze);
#endif // WITH_LOG
}

void MainWindow::draw_map(IVVector maze, int size)
{
    map.clear();
    std::vector<int> flat_vector;

    for (const auto& inner_vec : maze) 
    {
        flat_vector.insert(flat_vector.end(), inner_vec.begin(), inner_vec.end());
    }

    for (int i = 0, row = 1, column = 1; i < flat_vector.size(); ++i)
    {   
        map.push_back(new Item(central_widget, {row, column}, flat_vector[i], i + 1));
        map[i]->setGeometry(row * FIELD_BUTTON_SIZE, column * FIELD_BUTTON_SIZE, FIELD_BUTTON_SIZE, FIELD_BUTTON_SIZE);

        row++;

        if (row == size + 1)
        {
            row = 1;
            column++;
        }
    }
}

void MainWindow::show_initial_maze(IVVector maze, int size)
{
    std::vector<int> flat_vector;

    for (const auto& inner_vec : maze) 
    {
        flat_vector.insert(flat_vector.end(), inner_vec.begin(), inner_vec.end());
    }

    for (int i = 0; i < flat_vector.size(); ++i)
    {
        // map[i]->set_value(flat_vector[i]);

        if (flat_vector[i] == 7) map[i]->set_color(Color(128, 0, 128));
        if (flat_vector[i] == 9) map[i]->set_color(Color(0, 0, 255));
        if (flat_vector[i] == 1) map[i]->set_color(Color(0, 255, 0));
        if (flat_vector[i] == 0) map[i]->set_color(Color(255, 0, 0));
    }
}