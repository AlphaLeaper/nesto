#pragma once
#include <vector>
#include <map>
#include "parking_spot.h"

class Parking
{
public:
	Parking();
	Parking(  int floors, int rows, int columns );
public:
	void draw_taken_spots();
	void print_parking_info();
	void print_parking_spot_info( Parking_spot* spot );
	Parking_spot* find_free_spot();
	Parking_spot* find_spot_at( int floor, int row, int column );
	Parking_spot* find_spot_of( std::string registration );
	Parking_spot* take_parking_spot( std::string registration );
	void free_parking_spot( std::string registration );
	void free_parking_spot( Parking_spot* spot );
	void save_parking_configuration( std::string file );
	void load_parking_configuration( std::string file );
private:
	int floors;
	int rows;
	int columns;
	std::vector<Parking_spot> parking_spots;
	std::map<std::string, Parking_spot*> car_positions;
};