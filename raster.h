#ifndef _raster_h_
#define _raster_h_

#include "pixel_types.h"
#include <iostream>
#include <cstring>

namespace raphael {
/*
	template class for an Raster type
*/
template <class PIXEL> 
struct Raster	{
	public:
		Raster( uint32_t width, uint32_t height) : m_width(width), m_height(height){
			try	{
				// If some idiot tries to give any of the dimensions as
				// zero, create a 'Zero' raster. Therefore, Raster(50,0)
				// will create a raster of dimensions (0,0) because by definition,
				// a 'raster' has two non zero dimensions.
				if( (m_width == 0) or (m_height == 0 ) )	{
					m_width = 0;	
					m_height = 0;
					m_pix = nullptr;
				} else	{
					m_pix = new PIXEL[width * height];
				}
			} catch( std::exception &e )	{
				std::cout << e.what() << std::endl;
				m_width = 0;
				m_height = 0;
				delete [] m_pix;
				m_pix = nullptr;
			}
		}
		Raster() : m_width(0), m_height(0), m_pix(nullptr){}

		~Raster( )	{
			delete[] m_pix;
			m_pix = nullptr;
		}
		
		// Copy constructor
		Raster (const Raster& rhs): m_width(rhs.m_width),
									m_height(rhs.m_height)	{
			// Make sure enough memory can be allocated for the pixel 
			// data. Catch any exceptions thrown and perform clean up
			try	{
				uint32_t size = m_width * m_height;
				if( size != 0 )	{
					m_pix = new PIXEL[m_width * m_height];
					std::memcpy(m_pix, rhs.m_pix, m_width*m_height*sizeof(PIXEL));	
				} else	{
					m_pix = nullptr;
				}
			} catch (std::exception &e)	{
				std::cout << e.what() << std::endl;
				m_width = 0;
				m_height = 0;
				delete [] m_pix;
				m_pix = nullptr;
			}
		}

		// Move constructor
		Raster (Raster&& rhs ) : m_width(rhs.m_width),
								 m_height(rhs.m_height)	{
			// Steal rhs's pixel array
			m_pix = rhs.m_pix;
			rhs.m_pix = nullptr;
			rhs.m_width = 0;
			rhs.m_height = 0;
		}

		// Move assignment operator
		Raster& operator = (Raster&& rhs)	{
			// Disallow self assignment (if you do stupid things like
			// x = std::move(x), this won't crash and burn)
			if( this != &rhs )	{
				delete [] m_pix;
				m_pix = nullptr;
				m_width = rhs.m_width;
				m_height = rhs.m_height;
				m_pix = rhs.m_pix;

				rhs.m_pix = nullptr;
				rhs.m_width = 0;
				rhs.m_height = 0;
			}
			return *this;
		}
		
		// Copy assignment operator
		Raster& operator = (const Raster& rhs)	{
			// Disallow self assignment
			if( this != &rhs )	{
				// Check if perchance, the size of the two images are the same
				// If they are, then we do not need to make a long ass trip to the heap
				if( (m_width != rhs.m_width) or (m_height != rhs.m_height) )	{
					delete [] m_pix;
					m_pix = nullptr;
					m_width = rhs.m_width;
					m_height = rhs.m_height;
					if ( (m_width * m_height) != 0 )	{
						try	{
							m_pix = new PIXEL[m_width * m_height];
						} catch( std::exception &e)	{
							std::cout << e.what() << std::endl;
							delete [] m_pix;
							m_pix = nullptr;
							m_width = 0;
							m_height = 0;
						}
					}
				}
				if( m_pix != nullptr )	{
					std::memcpy( m_pix, rhs.m_pix, m_width * m_height * sizeof(PIXEL));
				}
			}
			return *this;	
		}

		uint32_t width()	{
			return m_width;
		}
		
		uint32_t height()	{
			return m_height;
		}
		const PIXEL* data()	{
			return m_pix;
		}
	private:
		uint32_t m_width;
		uint32_t m_height;
		PIXEL *m_pix;
};

} /* end of namespace rafael*/
#endif
