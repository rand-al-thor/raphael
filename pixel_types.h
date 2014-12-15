#ifndef _pixel_types_h_
#define _pixel_types_h_

#include <cstdint>

struct pixel3channel	{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

struct pixel4channel	{
	pixel3channel colour;
	uint8_t alpha;
};

#endif
