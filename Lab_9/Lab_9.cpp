#include <iostream>
#include "BinaryTreeCity.h"
#include "city.h"
#include <vector>


// вызов деструктора для удаления всех узлов
BinaryTreeCity::~BinaryTreeCity() {
    deleteTree(root);
}

// функция удаления всех узлов дерева
void BinaryTreeCity::deleteTree(TreeNode*& node) {
    if (!node) {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
    node = nullptr;
}

// добавление узла в дерево
void BinaryTreeCity::insert(TreeNode*& node, const City& city) {
    if (!node) { // если Null (нет потомков у узла)
        node = new TreeNode(city);
    }
    // если кол-во площади на одного человека в новом городе меньше или равна кол-во площали приходящейся на одного человка больше в узле node, то новый узел вставляется в leftNode
    else if (city.numberInhabitants / city.square <= node->city.numberInhabitants / node->city.square) {
        insert(node->left, city);
    }
    else {
        insert(node->right, city);
    }
}

// добавление города
void BinaryTreeCity::addCity(const City& city) {
    insert(root, city);
}

// удаление узла по сочетанию значений полей
BinaryTreeCity::TreeNode* BinaryTreeCity::remove(TreeNode*& node, int numberInhabitants, double square) {
    if (!node) { // нет узла
        return nullptr;
    }

    if (numberInhabitants / square < node->city.numberInhabitants / node->city.square) {    
            // пока справа больше площади на один кв метр, буде удялятся узел left (чтобы не нарушалась иерархия)
            node->left = remove(node->left, numberInhabitants, square); 
    }
    else if (numberInhabitants / square > node->city.numberInhabitants / node->city.square) {
        // пока справа меньше площади на один кв метр, буде удялятся узел right (чтобы не нарушалась иерархия)
        node->right = remove(node->right, numberInhabitants, square);
    }
    else {
        if (!node->left && !node->right) { // если оба дочерних узла пусты, то текщий узел удаляется, а указатель nullptr
            delete node;
            return nullptr;
        }
        else if (!node->left) { // если левый узел пустой, то 
            TreeNode* temp = node->right; // правый узел сохраняется во временную переменную указателя узла
            delete node; // далее, узел удаляется
            return temp; // возврат правого указателя на место удаленного узла
        }
        else if (!node->right) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }
        else { // если оба дочерних узла есть
            TreeNode* temp = node->right; // ищем наименьший узелв правом поддереве 
            while (temp->left)
            {
                temp = temp->left; // и заменяем текущие данного узла на данный найденного узла
            }
            node->city = temp->city;
            node->right = remove(node->right, temp->city.numberInhabitants, temp->city.square); // рекурсивно вызываем функцию для удаления узла с найденными данными из правого поддерева
        }
    }
    return node;
}

// удаление города
void BinaryTreeCity::removeCity( int numberInhabitants, double square) {
    root = remove(root, numberInhabitants, square);
}

// поиск заданного элемента
BinaryTreeCity::TreeNode* BinaryTreeCity::find(TreeNode* node, int numberInhabitants, double square) const {
    if (!node) { // отсутствует узел
        return nullptr; // 
    }

    if (numberInhabitants / square < node->city.numberInhabitants / node->city.square) {
        return find(node->left, numberInhabitants, square);
    }
    else if (numberInhabitants / square > node->city.numberInhabitants / node->city.square) {
        return find(node->right, numberInhabitants, square);
    }
    else {
        return node;
    }

}
// поиск города
bool BinaryTreeCity::hasCity(int numberInhabitants, double square) const {
    return find(root, numberInhabitants, square) != nullptr;
}

