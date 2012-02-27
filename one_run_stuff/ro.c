#include <stdio.h>

int main()
{
	for(int x0=0; x0<2; ++x0)
	{
		for(int x1=0; x1<2; ++x1)
		{
			for(int x2=0; x2<2; ++x2)
			{
				for(int x3=0; x3<2; ++x3)
				{
					printf("%d %d %d %d | %d | %d | %d\n", x0, x1, x2, x3, !(((x0||x1)&&x3)&&(!((x0||x1)&&x2))&&((!((x0||x1)&&x2))&&x3)), !((x0&&(!x2)&&x3) || ((!x0)&&x1&&(!x2)&&x3)) , (((!x0)||x2||(!x3))&&(x0||(!x1)||x2||(!x3))) )   ;
				}
			}
		}
	}
	return 0;
}
