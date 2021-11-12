#pragma once

namespace Engine
{
	class Application {
	public:
		Application();
		
		int start(unsigned int height, unsigned int width, const char* title);
	};

}
