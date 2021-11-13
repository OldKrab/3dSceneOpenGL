#include "Engine/Window.h"
#include <memory>

int main() {
	auto window = std::make_unique<Engine::Window>(1024, 768, "Test");
    window->Start();
}

