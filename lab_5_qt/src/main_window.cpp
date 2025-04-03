#include "main_window.h"
#include "nn/neural.h"

#include <cmath>
#include <iostream>

#include <QFont>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) 
{
    central_widget = new QWidget(this);
    this->setCentralWidget(central_widget);
    this->setMinimumSize(1000, 600);
    this->setMaximumSize(1000, 600);
    this->setWindowTitle("Лабораторная работа 5");


    for (int i = 0, row = 1, column = 1; i < 28 * 28 ; ++i)
    {
        pixels.push_back(new Pixel(central_widget, {row, column}));
        pixels[i]->set_geometry(row * PIXEL_SIZE, column * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE);
        pixels[i]->set_color(Color(255, 255, 255));
        
        row++;

        if (row == sqrt(28 * 28) + 1)
        {
            row = 1;
            column++;
        }
    }


    neuro_result = new QLabel(central_widget);
    ok_button = new Button(central_widget, [ & ] () {click_ok_button();});
    clear_button = new Button(central_widget, [ & ] () {click_clear_button();});

    neuro_result->setGeometry(590, 20, 400, 440);
    ok_button->set_geometry(590, 530, 200, 50);
    clear_button->set_geometry(795, 530, 200, 50);

    ok_button->set_text("Начать");
    clear_button->set_text("Очистить");
    neuro_result->setText("Здесь будет результат");
    neuro_result->setFont(QFont("Arial", 25));
    neuro_result->setAlignment(Qt::AlignCenter);

}

void MainWindow::click_ok_button()
{
    std::vector<int> pixels_ints(28*28);

    for (int i = 0; i < pixels.size() ; ++i)
    {
        if (pixels[i]->get_color() == Color(255, 255, 255))
        {
            pixels_ints[i] = 0;
        }
        if (pixels[i]->get_color() == Color(0, 0, 0))
        {
            pixels_ints[i] = 1;
        }
    }

    std::vector<std::vector<int>> pixels_ints_2d = convert_to_2d(pixels_ints);


    #ifdef WITH_LOG
    for (const auto& row : pixels_ints_2d) 
    {
        for (const auto& elem : row)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Предсказанная цифра: " << run_neuro_model(pixels_ints_2d) << std::endl;
    #endif //WITH_LOG

    neuro_result->setFont(QFont("Arial", 250));
    neuro_result->setText(QString::number(run_neuro_model(pixels_ints_2d)));
}

void MainWindow::click_clear_button()
{
    for (int i = 0; i < pixels.size() ; ++i)
    {
        pixels[i]->set_color(Color(255, 255, 255));
    }
    
    neuro_result->setFont(QFont("Arial", 25));
    neuro_result->setText("Здесь будет результат");
}

std::vector<std::vector<int>> MainWindow::convert_to_2d(const std::vector<int>& input)
{
    const int rows = 28;
    const int cols = 28;
    
    if (input.size() != rows * cols) 
    {
        throw std::invalid_argument("Input vector must have exactly 784 elements.");
    }

    std::vector<std::vector<int>> output(rows, std::vector<int>(cols));

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            output[i][j] = input[i * cols + j];
        }
    }

    return output;
}

int MainWindow::run_neuro_model(std::vector<std::vector<int>> vector)
{
    Mat digit_image = Neural::vector_to_mat(vector);

    // namedWindow("Цифра", WINDOW_NORMAL);
    // imshow("Цифра", digit_image);
    // waitKey(0);

    Ptr<ANN_MLP> neuralNet = ANN_MLP::load("../src/nn/model/trained_model/neuro_model.xml");

    if (neuralNet.empty()) 
    {
        cerr << "Ошибка: не удалось загрузить модель improved_mnist_model.xml!" << endl;
        return -1;
    }

    Mat inputFlattened = Neural::preprocess_image(digit_image);

    Mat result;
    neuralNet->predict(inputFlattened, result);

    Point maxLoc;
    minMaxLoc(result, nullptr, nullptr, nullptr, &maxLoc);
    return maxLoc.x;
}