#include <string>
#include <iostream>
using namespace std;

#pragma once
struct City {
    string cityName; // название города
    string dateFoundation; // дата основания города
    int numberInhabitants; // кол-во жителей
    double square; // площадь

     //Конструктор
    City(const string& Name, const string& date, int pop, double cityArea)
        : cityName(Name), dateFoundation(date), numberInhabitants(pop), square(cityArea) {}
    City(){}
};
