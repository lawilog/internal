#ifndef _LW_BYTES2STR_
#define _LW_BYTES2STR_

#include "printf++.hpp"

namespace LW {

std::string bytes2str(double m)
{
	if(m < 1024) return strprintf("%u B", (unsigned)m);
	m /= 1024;
	if(m < 1024) return strprintf("%.1f KB", m);
	m /= 1024;
	if(m < 1024) return strprintf("%.1f MB", m);
	m /= 1024;
	if(m < 1024) return strprintf("%.1f GB", m);
	m /= 1024;
	if(m < 1024) return strprintf("%.1f TB", m);
	m /= 1024;
	if(m < 1024) return strprintf("%.1f PB", m);
	m /= 1024;
	return strprintf("%.1f EB", m);
}

}

#endif // _LW_BYTES2STR_
