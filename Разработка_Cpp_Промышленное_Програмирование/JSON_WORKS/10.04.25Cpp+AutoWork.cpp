#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class TransBase {
public:
    virtual void Show() = 0;
    virtual json Save() = 0;
    virtual void Load(const json& j) = 0;
    virtual ~TransBase() {}
};

class Tachka : public TransBase {
    int x, y, side;
public:
    Tachka() {}
    Tachka(int x, int y, int side) : x(x), y(y), side(side) {}
    void Show() override { cout << "Tachka: (" << x << ", " << y << "), Сторона: " << side << endl; }

    json Save() override {
        return { {"type", "Tachka"}, {"x", x}, {"y", y}, {"side", side} };
    }

    void Load(const json& j) override {
        x = j["x"];
        y = j["y"];
        side = j["side"];
    }
};

class Auto : public TransBase {
    int x, y, radius;
public:
    Auto() {}
    Auto(int x, int y, int radius) : x(x), y(y), radius(radius) {}
    void Show() override { cout << "Auto: (" << x << ", " << y << "), радиус: " << radius << endl; }

    json Save() override {
        return { {"type", "Auto"}, {"x", x}, {"y", y}, {"radius", radius} };
    }

    void Load(const json& j) override {
        x = j["x"];
        y = j["y"];
        radius = j["radius"];
    }
};

class Bike : public TransBase {
    int x, y, width, height;
public:
    Bike() {}
    Bike(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}
    void Show() override { cout << "Bike: (" << x << ", " << y << "), Ширина: " << width << ", Высота: " << height << endl; }

    json Save() override {
        return { {"type", "Bike"}, {"x", x}, {"y", y}, {"width", width}, {"height", height} };
    }

    void Load(const json& j) override {
        x = j["x"];
        y = j["y"];
        width = j["width"];
        height = j["height"];
    }
};

void save_to_file(const vector<unique_ptr<TransBase>>& shapes, const string& filename) {
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

vector<unique_ptr<TransBase>> load_shapes(const string& filename) {
    vector<unique_ptr<TransBase>> shapes;
    ifstream in(filename);
    json j;
    in >> j;

    for (const auto& item : j) {
        unique_ptr<TransBase> shp;
        if (item["type"] == "Square") {
            auto square = make_unique<Tachka>();
            square->Load(item);
            shp = move(square);
        }
        else
        {
            if (item["type"] == "Circle") {
                auto circ = make_unique<Auto>();
                circ->Load(item);
                shp = move(circ);
            }
            else
            {
                if (item["type"] == "Ellipse") {
                    auto Ell = make_unique<Bike>();
                    Ell->Load(item);
                    shp = move(Ell);
                }
            }
        }
        if (shp) {
            shapes.push_back(move(shp));
        }
    }

    return shapes;
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<unique_ptr<TransBase>> shapes;
    shapes.emplace_back(make_unique<Tachka>(10, 10, 5));
    shapes.emplace_back(make_unique<Auto>(30, 30, 7));
    shapes.emplace_back(make_unique<Bike>(40, 40, 20, 10));

    string filename = "autos.json";
    save_to_file(shapes, filename);

    auto loaded_shapes = load_shapes(filename);

    cout << "Загруженные фигуры:" << endl;
    for (const auto& shape : loaded_shapes) {
        shape->Show();
    }
}
