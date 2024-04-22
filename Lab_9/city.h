#include <string>
#include <iostream>
using namespace std;

#pragma once
struct City {
    string cityName; // �������� ������
    string dateFoundation; // ���� ��������� ������
    int numberInhabitants; // ���-�� �������
    double square; // �������

     //�����������
    City(const string& Name, const string& date, int pop, double cityArea)
        : cityName(Name), dateFoundation(date), numberInhabitants(pop), square(cityArea) {}
    City(){}
};
