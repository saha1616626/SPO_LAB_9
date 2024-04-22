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
		TreeNode* left; // левый узел (потомок)
		TreeNode* right; // правый узел

		// конструктор TreeNode
		TreeNode(const City& cityData) : city(cityData), left(nullptr), right(nullptr) {}
	};

	TreeNode* root;

	// методы над деревом (не основные)
	void insert(TreeNode*& node, const City& city); // добавляет узел в дерево. есле узел пустой, то создается новый. если нет, то рекурсивно вызвает данный метод, чтобы определить в каком поддереве стоит вставить данный узел (с учетом сортировки)
	TreeNode* remove(TreeNode*& node, int numberInhabitants, double square); // удаляет узел из дерева. если узел не найден, то вызывает сам себя и рекурсивно ищет поддерево для удаления узла (или заменить правым или левым поддеревом)
	TreeNode* find(TreeNode* node, int numberInhabitants, double square) const; // поиск узла дерева по сочетанию свойст количеством жителей и площади
	//void inOrderTraversal(TreeNode* node, City* citiesArray, int& index) const; // обход дерева в порядки сортировки и заполняется массив citiesArray городами. index используется для отслеживания текущей позиции
	void inOrderTraversal(TreeNode* node, vector<City>& citiesVector) const;
	void deleteTree(TreeNode*& node); // рекурсивное удаление всех узлов, начиная с node

	// TreeNode*& ссылка на указатель узла дерева, позволяет внести изменения в указатель по ссылке внтри функции (после ее завершения)
	// TreeNode* указатель на узел дерева (для просмотра)

public:
	// конструктор и деструктор BinaryTreeCity
	BinaryTreeCity() : root(nullptr) {}
	~BinaryTreeCity();

	// методы для выполнения операции
	void addCity(const City& city); // добавление города 
	void removeCity(int numberInhabitants, double square); // удаление города по сочетанию свойств
	bool hasCity(int numberInhabitants, double square) const; // проверка наличия элемента в списке по сочетанию свойст
	//pair<City*, int> getAllCities() const; // получение всех структур. (без изменения состояния объекта)
	vector<City> getAllCities() const;

};

