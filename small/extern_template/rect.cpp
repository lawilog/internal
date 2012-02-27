#include "rect.h"

template<class T>
T Rect<T>::area()
{
	return (width * height);
}

template class Rect<int>;
