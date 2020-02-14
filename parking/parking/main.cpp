#include <iostream>
#include <fstream>
#include <string>
#include "parking.h"

int main( void )
{
	Parking parking( 3, 5, 8 );
	Boot( parking );
	bool isRunning = true;
	while ( isRunning )
		run( isRunning, parking );
}

void Boot( Parking& p )
{
	std::ifstream firstBootIn( "boot.dat", std::ios_base::binary );
	if ( !firstBootIn.good() )
	{
		std::ofstream firstBootOut( "boot.dat", std::ios_base::binary );
		firstBootOut.put( '1' );
	}
	else
		p.load_parking_configuration( "boot.dat" );
}

void ShutDown( bool& isRunning, Parking& p )
{
	isRunning = false;
	p.save_parking_configuration( "boot.dat" );
}

void run( bool& isRunning, Parking& p )
{
	std::string input;
	std::cout << "console>> ";
	std::cin >> input;

	if ( input == "take_spot" )
	{
		std::string registration;
		std::cout << "your registration: ";
		std::cin >> registration;
		std::cout << "successfuly registered, your parking spot is located at:\n";
		p.print_parking_spot_info( p.take_parking_spot( registration ) );
	}
	else if ( input == "remove_from_spot" )
	{
		std::string registration;
		std::cout << "vehicle registration: ";
		std::cin >> registration;
		p.free_parking_spot( registration );
	}
	else if ( input == "draw_taken_spots" )
	{
		std::cout << "taken spots:\n";
		p.draw_taken_spots();
	}
	else if ( input == "print_parking_info" )
	{
		std::cout << "printing parking info:\n";
		p.print_parking_info();
	}
	else if ( input == "print_parking_spot_at_frc" )
	{
		int floor;
		int row;
		int column;
		std::cout << "input floor, row and column: ";
		std::cin >> floor >> row >> column;
		p.print_parking_spot_info( p.find_spot_at( floor, row, column ) );
	}
	else if ( input == "print_parking_spot_at_reg" )
	{
		std::string reg;
		std::cout << "input reg: ";
		std::cin >> reg;
		p.print_parking_spot_info( p.find_spot_at( reg ) );
	}
}

