#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "ui/pixel.h"
#include "ui/button.h"

#include <QMainWindow>
#include <QWidget>
#include <QLabel>

#include <vector>


struct MainWindow : QMainWindow
{
    MainWindow(QWidget* parent);
    ~MainWindow() = default;


private:
    QWidget*                                central_widget;
    Button*                                 ok_button;
    Button*                                 clear_button;
    QLabel*                                 neuro_result;
    std::vector<Pixel *>                    pixels;

    void                                    click_ok_button();
    void                                    click_clear_button();
    int                                     run_neuro_model(std::vector<std::vector<int>> vector);
    std::vector<std::vector<int>>           convert_to_2d(const std::vector<int>& input);
};

#endif // MAIN_WINDOW_H