#include "d3dsamplewin.h"
#include "nativeappbase.h"

namespace Graphic
{
	NativeAppbase* CreateApplication()
	{
		return new D3DSampleWin;
	}
}