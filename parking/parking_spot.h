#pragma once
#include <string>

class Parking_spot
{
public:
	Parking_spot( int floor, int row, int column );
	Parking_spot( int floor, int row, int column, std::string registration );
public:
	void take_spot( std::string registration );
	void free_spot();
	void print_info();
	bool is_free();
public:
	int floor;
	int row;
	int column;
	std::string registration;
};