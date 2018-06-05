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
				tiles_[x] =new Tile("Resources/Tiles/053-Wall01.png",5);
				//tiles_[x]->transform_->position_ = Vector2(0.0f, -100.0f - float(i * 50));

				// タイルサイズ
				tiles_[x]->sprite->SetSize(Vector2(
				DEFAULT_SCREEN_WIDTH/ cell_horizontal, 
				DEFAULT_SCREEN_HEIGHT/ cell_vertical
				));
				tiles_[x]->sprite->transform_->position_ = Vector2(
					DEFAULT_SCREEN_WIDTH / cell_horizontal*x,
					DEFAULT_SCREEN_HEIGHT / cell_vertical*y);
				AddComponent(tiles_[x]->sprite);
			}
		}

	}

	void Stage::LoadStageData(int stageno)
	{
		int compare;
		errno_t err;

		FILE *fp;
		err = fopen_s(&fp,STAGE_DATA, "r");	// ファイルを開く

		if (err == 0)
		{
			printf("The file 'stage_file.dat' was opened\n");
		}
		else
		{
			printf("The file 'stage_file.dat' was not opened\n");
		}
		
		//fseek(fp, 0, SEEK_SET);	//	ファイルの始まりからシーク
		do
		{
			fscanf_s(fp, "Stage%d", &compare);

		} while (stageno != compare);
		fscanf_s(fp, "%d", &devide_horizontal);
		fscanf_s(fp, "%d", &devide_vertical);
		fscanf_s(fp, "%d", &cell_horizontal);
		fscanf_s(fp, "%d", &cell_vertical);


		fclose(fp);							// ファイル操作終了

	}

	Stage::~Stage()
	{
		delete[] * tiles_;
		delete[] tiles_;
	}

}