#ifndef _GAME_STAGE_STAGE_H_
#define _GAME_STAGE_STAGE_H_

//**********************************************************
// インクルードファイル
//**********************************************************
#include "tile.h"
#include "../Application/application.h"
#include "../../Base/Element/component.h"



//==========================================================
// マクロ
//==========================================================
#define CELL_VERTICAL (20)	//（仮）
#define CELL_HORIZONTAL (15)//（仮）

namespace shadowpartner
{
	//==========================================================
	// ステージクラス
	//==========================================================


	class Stage :public Component
	{
	public:
		Stage(int cell_vertical,int cell_horizontal);
		//variables
		//bool stage_pass_[CELL_VERTICAL][CELL_HORIZONTAL];

		//methods
	private:
		Tile **tiles_;
		friend class CornerCandidates;
		// variables

		// methods

	};

}

#endif