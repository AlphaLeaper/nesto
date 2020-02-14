#include "parking_spot.h"
#include <iostream>

Parking_spot::Parking_spot( int floor, int row, int column )
	:
	floor( floor ),
	row( row ),
	column( column ),
	registration( "" )
{
}

Parking_spot::Parking_spot( int floor, int row, int column, std::string registration )
	:
	floor( floor ),
	row( row ),
	column( column ),
	registration( registration )
{
}

void Parking_spot::take_spot( std::string reg )
{
	registration = reg;
}

void Parking_spot::free_spot()
{
	registration = "";
}

void Parking_spot::print_info()
{
	std::cout << "floor: " << floor << "\n";
	std::cout << "row: " << row << "\n";
	std::cout << "column: " << column << "\n";
	std::cout << "registration: " << registration << "\n\n";
}

bool Parking_spot::is_free()
{
	return ( registration == "" );
}
