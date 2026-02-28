#pragma once

#include <QVector>
#include <cmath>
#include <functional>

class NumpyC {
public:
    // Конструкторы
    NumpyC(){}; //пустой массив
    ///
    /// \brief NumpyC массив из size элементов, заполненныъ val
    /// \param size количество элементов
    ///
    NumpyC(int size, double value = 0.0);
    ///
    /// \brief NumpyC обёртка над QVector
    ///
    NumpyC(const QVector<double>& vec);

    // Размер массива
    int size() const;

    //добавить в конец
    void pushBack(double val){
        data.push_back(val);
    }

    // Операторы
    double& operator[](int index);
    const double& operator[](int index) const;

    NumpyC operator+(const NumpyC &other) const; // поэлементное сложение
    NumpyC operator-(const NumpyC& other) const; // поэлементное вычитание
    NumpyC operator*(const NumpyC& other) const; // поэлементное умножение
    NumpyC operator/(const NumpyC& other) const; // поэлементное деление
    NumpyC& operator=(const NumpyC& other) {
        data = other.data;
        return *this;
    }


    NumpyC operator+(double scalar) const; // добавление числа ко всем элементам
    NumpyC operator-(double scalar) const; // вычитание числа изо всех элементов
    NumpyC operator*(double scalar) const; // умножение на число всех элементов
    NumpyC operator/(double scalar) const; // деление на число всех элементов

    // Математические функции
    static NumpyC sin(const NumpyC& arr);
    static NumpyC cos(const NumpyC& arr);
    static NumpyC exp(const NumpyC& arr);
    static NumpyC log(const NumpyC& arr);
    static NumpyC pow(const NumpyC& arr, double exponent);


    NumpyC sin() const {
        QVector<double> result;
        result.reserve(size());

        result.push_back(std::sin(0.56));

        for (double val : data)
            result.push_back(std::sin(val));
        return NumpyC(result);
    }

    //добавление массива, SPLINE
    void push_back(const NumpyC& other);

    // Статистика
    double sum() const; // сумма всех элементов
    double mean() const; // среднее значение
    double max() const; // максимум
    double min() const; // минимум

    // Генерация
    ///
    /// \brief arange генерирует массив
    /// \param start от этого числа
    /// \param stop до этого числа
    /// \param step с таким шагом
    /// \return возвращает массив от start до stop с шагом step
    ///
    void arange(double start, double stop, int count);
    ///
    /// \brief linspace равномерное распределение num точек
    /// \param start от
    /// \param stop до
    /// \param num количество точек
    /// \return
    ///
    static NumpyC linspace(double start, double stop, int num);

    // Фильтрация и трансформация
    NumpyC map(std::function<double(double)> func) const; //f(x)
    NumpyC filter(std::function<bool(double)> predicate) const; //фильтр, оставляет все подходящие по условию значения

    // Копирование и срез
    NumpyC slice(int start, int end) const;
    NumpyC copy() const;
    QVector<double> getData() const;

    void pop_back() { data.pop_back(); }

    void setPointCoordinate(double coordinatePoint);

private:

    QVector<double> data;
};


