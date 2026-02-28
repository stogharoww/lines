#include "numpyc.h"
#include <QDebug>
#include <QtMath>


NumpyC::NumpyC(int size, double value)
{
    for (int i = 0; i < size; i++){
        data.append(value);
    }
}
NumpyC::NumpyC(const QVector<double> &vec)
{
    data = vec;
}

int NumpyC::size() const
{
    return data.size();
}

double &NumpyC::operator[](int index)
{
    return data[index];
}
const double& NumpyC::operator[](int index) const {
    return data[index];
}


QVector<double> NumpyC::getData() const
{
    return data;
}

// массив + массив
NumpyC NumpyC::operator+(const NumpyC &other) const
{
    QVector<double> result;
    int n = qMin(this->size(), other.size());
    result.reserve(qMax(this->size(), other.size()));
    for (int i = 0; i < n; i++) {
        result.push_back((*this)[i] + other[i]);
    }
    if (this->size() > other.size()) {
        for (int i = n; i < this->size(); i++)
            result.push_back((*this)[i]);
    } else if (other.size() > this->size()) {
        for (int i = n; i < other.size(); i++)
            result.push_back(other[i]);
    }

    return NumpyC(result);
}



NumpyC NumpyC::operator-(const NumpyC &other) const
{
    QVector<double> result;
    result.reserve(qMax(this->size(), other.size()));
    int n = qMin(this->size(), other.size());
    for (int i = 0; i < n; i++) {
        result.push_back((*this)[i] - other[i]);
    }
    if (this->size() > other.size()) {
        for (int i = n; i < this->size(); i++)
            result.push_back((*this)[i]);
    } else if (other.size() > this->size()) {
        for (int i = n; i < other.size(); i++)
            result.push_back(-other[i]);
    }

    return NumpyC(result);
}
NumpyC NumpyC::operator*(const NumpyC &other) const {
    QVector<double> result;
    int n = qMin(this->size(), other.size());
    result.reserve(qMax(this->size(), other.size()));

    for (int i = 0; i < n; i++) {
        result.push_back((*this)[i] * other[i]);
    }

    if (this->size() > other.size()) {
        for (int i = n; i < this->size(); i++)
            result.push_back((*this)[i]);
    } else if (other.size() > this->size()) {
        for (int i = n; i < other.size(); i++)
            result.push_back(other[i]);
    }

    return NumpyC(result);
}
NumpyC NumpyC::operator/(const NumpyC &other) const {
    QVector<double> result;
    int n = qMin(this->size(), other.size());
    result.reserve(qMax(this->size(), other.size()));

    for (int i = 0; i < n; i++) {
        double divisor = other[i];
        result.push_back(divisor != 0.0 ? (*this)[i] / divisor : 0.0); // защита от деления на 0
    }

    if (this->size() > other.size()) {
        for (int i = n; i < this->size(); i++)
            result.push_back((*this)[i]);
    } else if (other.size() > this->size()) {
        for (int i = n; i < other.size(); i++)
            result.push_back(0.0); // деление 0 / x → 0
    }

    return NumpyC(result);
}

// стандартные функции
NumpyC NumpyC::sin(const NumpyC &arr)
{
    QVector<double> result;
    int size = arr.size();
    result.reserve(size);
    for (int i = 0; i < size; i++){
        result.push_back(std::sin(arr[i]));
    }
    qDebug() << "SIN DEBUG size: " << result.size();
    return NumpyC(result);
}
NumpyC NumpyC::cos(const NumpyC &arr)
{
    QVector<double> result;
    int size = arr.size();
    result.reserve(size);
    for (int i = 0; i < size; i++){
        result.push_back(qCos(arr[i]));
    }
    return NumpyC(result);
}
NumpyC NumpyC::exp(const NumpyC &arr)
{
    QVector<double> result;
    int size = arr.size();
    result.reserve(size);
    for (int i = 0; i < size; i++){
        result.push_back(qExp(arr[i]));
    }
    return NumpyC(result);
}
NumpyC NumpyC::log(const NumpyC &arr)
{
    QVector<double> result;
    int size = arr.size();
    result.reserve(size);
    for (int i = 0; i < size; i++){
        result.push_back(qLn(arr[i]));
    }
    return NumpyC(result);
}
NumpyC NumpyC::pow(const NumpyC &arr, double exponent)
{
    QVector<double> result;
    int size = arr.size();
    result.reserve(size);
    for (int i = 0; i < size; i++){
        result.push_back(qPow(arr[i], exponent));
    }
    return NumpyC(result);
}

