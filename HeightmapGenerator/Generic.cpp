#include "Core.h"
namespace Heightmap
{
	inline int Generic::iMod(int quo, int div)
	{
		int mod = quo % div;
		return (mod < 0 ? mod + div : mod);
	}

}
