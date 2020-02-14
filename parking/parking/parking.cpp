#include "parking.h"
#include <iostream>
#include <fstream>
#include <map>

Parking::Parking()
	:
	floors( 1 ),
	rows( 1 ),
	columns( 1 ),
	last_spot_index( 0 )
{
	for ( int f = 1; f <= floors; f++ )
		for ( int r = 1; r <= rows; r++ )
			for ( int c = 1; c <= columns; c++ )
				parking_spots.push_back( Parking_spot( f, r, c ) );
}

Parking::Parking( int floors_num, int rows_num, int columns_num )
	:
	floors( floors_num ),
	rows( rows_num ),
	columns( columns_num ),
	last_spot_index( 0 )
{
	for ( int f = 1; f <= floors; f++ )
		for ( int r = 1; r <= rows; r++ )
			for ( int c = 1; c <= columns; c++ )
				parking_spots.push_back( Parking_spot( f, r, c ) );
}

void Parking::draw_taken_spots()
{
	std::cout << "spots with 1 are taken, spots with 0 are free: \n\n";
	for ( int f = 1; f <= floors; f++ )
	{
		std::cout << "floor " << f << ":\n";
		for ( int r = 1; r <= rows; r++ )
		{
			for ( int c = 1; c <= columns; c++ )
			{
				Parking_spot* spot = find_spot_at( f, r, c );
				std::cout << !(spot->is_free()) << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
}

void Parking::print_parking_info()
{
	for ( int i = 0; i < parking_spots.size(); i++ )
	{
		parking_spots[i].print_info();
	}
}

void Parking::print_parking_spot_info( Parking_spot* spot )
{
	spot -> print_info();
}

Parking_spot* Parking::find_free_spot()
{
	last_spot_index += 2;
	if ( last_spot_index > parking_spots.size() )
		last_spot_index = 1;
	else if ( last_spot_index = parking_spots.size() )
	{
		std::cout << "there is no parking spot left\n\n";
		return nullptr;
	}

	return &parking_spots[last_spot_index];
	/*int increment = 0;
	for ( int i = 0; i < 2; i++ )
	{
		int top_row = rows;
		int bottom_row = 1;

		for ( ; bottom_row <= top_row; bottom_row += 2, top_row -= 2 )
		for ( int f = 1; f <= floors; f++ )
		for ( int c = 1 + increment; c <= columns; c += 2 )
		{
			int top_index = c + (top_row - 1)*columns + (f - 1)*columns*rows - 1;
			int bot_index = c + (bottom_row - 1)*columns + (f - 1)*columns*rows - 1;

			if ( parking_spots[top_index].is_free() )
				return &parking_spots[top_index];
			
			if ( parking_spots[bot_index].is_free() )
				return &parking_spots[bot_index];
		}

		top_row = rows - 1;
		bottom_row = 2;
		increment = !increment;

		for ( ; bottom_row <= top_row; bottom_row += 2, top_row -= 2 )
		for ( int f = 1; f <= floors; f++ )
		for ( int c = 1 + increment; c <= columns; c += 2 )
		{
			int top_index = c + (top_row - 1)*columns + (f - 1)*columns*rows - 1;
			int bot_index = c + (bottom_row - 1)*columns + (f - 1)*columns*rows - 1;

			if ( parking_spots[top_index].is_free() )
				return &parking_spots[top_index];

			if ( parking_spots[bot_index].is_free() )
				return &parking_spots[bot_index];
		}
	}
	return nullptr;*/
}

Parking_spot * Parking::find_spot_at( int floor, int row, int column )
{
	int index = column + (row - 1)*columns + (floor - 1)*rows*columns - 1;
	return &parking_spots[index];
}

Parking_spot* Parking::find_spot_of( std::string reg )
{
	return car_positions[reg];
	/*for (int i = 0; i < parking_spots.size(); i++)
	{
		if (parking_spots[i].registration == reg)
			return &parking_spots[i];
		else
			return nullptr;
	}*/
}

Parking_spot* Parking::take_parking_spot( std::string reg )
{
	Parking_spot* free_spot = find_free_spot();
	if (free_spot != nullptr)
	{
		free_spot->take_spot(reg);
		car_positions[reg] = free_spot;
		return free_spot;
	}
	else
	{
		std::cout << "all spots are taken\n\n";
		return nullptr;
	}
}

void Parking::free_parking_spot( std::string reg )
{
	find_spot_of( reg ) -> free_spot();
	car_positions.erase( reg );
}

void Parking::free_parking_spot( Parking_spot* spot )
{
	spot -> free_spot();
}

void Parking::save_parking_configuration( std::string file )
{
	std::ofstream out( file.c_str(), std::ios_base::binary );
	if ( out.fail() )
	{
		std::cout << "failed to save the file\n\n";
		return;
	}

	std::string last_spot_index_s = std::to_string( last_spot_index );
	std::string num_floors = std::to_string( floors );
	std::string num_rows = std::to_string( rows );
	std::string num_columns = std::to_string( columns );
	
	for ( int i = 0; i < last_spot_index_s.size(); i++ )
		out.put( last_spot_index_s[i] );
	out.put( '|' );

	for ( int i = 0; i < num_floors.size(); i++ )
		out.put( num_floors[i] );
	out.put( '|' );

	for ( int i = 0; i < num_rows.size(); i++ )
		out.put( num_rows[i] );
	out.put( '|' );

	for ( int i = 0; i < num_columns.size(); i++ )
		out.put( num_columns[i] );
	out.put( '|' );

	for ( int i = 0; i < parking_spots.size(); i++ )
	{
		std::string reg = parking_spots[i].registration;
		for ( int i2 = 0; i2 < reg.size(); i2++ )
		{
			out.put( reg[i2] );
		}
		out.put( '|' );
	}

	std::cout << "parking configuration saved at " << file << "\n\n";
}

void Parking::load_parking_configuration( std::string file )
{
	char execute_function;
	std::cout << "WARNING! all current data will be overwriten. Proceed? (y)es (n)o: ";
	std::cin >> execute_function;
	if ( execute_function == 'n' )
		return;

	std::ifstream in( file.c_str(), std::ios_base::binary );
	if ( in.fail() )
	{
		std::cout << "failed to save the file\n\n";
		return;
	}
	
	parking_spots.clear();

	std::string last_spot_index_s = "";
	std::string num_floors = "";
	std::string num_rows = "";
	std::string num_columns = "";

	for ( char c = in.get(); in.good() && c != '|'; c = in.get() )
		last_spot_index_s += c;
	last_spot_index = std::stoi( last_spot_index_s );

	for ( char c = in.get(); in.good() && c != '|'; c = in.get() )
		num_floors += c;
	floors = std::stoi( num_floors );

	for ( char c = in.get(); in.good() && c != '|'; c = in.get() )
		num_rows += c;
	rows = std::stoi( num_rows );

	for ( char c = in.get(); in.good() && c != '|'; c = in.get() )
		num_columns += c;
	columns = std::stoi( num_columns );

	std::string tempReg = "";
	for ( int f = 1; f <= floors; f++ )
	for ( int r = 1; r <= rows; r++ )
	for ( int c = 1; c <= columns; c++ )
	{
		for ( char c = in.get(); in.good() && c != '|'; c = in.get() )
		{
			tempReg += c;
		}
		Parking_spot tempSpot( f, r, c, tempReg );
		parking_spots.push_back( tempSpot );
		tempReg = "";
	}

	std::cout << "parking configuration from " << file << " loaded\n\n";
}
