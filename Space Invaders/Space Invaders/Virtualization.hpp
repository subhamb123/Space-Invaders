#pragma once

#include "header.hpp"
#include "Scoring.hpp"
#include "Menu.hpp"

class Virtualization {
public:
	Virtualization();
	~Virtualization();
private:
	Scoring s;
	Menu m;
};