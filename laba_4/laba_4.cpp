#include <iostream>
#include <vector>
#include <cmath>
//#include <windows.h>
#include <stdexcept>

using namespace std;

class RegularPolygon {
private:
    int sides;
    double sideLength;
    double orientation;

    constexpr static const double PI = 3.14159265358979323846;

public:
    RegularPolygon(int n = 3, double length = 1, double angle = 0)
        : sides(n), sideLength(length), orientation(angle* PI / 360) {
        if (n < 3) sides = 3;
        if (length <= 0) sideLength = 1.0;
    }

    //перегрузки сложения и вычитания с целым числом
    RegularPolygon operator+(int n) const {
        return RegularPolygon(sides + n, sideLength, orientation * 180.0 / PI);
    }

    RegularPolygon operator-(int n) const {
        return RegularPolygon(sides - n > 2 ? sides - n : 3, sideLength, orientation * 180.0 / PI);
    }

    //инкремент и декремент
    RegularPolygon& operator++() {  //префиксный
        ++sides;
        return *this;
    }

    RegularPolygon operator++(int) {  //постфиксный
        RegularPolygon temp = *this;
        ++sides;
        return temp;
    }

    RegularPolygon& operator--() {  //префиксный
        if (sides > 3)
            --sides;
        return *this;
    }

    RegularPolygon operator--(int) {  //постфиксный
        RegularPolygon temp = *this;
        if (sides > 3)
            --sides;
        return temp;
    }

    //перегрузки умножения и деления на число
    RegularPolygon operator*(double factor) const {
        return RegularPolygon(sides, sideLength * factor, orientation * 180.0 / PI);
    }
    RegularPolygon operator/(double factor) const {
        if (factor == 0)
            throw invalid_argument("Division by zero");
        return RegularPolygon(sides, sideLength / factor, orientation * 180.0 / PI);
    }

    //геометрические вычисления
    double getPerimeter() const {
        return sides * sideLength;
    }

    double getArea() const {
        return (sides * sideLength * sideLength) / (4.0 * tan(PI / sides));
    }

    double getCentralAngle() const {
        return 360 / sides;
    }

    vector<double> getEdgeDirections() const {
        vector<double> directions;
        double angle = orientation;
        for (int i = 0; i < sides; ++i) {
            directions.push_back(angle * 180.0 / PI);
            angle += 2 * PI / sides;
        }
        return directions;
    }

    double getInscribedRadius() const {
        return sideLength / (2 * tan(PI / sides));
    }

    double getCircumscribedRadius() const {
        return sideLength / (2 * sin(PI / sides));
    }

    //изменение ориентации
    void rotate(double angle) {
        orientation += angle * PI / 180.0;
    }

    //вывод
    void print() const {
        cout << "Правильный " << sides << "-угольник\n"
            << "Длина стороны: " << sideLength << "\n"
            << "Ориентация: " << orientation * 180.0 / PI << "°\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const RegularPolygon& poly) {
        os << "Правильный " << poly.sides << "-угольник\n"
            << "Длина -> " << poly.sideLength << ", "
            << "ориентация -> " << poly.orientation * 180.0 / PI << "°";
        return os;
    }
};

int main() {

        setlocale(LC_ALL, "Rus");
        //SetConsoleCP(CP_UTF8);
        //SetConsoleOutputCP(CP_UTF8);

        int sides;
        double length;

        cout << "Введите количество сторон многоугольника: ";
        cin >> sides;
        cout << "Введите длину стороны многоугольника: ";
        cin >> length;

        RegularPolygon poly (sides, length); // Создание многоугольника

        bool running = true;
        while (running) {
            cout << "\nМеню:\n";
            cout << "1. Показать многоугольник\n";
            cout << "2. Сложение длины стороны\n";
            cout << "3. Вычитание длины стороны\n";
            cout << "4. Постинкремент\n";
            cout << "5. Постдекремент\n";
            cout << "6. Показать периметр\n";
            cout << "7. Показать площадь\n";
            cout << "8. Показать центральный угол\n";
            cout << "9. Показать направления рёбер\n";
            cout << "10. Вращение\n";
            cout << "11. Выход\n";
            cout << "Выберите опцию (1-11): ";

            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Многоугольник: " << poly << endl;
                break;
            case 2: {
                double value;
                cout << "Введите величину для сложения: ";
                cin >> value;
                poly = poly + value;
                cout << "Сложение (+ " << value << "): " << poly << endl;
                break;
            }
            case 3: {
                double value;
                cout << "Введите величину для вычитания: ";
                cin >> value;
                poly = poly - value;
                cout << "Вычитание (- " << value << "): " << poly << endl;
                break;
            }
            case 4:
                ++poly;
                cout << "Постинкремент: " << poly << endl;
                break;
            case 5:
                --poly;
                cout << "Постдекремент: " << poly << endl;
                break;
            case 6:
                cout << "Периметр: " << poly.getPerimeter() << endl;
                break;
            case 7:
                cout << "Площадь: " << poly.getArea() << endl;
                break;
            case 8:
                cout << "Центральный угол: " << poly.getCentralAngle() << endl;
                break;
            case 9: {
                vector<double> directions = poly.getEdgeDirections();
                cout << "Направления рёбер: ";
                for (auto i : directions) {
                    cout << i << "° ";
                }
                cout << endl;
                break;
            }
            case 10: {
                double angle;
                cout << "Введите угол для вращения: ";
                cin >> angle;
                poly.rotate(angle);
                cout << "Вращение (на " << angle << "°): " << poly << endl;
                break;
            }
            case 11:
                running = false;
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неверный выбор. Пожалуйста, выберите снова." << endl;
                break;
            }
        }

        return 0;
    }