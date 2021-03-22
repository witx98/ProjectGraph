#pragma once
#include "Graf.h"
#include "Ewelina\menu.h"
#include <iostream>
#include <sstream>


int main() {
	graf::Graf* program = new graf::Graf;

	program->wykonaj();


	std::cout << "--------" << std::endl;
	
	menu();

	delete program;
	
	return 0;
}

