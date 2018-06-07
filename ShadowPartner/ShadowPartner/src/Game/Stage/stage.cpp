#include "stage.h"
#include <stdio.h>

namespace shadowpartner
{
	Stage::Stage(StageNumber stageno)
	{

		LoadStageData(stageno);

		tiles_ = new Tile *[cell_vertical * cell_horizontal];

		errno_t err;
		FILE *fp;
		err = fopen_s(&fp, TILE_DATA, "r");	// ファイルを開く
		if (err == 0)
		{
			printf("The file 'test_no.csv' was opened\n");
		}
		else
		{
			printf("The file 'test_no.csv' was not opened\n");
		}

		for (int y = 0; y < cell_vertical; y++)
		{
			for (int x = 0; x < cell_horizontal; x++)
			{
				int tileno;
				fscanf_s(fp, "%d,", &tileno);

				//　MakeVertex
				tiles_[y * cell_horizontal + x] =new Tile(TILE_PICTURE, tileno, devide_horizontal, devide_vertical, cell_horizontal, cell_vertical);
			}
		}

		fclose(fp);							// ファイル操作終了

	}

	void Stage::Draw()
	{
		Vector3 world_pos = Vector3(transform_->GetWorldPosition(), 0.0f);
		Vector3 draw_pos = Vector3(world_pos.x, -world_pos.y, 0.0f) / Camera::main_->GetZoom();	// スクリーン上の描画位置.まずy軸の方向を変える
		Vector3 screen_center = Vector3(Application::Instance()->GetScreenWidth() / 2, Application::Instance()->GetScreenHeight() / 2, 0.0f);
		draw_pos += Vector3(Camera::main_->transform_->position_, 0.0f) + screen_center;

		screen_center = Vector3(transform_->position_,0.0f);

		float zoom = Camera::main_->GetZoom();
		//Vector2 world_scale = transform_->GetWorldScale();

		float x_size = DEFAULT_SCREEN_WIDTH / cell_horizontal / zoom;
		float y_size = DEFAULT_SCREEN_HEIGHT / cell_vertical / zoom;

		for (int y = 0; y < cell_vertical; y++)
		{
			for (int x = 0; x < cell_horizontal; x++)
			{
				Vector2 uv_offset = tiles_[y * cell_horizontal + x]->uv_offset_;
				Vector2 uv_size = tiles_[y * cell_horizontal + x]->uv_size_;

				//SetVertex
				float vertex_left= x*x_size;
				float vertex_right= vertex_left+ x_size;
				float vertex_up= y*y_size;
				float vertex_down= vertex_up+ y_size;
				tiles_[y * cell_horizontal + x]->vertices_[0].vertex_ = screen_center+Vector3(vertex_left, vertex_up, 0.0f);
				tiles_[y * cell_horizontal + x]->vertices_[1].vertex_ = screen_center+Vector3(vertex_right, vertex_up, 0.0f);
				tiles_[y * cell_horizontal + x]->vertices_[2].vertex_ = screen_center+Vector3(vertex_left, vertex_down, 0.0f);
				tiles_[y * cell_horizontal + x]->vertices_[3].vertex_ = screen_center+Vector3(vertex_right, vertex_down, 0.0f);

				tiles_[y * cell_horizontal + x]->vertices_[0].tex_coor_ = uv_offset;
				tiles_[y * cell_horizontal + x]->vertices_[1].tex_coor_ = uv_offset + Vector2(uv_size.x, 0.0f);
				tiles_[y * cell_horizontal + x]->vertices_[2].tex_coor_ = uv_offset + Vector2(0.0f, uv_size.y);
				tiles_[y * cell_horizontal + x]->vertices_[3].tex_coor_ = uv_offset + uv_size;

				
				tiles_[y * cell_horizontal + x]->texture_->DrawTriangleStrip(&(tiles_[y * cell_horizontal + x]->vertices_[0]));
				

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
		if (tiles_ != nullptr)
		{
			delete tiles_;

		}

	}

}