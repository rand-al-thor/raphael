#ifndef _logger_h_
#define _logger_h_

#include <sstream>
#include <memory>
#include <chrono>
#include <ctime>
#include <cstdio>

namespace log	{

enum log_level	{
	log_ERROR,
	log_WARNING,
	log_NOTICE,
	log_INFO,
	log_DEBUG,
	log_DEBUG2,
	log_TRACE
};

const char *log_strings[] = { "ERROR: ", "WARNING: ", "NOTICE: ", "INFO: ",  "DEBUG: ", "DEBUG2: " ,"TRACE: " };

/*
	Policy to decide whether to print a log which has level: 'LEVEL' or
	not. Compare it to the value of 'MAX_LEVEL'. This decision is made at
	compile time.
*/
template < int LEVEL, int MAX_LEVEL >
struct VisibilityTrait	{
	enum	{
		value = (((LEVEL <= MAX_LEVEL) &&  (LEVEL >= 0))? 1 : 0)
	};
};

/*
	Internal implementation of the logger.
*/
template <int LEVEL, int VISIBILITY> struct logger_impl {};

/*	Template specialization in case of invisibility */
template <int LEVEL>
struct logger_impl<LEVEL, 0>	{
	logger_impl( const std::string &msg) {}	// Empty constructor which does nothing
	~logger_impl ()	{} // Empty destructor which does nothing
};

/*	Template specialization in case of visibility */
template <int LEVEL>
struct logger_impl <LEVEL, 1>	{
	public:
		logger_impl ( const std::string& msg )	{
			oss << log_strings[LEVEL] << msg << std::endl;
		}
		~logger_impl()	{
			std::fprintf(stdout, "%s", oss.str().c_str() );
			std::fflush(stdout);
		}
	private:
		std::ostringstream oss ;
};


/*
	The logger class. This class will be given a 'MAX_LEVEL' value
	compile time. Every time it is invoked, it will have a compile
	time value of desired log level. This class is merely a wrapper
	around the internal logger class
*/

template < int MAX_LEVEL >
struct logger	{
	public:
		// Constructor
		logger() {}

		// Delete the copy constructor and 
		// the copy assignment operator
		logger( const logger&rhs) = delete;
		void operator = (const logger& rhs) = delete;

		template < int LEVEL >
		void log(const std::string& msg )	{
			logger_impl < LEVEL, VisibilityTrait<LEVEL, MAX_LEVEL>::value > my_logger(msg);
		}
	private:
};

} /* end of namespace imgproc*/

#endif
