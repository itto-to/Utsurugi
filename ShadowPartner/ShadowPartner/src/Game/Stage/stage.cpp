#include "stage.h"
#include <stdio.h>

namespace shadowpartner
{
	Stage::Stage(StageNumber stageno,GameObject &game_object, char datatileno[], char datatilepass[])
	{

		LoadStageData(stageno);

		tiles_ = new Tile *[cell_vertical * cell_horizontal];

		errno_t err_no,err_pass;
		FILE *fp_no;
		FILE *fp_pass;

		err_no = fopen_s(&fp_no, datatileno, "r");	// ファイルを開く
		err_pass = fopen_s(&fp_pass, datatilepass, "r");	// ファイルを開く


		if (err_no == 0)
		{
			printf("The file 'test_no.csv' was opened\n");
		}
		else
		{
			printf("The file 'test_no.csv' was not opened\n");
		}

		if (fp_pass == 0)
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
				int tilepass;


				fscanf_s(fp_no, "%d,", &tileno);
				fscanf_s(fp_pass, "%d,", &tilepass);

				//　MakeVertex
				tiles_[y * cell_horizontal + x] =new Tile(TILE_PICTURE, tileno, devide_horizontal, devide_vertical, cell_horizontal, cell_vertical,game_object);

				// 通過不可のタイルだけコライダーを作る
				if (tilepass)
				{
					BoxInitializer box_init;
					box_init.width_ = DEFAULT_SCREEN_WIDTH / cell_horizontal /2.0f;
					box_init.height_ = DEFAULT_SCREEN_HEIGHT / cell_vertical / 2.0f;

					//PosCollider
					box_init.pos_= Vector2((x+0.5f)*box_init.width_, (y + 0.5f)*box_init.height_);					// BoxCollider座標

					tiles_[y * cell_horizontal + x]->box_collider_ = new BoxCollider(box_init);
					tiles_[y * cell_horizontal + x]->box_collider_->SetOffset(Vector2((x + 0.5f)*box_init.width_, (y + 0.5f)*box_init.height_));
					game_object.AddComponent(tiles_[y * cell_horizontal + x]->box_collider_);
				}
				else
				{
					tiles_[y * cell_horizontal + x]->box_collider_ = NULL;
				}

			}
		}

		fclose(fp_no);							// ファイル操作終了
		fclose(fp_pass);							// ファイル操作終了

	}

	void Stage::Draw()
	{
		Vector3 world_pos = Vector3(transform_->GetWorldPosition(), 0.0f);
		Vector3 draw_pos = Vector3(world_pos.x, -world_pos.y, 0.0f) / Camera::main_->GetZoom();	// スクリーン上の描画位置.まずy軸の方向を変える
		Vector3 screen_center = Vector3(Application::Instance()->GetScreenWidth() / 2, Application::Instance()->GetScreenHeight() / 2, 0.0f);
		draw_pos += screen_center - Vector3(Camera::main_->transform_->position_, 0.0f);

		float zoom = Camera::main_->GetZoom();
		//Vector2 world_scale = transform_->GetWorldScale();

		float x_size = DEFAULT_SCREEN_WIDTH / cell_horizontal / zoom;
		float y_size = DEFAULT_SCREEN_HEIGHT / cell_vertical / zoom;

		for (int y = 0; y < cell_vertical; y++)
		{
			for (int x = 0; x < cell_horizontal; x++)
			{
				// tile置かない場合
				if (!tiles_[y * cell_horizontal + x]->texture_)
					continue;

				Vector2 uv_offset = tiles_[y * cell_horizontal + x]->uv_offset_;
				Vector2 uv_size = tiles_[y * cell_horizontal + x]->uv_size_;

				//SetVertex
				float vertex_left=  (x - cell_horizontal / 2.0f)*x_size;
				float vertex_right= vertex_left+ x_size;
				float vertex_up= (y - cell_vertical / 2.0f)*y_size;
				float vertex_down= vertex_up+ y_size;

				// テクスチャ座標
				tiles_[y * cell_horizontal + x]->vertices_[0].tex_coor_ = uv_offset;
				tiles_[y * cell_horizontal + x]->vertices_[1].tex_coor_ = uv_offset + Vector2(uv_size.x, 0.0f);
				tiles_[y * cell_horizontal + x]->vertices_[2].tex_coor_ = uv_offset + Vector2(0.0f, uv_size.y);
				tiles_[y * cell_horizontal + x]->vertices_[3].tex_coor_ = uv_offset + uv_size;

				// vertex座標
				tiles_[y * cell_horizontal + x]->vertices_[0].vertex_ = draw_pos+Vector3(vertex_left, vertex_up, 0.0f);
				tiles_[y * cell_horizontal + x]->vertices_[1].vertex_ = draw_pos+Vector3(vertex_right, vertex_up, 0.0f);
				tiles_[y * cell_horizontal + x]->vertices_[2].vertex_ = draw_pos+Vector3(vertex_left, vertex_down, 0.0f);
				tiles_[y * cell_horizontal + x]->vertices_[3].vertex_ = draw_pos+Vector3(vertex_right, vertex_down, 0.0f);

				
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

#ifdef _DEBUG
		if (err == 0)
		{
			debug::Debug::Log("The file 'stage_file.dat' was opened\n");
		}
		else
		{
			debug::Debug::Log("The file 'stage_file.dat' was not opened\n");
		}
#endif

		fseek(fp, 0, SEEK_SET);	//	ファイルの始まりからシーク
		do
		{
			fscanf_s(fp, "Stage%d", &compare);

		} while (stageno != compare);
		fscanf_s(fp, "%d\n", &devide_horizontal);
		fscanf_s(fp, "%d\n", &devide_vertical);
		fscanf_s(fp, "%d\n", &cell_horizontal);
		fscanf_s(fp, "%d\n", &cell_vertical);

		//fscanf_s(fp, "%s", file_tileno);
		//fscanf_s(fp, "%s", file_tilepass);


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