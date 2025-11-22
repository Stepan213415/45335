#include <iostream>
#include <vector>
#include <cmath>
#include <clocale>

class SpaceObject {
protected:
    double x, y, z;
public:
    SpaceObject(double px = 0, double py = 0, double pz = 0) : x(px), y(py), z(pz) {}
    virtual ~SpaceObject() {}

    void MoveTo(double nx, double ny, double nz) {
        x = nx; y = ny; z = nz;
    }

    void MoveBy(double dx, double dy, double dz) {
        x += dx; y += dy; z += dz;
    }

    virtual double Volume() const = 0;
    virtual double SurfaceArea() const = 0;

    virtual void PrintInfo() const {
        std::cout << "Center: (" << x << ", " << y << ", " << z << ")  ";
    }

    double GetX() const { return x; }
    double GetY() const { return y; }
    double GetZ() const { return z; }
};

class Parallelepiped : public SpaceObject {
private:
    double length, width, height;
public:
    Parallelepiped(double x=0, double y=0, double z=0, double l=1, double w=1, double h=1)
        : SpaceObject(x, y, z), length(l), width(w), height(h) {}

    void SetDimensions(double l, double w, double h) {
        if (l > 0 && w > 0 && h > 0) {
            length = l; width = w; height = h;
        }
    }

    void Scale(double factor) {
        if (factor > 0) {
            length *= factor; width *= factor; height *= factor;
        }
    }

    double Volume() const {
        return length * width * height;
    }

    double SurfaceArea() const {
        return 2 * (length * width + length * height + width * height);
    }

    void PrintInfo() const {
        SpaceObject::PrintInfo();
        std::cout << "Parallelepiped: "
                  << length << "x" << width << "x" << height
                  << "  Volume=" << Volume()
                  << "  Area=" << SurfaceArea() << std::endl;
    }
};

class Sphere : public SpaceObject {
private:
    double radius;
public:
    Sphere(double x=0, double y=0, double z=0, double r=1)
        : SpaceObject(x, y, z), radius(r) { if (r < 0) radius = 0; }

    void SetRadius(double r) {
        if (r >= 0) radius = r;
    }

    void Scale(double factor) {
        if (factor > 0) radius *= factor;
    }

    double Volume() const {
        return (4.0 / 3.0) * 3.1415926535 * std::pow(radius, 3);
    }

    double SurfaceArea() const {
        return 4.0 * 3.1415926535 * std::pow(radius, 2);
    }

    void PrintInfo() const {
        SpaceObject::PrintInfo();
        std::cout << "Sphere: R=" << radius
                  << "  Volume=" << Volume()
                  << "  Area=" << SurfaceArea() << std::endl;
    }
};

int main() {
    setlocale(LC_ALL, "Ukrainian");

    std::vector<SpaceObject*> objects;

    objects.push_back(new Parallelepiped(0, 0, 0, 5, 3, 4));
    objects.push_back(new Sphere(10, -5, 8, 6));

    std::cout << "Start objects:\n";

    for (unsigned int i = 0; i < objects.size(); i++) {
        objects[i]->PrintInfo();
    }

    std::cout << "\nAfter move and scale:\n";

    objects[0]->MoveBy(2, 3, -1);
    ((Parallelepiped*)objects[0])->Scale(1.5);

    objects[1]->MoveTo(0, 0, 0);
    ((Sphere*)objects[1])->Scale(0.8);

    for (unsigned int i = 0; i < objects.size(); i++) {
        objects[i]->PrintInfo();
    }

    for (unsigned int i = 0; i < objects.size(); i++) {
        delete objects[i];
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.get();
    return 0;
}
