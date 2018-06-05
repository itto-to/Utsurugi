#include "stage.h"
#include <stdio.h>

namespace shadowpartner
{
	Stage::Stage(StageNumber stageno)
	{
		LoadStageData(stageno);
		tiles_ = new Tile *[cell_vertical];
		for (int y = 0; y <= cell_vertical; y++)
		{

			for (int x = 0; x < cell_horizontal; x++)
			{
				tiles_[x] =new Tile("053-Wall01.png",5);
				//tiles_[x]->transform_->position_ = Vector2(0.0f, -100.0f - float(i * 50));

				// �^�C���T�C�Y
				tiles_[y][x].sprite.SetSize(Vector2(
				float(DEFAULT_SCREEN_WIDTH/ cell_horizontal), float(DEFAULT_SCREEN_HEIGHT/ cell_vertical)
				));
				AddComponent(&(tiles_[y][x].sprite));
			}
		}

	}

	void Stage::LoadStageData(StageNumber stageno)
	{
		int compare;

		FILE *fp;
		fopen_s(&fp,STAGE_DATA, "r");	// �t�@�C�����J��

		if (fp == NULL)
		{
			printf("\n%s �t�@�C���f�[�^�擾���s...\n", STAGE_DATA);
			return;
		}

		fseek(fp, 0, SEEK_SET);	//	�t�@�C���̎n�܂肩��V�[�N

		do
		{
			fscanf_s(fp, "Stage%d", &compare);

		} while (stageno != compare);
		fscanf_s(fp, "%d", &devide_horizontal);
		fscanf_s(fp, "%d", &devide_vertical);
		fscanf_s(fp, "%d", &cell_horizontal);
		fscanf_s(fp, "%d", &cell_vertical);


		fclose(fp);							// �t�@�C������I��

	}

	Stage::~Stage()
	{
		delete[]tiles_;
	}

}