//// заполнение массива всеми элементами
//void BinaryTreeCity::inOrderTraversal(TreeNode* node, City* citiesArray, int& index) const {
//    if (!node) {
//        return; // если узел пустой, то программа работает дальше без заполнения массива
//    }
//    
//    // обход узлов дерева в порядке возрастная
//    inOrderTraversal(node->left, citiesArray, index); // рекурсивная функция для левого поддерева, для обхождения всех ее узлов
//    if (citiesArray) {
//        citiesArray[index++] = node->city; // запись, если массив городов не является nullptr
//    }; // запись при наличии элементов
//    inOrderTraversal(node->right, citiesArray, index);
//}
//
//// заполнение массива всеми городами
//pair<City*, int> BinaryTreeCity::getAllCities() const {
//    if (!root) {
//        return std::make_pair(nullptr, 0);
//    }
//
//    int numOfCities = 0;
//    inOrderTraversal(root, nullptr, numOfCities);
//
//    City* citiesArray = new City[numOfCities];
//    int index = 0;
//    inOrderTraversal(root, citiesArray, index);
//
//    return std::make_pair(citiesArray, numOfCities);
//}

vector<City> BinaryTreeCity::getAllCities() const {
    vector<City> citiesVector;
    inOrderTraversal(root, citiesVector);
    return citiesVector;
}

void BinaryTreeCity::inOrderTraversal(TreeNode* node, vector<City>& citiesVector) const {
    if (!node) {
        return;
        string error = "Ошибка вывода данных!";
        throw error;
    }

    inOrderTraversal(node->left, citiesVector); // рекурсивная функция для левого поддерева, для обхождения всех ее узлов
    citiesVector.push_back(node->city); // запись, если массив городов не является nullptr
    inOrderTraversal(node->right, citiesVector);
}



int main()
{
    setlocale(LC_ALL, "Ru"); // русская локализация

    BinaryTreeCity binaryTreeCity;
    City city;
    
    int position = 0; // позиция
    int number = 0; // номер программы
    bool flag = true; // цикл работы программы

    while (flag != false) {

        cout << "1. Добавить город (Элемента)" << endl;
        cout << "2. Удалить город (Элемента) по сочетанию населения и площади (кол-во кв.м на 1 ч.)" << endl;
        cout << "3. Проверка наличия города (Элемента) по сочетанию населения и площади (кол-во кв.м на 1 ч.)" << endl;
        cout << "4. Получение описаний всех структур хранящихся в дереве" << endl;

        cout << "5. Выход из программы" << endl;
        cout << "\nВведите номер функции: ";
        try {
            cin >> number;
        }
        catch (string error_message) {
            cin.clear();
        }
        cout << endl;

        // добавление городов в список
        switch (number)
        {
        case 1:
            cout << "Название города: ";
            cin >> city.cityName;
            cout << "Дата основания города: ";
            cin >> city.dateFoundation;
            cout << "Кол-во жителей: ";
            cin >> city.numberInhabitants;
            cout << "Площадь города: ";
            cin >> city.square;
            cout << endl;

            binaryTreeCity.addCity(city);
            break;

        case 2: {
            int numPeple = 0;
            double numSquare = 0;
            cout << "\nВведите численность населения: ";
            cin >> numPeple;
            cout << "\nВведите площадь города: ";
            cin >> numSquare;
            binaryTreeCity.removeCity(numPeple, numSquare);


            break;
        }

        case 3: {
            int numPeple = 0;
            double numSquare = 0;
            cout << "\nВведите численность населения: ";
            cin >> numPeple;
            cout << "\nВведите площадь города: ";
            cin >> numSquare;

            if (binaryTreeCity.hasCity(numPeple, numSquare) == 1) {
                cout << "Город с параметрами с данными параметрами найден!" << endl;
            }
            else {
                cout << "Город с параметрами с данными параметрами не найден!" << endl;
            }
            cout << endl;  
            break;
        }

        case 4: {

            try {
                vector<City> allCities = binaryTreeCity.getAllCities();

                // Вывод описаний всех городов
                std::cout << "\nПолучение всех городов:" << std::endl;
                for (const auto& city : allCities) {
                    cout << "\nНазвание города: " << city.cityName << endl;
                    cout << "Дата основания: " << city.dateFoundation << endl;
                    cout << "Кол-во жителей: " << city.numberInhabitants << endl;
                    cout << "Площадь города: " << city.square << endl;
                    cout << endl;
                }
            }
            catch (string error) {
                cout << error << endl;
                cin.clear();
            }
            break;
        }

        case 5: {
            flag = false;
            break;
            break;
        }

        default:
            break;

            return 0;
        }
    }
}
