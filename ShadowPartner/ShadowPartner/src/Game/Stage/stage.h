#ifndef _GAME_STAGE_STAGE_H_
#define _GAME_STAGE_STAGE_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "tile.h"
#include "../Application/application.h"
#include "../../Base/Element/component.h"



//==========================================================
// �}�N��
//==========================================================
#define CELL_VERTICAL (20)	//�i���j
#define CELL_HORIZONTAL (15)//�i���j

namespace shadowpartner
{
	//==========================================================
	// �X�e�[�W�N���X
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