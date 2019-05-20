#pragma once
class LoadShaders
{
public:
	LoadShaders();
	
	unsigned int loadShaders(const char* vertexPath, const char* fragmentPath);

	~LoadShaders();
};

