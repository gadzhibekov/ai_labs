#ifndef DATA_H
#define DATA_H

#include <vector>
#include <utility>
#include <string>

std::vector<std::pair<std::string, std::pair<std::vector<std::string>, std::vector<std::string>>>> items_vector = 
{
    {"Какой парадигме программирования следует этот язык ?", {{"Объектно-ориентированное", "Процедурное", "Функциональное", "Логическое", "Мультипарадигменное"}, {"Java", "C", "Scala", "Prolog", "Python"}}},
    {"Является ли язык строго- или слабо типизированным ?", {{"Строго типизированный", "Слабо типизированный"}, {"C++", "Python", "JavaScript"}}},
    {"Какая система типов используется в языке ?", {{"Динамическая", "Статическая"}, {"Ruby", "C++"}}},
    // {"Для каких задач чаще всего применяется этот язык ?", {{"Веб-разработка", "Системное программирование", "Игровая разработка", "Машинное обучение", "Анализ данных"}, {"PHP", "C", "C#", "Python", "R"}}},
    // {"Какие операционные системы или платформы поддерживаются этим языком ?", {{"Windows", "Linux", "macOS", "Мультиплатформенный"}, {"C#", "C", "Swift", "Java"}}},
    // {"Насколько широко используется этот язык в индустрии ?", {{"Высоко", "Средне", "Низко"}, {"JavaScript", "Go", "Erlang"}}},
    // {"Какие известные проекты/программы написаны на этом языке ?", {{"Linux Kernel", "YouTube", "Instagram", "Unreal Engine", "Microsoft Office"}, {"C", "Python", "Python", "C++", "C#"}}},
    // {"Какова доступность документации и обучающих материалов для этого языка ?", {{"Отличная", "Хорошая", "Средняя", "Плохая"}, {"Python", "Ruby", "Scala", "Assembly"}}},
    // {"Как язык показывает себя с точки зрения производительности ?", {{"Высокая", "Средняя", "Низкая"}, {"C++", "Python", "PHP"}}},
    // {"Каковы ограничения производительности этого языка ?", {{"Потребление памяти", "Медленная скорость исполнения", "Ограничения интерпретации"}, {"C#", "Python", "Ruby"}}},
    // {"Насколько лёгок в изучении синтаксис этого языка ?", {{"Лёгкий", "Средний", "Сложный"}, {"Python", "Java", "C++"}}},
    // {"Какие особенности синтаксиса делают его уникальным ?", {{"Простота", "Читаемость кода", "Подходит для новичков", "Сложен для восприятия"}, {"Python", "Ruby", "Scratch", "C++"}}},
    // {"Какие преимущества предлагает этот язык для параллельного/многопоточного программирования ?", {{"Эффективная многопоточность", "Лимитированная поддержка потоков", "Сложная настройка потоков"}, {"Java", "Python", "C++"}}},
    // {"Есть ли у языка встроенные возможности для работы с сетью ?", {{"Есть (встроенные модули)", "Только с использованием сторонних библиотек"}, {"Go", "C++"}}},
    // {"Какие механизмы управления памятью используются в этом языке ?", {{"Ручное управление", "Сборщик мусора", "Управляется компилятором", "Ограниченная работа с памятью"}, {"C++", "Python", "Rust", "Assembly"}}},
    // {"Как активно развивается этот язык ?", {{"Часто создаются обновления", "Редкие обновления", "Считается устаревшим"}, {"Swift", "Perl", "COBOL"}}},
    // {"Какие уникальные возможности предлагает этот язык ?", {{"Безопасность памяти", "Высокая производительность", "Простота интеграции с другими языками"}, {"Rust", "Go", "Python"}}}
};

#endif // DATA_H