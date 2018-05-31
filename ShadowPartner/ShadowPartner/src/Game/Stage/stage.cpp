#include "stage.h"
#include <stdio.h>

namespace shadowpartner
{
	Stage::Stage(int vertical, int horizontal)
	{
		tiles_ = new Tile *[vertical];
		for (int y = 0; y <= vertical; y++)
			for (int x = 0; x < horizontal; x++)
			{

			}

	}
}