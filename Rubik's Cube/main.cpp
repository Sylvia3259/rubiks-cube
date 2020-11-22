#include <iostream>
#include <Windows.h>
#include "Engine.h"
using namespace std;

class RubiksEngine : Engine {
private:
public:
    RubiksEngine(int width, int height) : Engine(width, height) {}

    void OnCreate() override {

    }
    void OnUpdate(double deltaTime) override {

    }
    void OnDestroy() override {

    }
};

int main() {
    return 0;
}