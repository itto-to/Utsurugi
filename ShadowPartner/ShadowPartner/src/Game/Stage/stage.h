#ifndef _GAME_STAGE_STAGE_H_
#define _GAME_STAGE_STAGE_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "tile.h"
#include "../../Base/2D/camera.h"
#include "../../Base/2D/sprite.h"
#include "../Application/application.h"
#include "../../Base/Element/component.h"
#include "../../Base/Debug/debugger.h"

#include "../../Base/Physics/physics.h"

//==========================================================
// �}�N��
//==========================================================
#define STAGE_DATA "stage_file.dat"
#define TILE_PICTURE "Resources/Texture/Tile/GroundTiles.png"
#define CELL_VERTICAL (20)	//�i���j
#define CELL_HORIZONTAL (15)//�i���j
#define FILE_CHAR_BUFFER (32)//�i���j

namespace shadowpartner
{
	enum StageNumber
	{
		kStage1_1 = 0,
		kStage1_2,
		kStage1_3,
	};

	//==========================================================
	// �X�e�[�W�N���X
	//==========================================================


	class Stage :public Component
	{
	public:
		Stage(StageNumber stageno,GameObject &game_object);
		void LoadStageData (int stageno);
		~Stage();

	protected:
		void Draw();

	private:
		char file_tileno[64];
		char file_tilepass[64];
		unsigned devide_horizontal;
		unsigned devide_vertical;
		unsigned cell_horizontal;
		unsigned cell_vertical;
		Tile **tiles_;
		friend class CornerCandidates;
		// variables
		physics::TileMapCollider *tilemap_collider;
		bool *collision_exist;
		// methods

	};

}

#endif