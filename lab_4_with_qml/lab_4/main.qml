import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window
{
    width: 640
    height: 480
    visible: true
    title: qsTr("Экспертная система")

    property var questions:
    [
        {
            "question": "Какой парадигме программирования следует этот язык?",
            "answers": ["Объектно-ориентированное", "Процедурное", "Функциональное", "Логическое", "Мультипарадигменное"],
            "value_of_answers": ["Java", "C", "Scala", "Prolog", "Python"]
        },
        {
            "question": "Является ли язык строго- или слабо типизированным?",
            "answers": ["Строго типизированный", "Слабо типизированный"],
            "value_of_answers": ["C++", "Python"]
        },
        {
            "question": "Какая система типов используется в языке?",
            "answers": ["Динамическая", "Статическая"],
            "value_of_answers": ["Ruby", "C++"]
        }
    ]

    property int    currentQuestionIndex:   0
    property int    selectedAnswerIndex:    -1          // Индекс выбранного ответа
    property var    selectedAnswers:        []          // Массив для хранения выбранных ответов
    property string mostFrequentElement:    ""          // Самый часто встречающийся элемент
    property bool   isSurveyCompleted:      false       // Флаг завершения опроса

    Column
    {
        anchors.centerIn: parent
        spacing: 20

        Text
        {
            id: questionText
            text: isSurveyCompleted ? "Опрос завершен" : questions[currentQuestionIndex].question
            font.pixelSize: 24
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Column
        {
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter
            visible: !isSurveyCompleted

            Repeater
            {
                model: questions[currentQuestionIndex].answers.length
                Row
                {
                    spacing: 10
                    RadioButton
                    {
                        id: radioButton
                        checked: index === selectedAnswerIndex
                        onClicked: selectedAnswerIndex = index
                    }

                    Text
                    {
                        text: questions[currentQuestionIndex].answers[index]
                        font.pixelSize: 18
                        anchors.verticalCenter: radioButton.verticalCenter
                    }
                }
            }
        }

        Row {
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter

            Button
            {
                text: "Начать заново"
                width: 100
                height: 50

                onClicked:
                {
                    currentQuestionIndex = 0
                    selectedAnswerIndex = -1
                    selectedAnswers = []
                    mostFrequentElement = ""
                    isSurveyCompleted = false
                }
            }

            Button
            {
                text: "Назад"
                width: 100
                height: 50
                onClicked:
                {
                    if (currentQuestionIndex > 0)
                    {
                        selectedAnswers.pop()
                        currentQuestionIndex--
                        selectedAnswerIndex = -1
                    }
                    else
                    {
                        console.log("Это первый вопрос")
                    }
                }
            }

            Button {
                text: "Далее"
                width: 100
                height: 50
                onClicked:
                {
                    if (isSurveyCompleted)
                    {
                        console.log("Опрос завершен")
                    }
                    else
                    {
                        if (selectedAnswerIndex !== -1)
                        {
                            var selectedValue = questions[currentQuestionIndex].value_of_answers[selectedAnswerIndex]
                            selectedAnswers.push(selectedValue)
                        }

                        if (currentQuestionIndex < questions.length - 1)
                        {
                            currentQuestionIndex++
                            selectedAnswerIndex = -1
                        }
                        else
                        {
                            // Анализ массива выбранных ответов
                            mostFrequentElement = findMostFrequent(selectedAnswers)
                            console.log("Ваш выбор:", mostFrequentElement)
                            console.log("Все выбранные ответы:", selectedAnswers)
                            isSurveyCompleted = true
                        }
                    }
                }
            }

            Button
            {
                text: "Выход"
                width: 100
                height: 50
                onClicked: Qt.quit()
            }
        }

        // Текст для отображения самого частого элемента
        Text
        {
            id: resultText
            text: mostFrequentElement ? "Ваш выбор: " + mostFrequentElement : ""
            font.pixelSize: 18
            anchors.horizontalCenter: parent.horizontalCenter
            visible: isSurveyCompleted
        }
    }

    function findMostFrequent(array)
    {
        var counts = {}
        var maxCount = 0
        var mostFrequentElement = null

        for (var i = 0; i < array.length; i++)
        {
            var element = array[i]
            if (counts[element])
            {
                counts[element]++
            }
            else
            {
                counts[element] = 1
            }

            if (counts[element] > maxCount)
            {
                maxCount = counts[element]
                mostFrequentElement = element
            }
        }

        return mostFrequentElement
    }
}
