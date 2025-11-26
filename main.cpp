#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

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

    virtual void SetVolume(double targetVolume) = 0;

    virtual void PrintInfo() const {
        std::cout << "Center: (" << x << ", " << y << ", " << z << ") ";
    }
};

class Parallelepiped : public SpaceObject {
private:
    double length, width, height;
public:
    Parallelepiped(double x=0, double y=0, double z=0, double l=1, double w=1, double h=1)
        : SpaceObject(x, y, z), length(l), width(w), height(h) {}

    void SetVolume(double targetVolume) override {
        if (targetVolume <= 0) {
            std::cout << "Error: Volume must be positive." << std::endl;
            return;
        }

        double currentVolume = Volume();
        if (currentVolume == 0) return;

        double scaleFactor = std::pow(targetVolume / currentVolume, 1.0/3.0);

        length *= scaleFactor;
        width *= scaleFactor;
        height *= scaleFactor;
    }

    double Volume() const override {
        return length * width * height;
    }

    double SurfaceArea() const override {
        return 2 * (length * width + length * height + width * height);
    }

    void PrintInfo() const override {
        SpaceObject::PrintInfo();
        std::cout << "| Type: Parallelepiped | Dim: "
                  << std::fixed << std::setprecision(2)
                  << length << "x" << width << "x" << height
                  << " | Vol: " << Volume()
                  << " | Area: " << SurfaceArea() << std::endl;
    }
};

class Sphere : public SpaceObject {
private:
    double radius;
    const double PI = 3.1415926535;
public:
    Sphere(double x=0, double y=0, double z=0, double r=1)
        : SpaceObject(x, y, z), radius(r) { if (r < 0) radius = 0; }

    void SetVolume(double targetVolume) override {
        if (targetVolume <= 0) {
            std::cout << "Error: Volume must be positive." << std::endl;
            return;
        }
        radius = std::pow((3.0 * targetVolume) / (4.0 * PI), 1.0/3.0);
    }

    double Volume() const override {
        return (4.0 / 3.0) * PI * std::pow(radius, 3);
    }

    double SurfaceArea() const override {
        return 4.0 * PI * std::pow(radius, 2);
    }

    void PrintInfo() const override {
        SpaceObject::PrintInfo();
        std::cout << "| Type: Sphere       | R: "
                  << std::fixed << std::setprecision(2) << radius
                  << "          | Vol: " << Volume()
                  << " | Area: " << SurfaceArea() << std::endl;
    }
};

int main() {
    std::vector<SpaceObject*> objects;

    objects.push_back(new Parallelepiped(0, 0, 0, 2, 3, 4));
    objects.push_back(new Sphere(10, 5, 5, 2));

    std::cout << "Initial state of objects" << std::endl;
    for (const auto* obj : objects) {
        obj->PrintInfo();
    }

    std::cout << "\nSetting target volume (1000.0) for all shapes" << std::endl;
    double targetVol = 1000.0;

    for (auto* obj : objects) {
        obj->SetVolume(targetVol);
    }

    std::cout << "\nState of objects after volume change" << std::endl;
    for (const auto* obj : objects) {
        obj->PrintInfo();
    }

    for (auto* obj : objects) {
        delete obj;
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.get();
    return 0;
}
