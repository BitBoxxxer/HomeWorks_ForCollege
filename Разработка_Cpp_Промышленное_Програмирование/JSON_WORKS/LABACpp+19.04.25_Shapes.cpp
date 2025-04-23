#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class Shape {
public:
    virtual void Show() = 0;
    virtual json Save() = 0;
    virtual void Load(const json& j) = 0;
    virtual ~Shape() {}
};

class Square : public Shape {
    int x, y, side;
public:
    Square() {}
    Square(int x, int y, int side) : x(x), y(y), side(side) {}
    void Show() override { cout << "Square: (" << x << ", " << y << "), Сторона: " << side << endl; }

    json Save() override {
        return { {"type", "Square"}, {"x", x}, {"y", y}, {"side", side} };
    }

    void Load(const json& j) override {
        x = j["x"];
        y = j["y"];
        side = j["side"];
    }
};

class Rectangle : public Shape {
    int x, y, width, height;
public:
    Rectangle() {}
    Rectangle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}
    void Show() override { cout << "Rectangle: (" << x << ", " << y << "), Ширина: " << width << ", Высота: " << height << endl; }

    json Save() override {
        return { {"type", "Rectangle"}, {"x", x}, {"y", y}, {"width", width}, {"height", height} };
    }

    void Load(const json& j) override {
        x = j["x"];
        y = j["y"];
        width = j["width"];
        height = j["height"];
    }
};

class Circle : public Shape {
    int x, y, radius;
public:
    Circle() {}
    Circle(int x, int y, int radius) : x(x), y(y), radius(radius) {}
    void Show() override { cout << "Circle: (" << x << ", " << y << "), радиус: " << radius << endl; }

    json Save() override {
        return { {"type", "Circle"}, {"x", x}, {"y", y}, {"radius", radius} };
    }

    void Load(const json& j) override {
        x = j["x"];
        y = j["y"];
        radius = j["radius"];
    }
};

class Ellipse : public Shape {
    int x, y, width, height;
public:
    Ellipse() {}
    Ellipse(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}
    void Show() override { cout << "Ellipse: (" << x << ", " << y << "), Ширина: " << width << ", Высота: " << height << endl; }

    json Save() override {
        return { {"type", "Ellipse"}, {"x", x}, {"y", y}, {"width", width}, {"height", height} };
    }

    void Load(const json& j) override {
        x = j["x"];
        y = j["y"];
        width = j["width"];
        height = j["height"];
    }
};

void save_to_file(const vector<unique_ptr<Shape>>& shapes, const string& filename) {
    json vector_json;
    for (const auto& shape : shapes) {
        vector_json.push_back(shape->Save());
    }
    ofstream out(filename);
    if (out.is_open()) {
        out << vector_json.dump(4) << endl;
    }
    else {
        cout << "Ошибка при открытии файла!" << endl;
    }
}

vector<unique_ptr<Shape>> load_shapes(const string& filename) {
    vector<unique_ptr<Shape>> shapes;
    ifstream in(filename);
    json j;
    in >> j;

    for (const auto& item : j) {
        unique_ptr<Shape> shp;
        if (item["type"] == "Square") {
            auto square = make_unique<Square>();
            square -> Load(item);
            shp = move(square);
        }
        else
        {
            if (item["type"] == "Circle") {
                auto circ = make_unique<Circle>();
                circ->Load(item);
                shp = move(circ);
            }
            else
            {
                if (item["type"] == "Rectangle") {
                    auto rec = make_unique<Rectangle>();
                    rec->Load(item);
                    shp = move(rec);
                }
                else
                {
                    if (item["type"] == "Ellipse") {
                        auto Ell = make_unique<Ellipse>();
                        Ell->Load(item);
                        shp = move(Ell);
                    }
                }
            }

        }
        if (shp) 
            shapes.push_back(move(shp));
    }

    return shapes;
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<unique_ptr<Shape>> shapes;
    shapes.emplace_back(make_unique<Square>(10, 10, 5));
    shapes.emplace_back(make_unique<Rectangle>(20, 20, 10, 5));
    shapes.emplace_back(make_unique<Circle>(30, 30, 7));
    shapes.emplace_back(make_unique<Ellipse>(40, 40, 20, 10));

    string filename = "shapes.json";
    save_to_file(shapes, filename);

    auto loaded_shapes = load_shapes(filename);

    cout << "Загруженные фигуры json:" << endl;
    for (auto& shape : loaded_shapes) {
        shape->Show();
    }
}
