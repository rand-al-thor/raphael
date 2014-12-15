#include "raster.h"
#include <gtest/gtest.h>
#include <utility>

typedef raphael::Raster<unsigned char> raster_t;

namespace	{

void check_empty_raster( raster_t &ras )	{
	ASSERT_EQ(ras.height(), 0);
	ASSERT_EQ(ras.width(),0);
	ASSERT_EQ(ras.data(), nullptr);
}

} /* end of anonymous namespace*/ 


TEST( Raster, CreateRaster )	{

	{
		raster_t myraster;
		check_empty_raster(myraster);
	}

	{
		raster_t myraster(100,0);
		check_empty_raster(myraster);
	}

	{
		raster_t myraster(0,100);
		check_empty_raster(myraster);
	}
}

TEST( Raster, CopyRaster )	{
	raster_t ras(100,100);
	raster_t copy(ras);

	ASSERT_EQ( ras.height(), copy.height() );
	ASSERT_EQ( ras.width(), copy.width() );

	const unsigned char* pix_ras = ras.data();
	const unsigned char* pix_copy = copy.data();

	for( int i = 0; i < (ras.height() * ras.width()); ++i)	{
		ASSERT_EQ( pix_ras[i], pix_copy[i] );
	}
}

TEST( Raster, MoveRaster )	{
	raster_t ras(100,100);
	raster_t copy( std::move(ras) );

	check_empty_raster( ras );

	ASSERT_EQ( copy.height(), 100 );
	ASSERT_EQ( copy.width(), 100); 
}

int main( int argc, char *argv[])	{
	::testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}
