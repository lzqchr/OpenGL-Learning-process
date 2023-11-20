#pragma once
#include "GL/glew.h"
#include <iostream>
class SSBO
{
public:
	SSBO(const void* data, unsigned int size);
	~SSBO();
    void Update(const void* data, unsigned int size, unsigned int offset);
    void Bind(unsigned int solt = 0);
private:
	unsigned int ID;
};
