////////////////////////////////////////////////////////////////////////////////
///
/// @file log.hpp
/// @brief Extremely basic debug logging functionality.
/// @author Zenon Parker
/// @date 2015
///
////////////////////////////////////////////////////////////////////////////////

#ifndef LOG_HPP
#define LOG_HPP

#ifdef VERBOSE
#define DEBUG(X) std::cout << X << std::endl;
#else
#define DEBUG(X) ;
#endif // VERBOSE

#endif // LOG_HPP

