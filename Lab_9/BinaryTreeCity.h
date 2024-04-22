#include <iostream>
#include "city.h"
#include <vector>
#include <string>
using namespace std;
#pragma once
class BinaryTreeCity
{
private:
	struct TreeNode {
		City city;
		TreeNode* left; // ����� ���� (�������)
		TreeNode* right; // ������ ����

		// ����������� TreeNode
		TreeNode(const City& cityData) : city(cityData), left(nullptr), right(nullptr) {}
	};

	TreeNode* root;

	// ������ ��� ������� (�� ��������)
	void insert(TreeNode*& node, const City& city); // ��������� ���� � ������. ���� ���� ������, �� ��������� �����. ���� ���, �� ���������� ������� ������ �����, ����� ���������� � ����� ��������� ����� �������� ������ ���� (� ������ ����������)
	TreeNode* remove(TreeNode*& node, int numberInhabitants, double square); // ������� ���� �� ������. ���� ���� �� ������, �� �������� ��� ���� � ���������� ���� ��������� ��� �������� ���� (��� �������� ������ ��� ����� ����������)
	TreeNode* find(TreeNode* node, int numberInhabitants, double square) const; // ����� ���� ������ �� ��������� ������ ����������� ������� � �������
	//void inOrderTraversal(TreeNode* node, City* citiesArray, int& index) const; // ����� ������ � ������� ���������� � ����������� ������ citiesArray ��������. index ������������ ��� ������������ ������� �������
	void inOrderTraversal(TreeNode* node, vector<City>& citiesVector) const;
	void deleteTree(TreeNode*& node); // ����������� �������� ���� �����, ������� � node

	// TreeNode*& ������ �� ��������� ���� ������, ��������� ������ ��������� � ��������� �� ������ ����� ������� (����� �� ����������)
	// TreeNode* ��������� �� ���� ������ (��� ���������)

public:
	// ����������� � ���������� BinaryTreeCity
	BinaryTreeCity() : root(nullptr) {}
	~BinaryTreeCity();

	// ������ ��� ���������� ��������
	void addCity(const City& city); // ���������� ������ 
	void removeCity(int numberInhabitants, double square); // �������� ������ �� ��������� �������
	bool hasCity(int numberInhabitants, double square) const; // �������� ������� �������� � ������ �� ��������� ������
	//pair<City*, int> getAllCities() const; // ��������� ���� ��������. (��� ��������� ��������� �������)
	vector<City> getAllCities() const;

};

