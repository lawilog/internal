#ifndef _RECTTEMPLATE_H_
#define _RECTTEMPLATE_H_

template<class T>
class Rect
{
	public:
		T left;
		T top;
		T width;
		T height;
		Rect(T _left, T _top, T _width, T _height) : left(_left), top(_top), width(_width), height(_height) {}
		
		T area();
};

#endif // _RECTTEMPLATE_H_
