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
#define STAGE_DATA "stage_file.dat"
#define CELL_VERTICAL (20)	//（仮）
#define CELL_HORIZONTAL (15)//（仮）
#define FILE_CHAR_BUFFER (32)//（仮）

namespace shadowpartner
{
	enum StageNumber
	{
		kTest = 0,
	};

	//==========================================================
	// ステージクラス
	//==========================================================


	class Stage :public GameObject
	{
	public:
		Stage(StageNumber stageno);
		void LoadStageData (int stageno);
		~Stage();
		//methods
	private:
		unsigned devide_horizontal;
		unsigned devide_vertical;
		unsigned cell_horizontal;
		unsigned cell_vertical;
		Tile **tiles_;
		friend class CornerCandidates;
		// variables

		// methods

	};

}

#endif