#ifndef _image_reader_h_
#define _image_reader_h_a

#include <raster.h>

namespace reader	{

template <class T>
class image_reader_imp	{

	image_reader_imp() = delete;
	image_reader_imp( const std::string& filename) : mFileName(filename)	{}
	
	bool open_file() = 0;

	bool read_image( raphael::raster& img ) = 0;

	void close_file() = 0;
	
	~image_reader_imp()	{}
	std::string mFileName;
};

} /* end of namespace reader*/

#endif
