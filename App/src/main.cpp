#include "Engine/Window.h"
#include <memory>
#include <iostream>
int main() {
	try{
	auto window = std::make_unique<Engine::Window>(800, 800, "Test");
    window->Start();
	}catch (std::exception e)
	{
		std::cout << e.what();
	}
}

