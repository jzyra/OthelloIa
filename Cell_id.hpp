/*!
* \file Cell_id.hpp
* \brief Contains define for calculate cell id.
* \author Jeremy ZYRA
*/
#ifndef CELL_ID_H
#define CELL_ID_H

//Get cell id with x, y, and width in parameter.
#define CELL_ID(x, y, size_width) (((y)*(size_width))+(x))
//Get x, y with cell id and width in parameter.
#define CELL_COORD(id, size_width) ((id)%(size_width)), ((id)/(size_width))

enum {
	HUMAN=1,
	IA=2
};

#endif