void NumpyC::push_back(const NumpyC &other)
{
    for (int i = 0; i < other.size(); i++){
        data.push_back(other[i]);
    }

}

// статистика
double NumpyC::sum() const
{
    double result = 0;
    int size = this->size();
    for (int i = 0; i < size; i++){
        result += (*this)[i];
    }
    return result;
}
double NumpyC::mean() const
{
    double result = 0;
    int size = this->size();
    for (int i = 0; i < size; i++){
        result += (*this)[i];
    }
    result /= size;
    return result;
}
double NumpyC::max() const
{
    double result = 0;
    const QVector<double>& vec = getData();
    auto it = std::max_element(vec.begin(), vec.end());
    if (it != vec.end()){
        result = *it;
    }
    return result;
}
double NumpyC::min() const
{
    double result = 0;
    const QVector<double>& vec = getData();
    auto it = std::min_element(vec.begin(), vec.end());
    if (it != vec.end()){
        result = *it;
    }
    return result;
}

// генераторы
void NumpyC::arange(double start, double stop, int count) {
    data.clear();
    if (count <= 1) return;

    double step = (stop - start) / (count - 1);
    data.reserve(count);

    for (int i = 0; i < count; ++i) {
        data.push_back(start + i * step);
    }
}

NumpyC NumpyC::linspace(double start, double stop, int num)
{
    QVector<double> result;
    result.reserve(num);
    if (num > 2){
        double step = (stop - start) / (num - 1);
        for (int i = 0; i < num; ++i) {
            result.push_back(start + i * step);
        }
    }
    else if (num == 2)
        result = {start, stop};
    else if (num == 1)
        result = {start};
    else if (num == 0)
        result = {};

    return NumpyC(result);
}

void NumpyC::setPointCoordinate(double coordinatePoint)
{
    data.push_back(coordinatePoint);
}

// функции и фильтр
NumpyC NumpyC::map(std::function<double (double)> func) const
{
    QVector<double> result;
    int size = this->size();
    result.reserve(size);
    for (int i = 0; i < size; i++){
        result.push_back(func((*this)[i]));
    }
    return NumpyC(result);
}
NumpyC NumpyC::filter(std::function<bool (double)> predicate) const
{
    QVector<double> result;
    for (double val : getData()){
        if (predicate(val))
            result.push_back(val);
    }
    return NumpyC(result);
}

//срез и копирование
NumpyC NumpyC::slice(int start, int end) const
{
    QVector<double> result;
    int size = end - start;
    result.reserve(size);
    for (int i = start; i < end; i++)
        result.push_back((*this)[i]);
    return NumpyC(result);
}
NumpyC NumpyC::copy() const
{
    return NumpyC(this->getData());
}

// элемент + число
NumpyC NumpyC::operator+(double scalar) const{
    QVector<double> result;
    int size = this->size();
    result.reserve(size); // ускорение push_back
    for (int i = 0; i < size; i++){
        double sum = scalar + (*this)[i];
        result.push_back(sum);
    }
    return NumpyC(result);
}
NumpyC NumpyC::operator-(double scalar) const{
    QVector<double> result;
    int size = this->size();
    result.reserve(size);
    for (int i = 0; i < size; i++){
        double sum = (*this)[i] - scalar;
        result.push_back(sum);
    }
    return NumpyC(result);
}
NumpyC NumpyC::operator*(double scalar) const{
    QVector<double> result;
    int size = this->size();
    result.reserve(size);
    for (int i = 0; i < size; i++){
        double sum = (*this)[i] * scalar;
        result.push_back(sum);
    }
    return NumpyC(result);
}
NumpyC NumpyC::operator/(double scalar) const{
    QVector<double> result;
    if (scalar == 0){
        qDebug() << "ERR: деление на 0";
        return *this;
    }
    int size = this->size();
    result.reserve(size);
    for (int i = 0; i < size; i++){
        double sum = (*this)[i] / scalar;
        result.push_back(sum);
    }
    return NumpyC(result);
}
