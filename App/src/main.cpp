#include "Engine/Application.h"
#include <memory>

int main() {
	auto app = std::make_unique<Engine::Application>();
	app->start(1024, 768, "Test");
}

