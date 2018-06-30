#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止
#include "stage.h"
#include <stdio.h>

#include "../../Base/Debug/debugger.h"

using namespace physics;

#ifdef _DEBUG
using namespace debug;
#endif

namespace shadowpartner
{
	Stage::Stage(StageNumber stageno, GameObject &game_object)
	{

		LoadStageData(stageno);

		tiles_ = new Tile *[cell_vertical * cell_horizontal];

		errno_t err_no, err_pass;
		FILE *fp_no;
		FILE *fp_pass;

		err_no = fopen_s(&fp_no, file_tileno, "r");	// ファイルを開く
		err_pass = fopen_s(&fp_pass, file_tilepass, "r");	// ファイルを開く

#ifdef _DEBUG

		if (err_no == 0)
		{
			Debug::Log("The file 'test_no.csv' was opened\n");
		}
		else
		{
			Debug::Log("The file 'test_no.csv' was not opened\n");
		}

		if (fp_pass == 0)
		{
			Debug::Log("The file 'test_no.csv' was opened\n");
		}
		else
		{
			Debug::Log("The file 'test_no.csv' was not opened\n");
		}
#endif

		// TileMapColliderの設定
		TileMapInitializer tile_init;
		tile_init.pos_ = game_object.transform_->position_;
		tile_init.x_lenght_ = cell_horizontal;
		tile_init.y_lenght_ = cell_vertical;
		tile_init.friction_ = 0.0f;
		tile_init.width_ = (float)DEFAULT_SCREEN_WIDTH / cell_horizontal / (float)PIXEL_PER_UNIT;
		tile_init.height_ = (float)DEFAULT_SCREEN_HEIGHT / cell_vertical / (float)PIXEL_PER_UNIT;
		collision_exist = new bool[cell_horizontal * cell_vertical];

		for (int y = 0; y < cell_vertical; y++)
		{
			for (int x = 0; x < cell_horizontal; x++)
			{
				int tileno;
				int tilepass;


				fscanf_s(fp_no, "%d,", &tileno);
				fscanf_s(fp_pass, "%d,", &tilepass);

				//　MakeVertex
				tiles_[y * cell_horizontal + x] = new Tile(TILE_PICTURE, tileno, devide_horizontal, devide_vertical, cell_horizontal, cell_vertical, game_object);

				// 通過不可のタイルだけコライダーを作る
				if (tilepass)
				{
					collision_exist[y * cell_horizontal + x] = true;
				}
				else
				{
					collision_exist[y * cell_horizontal + x] = false;
				}
			}
		}

		fclose(fp_no);							// ファイル操作終了
		fclose(fp_pass);							// ファイル操作終了

		tile_init.collision_exist = collision_exist;
		tilemap_collider = new TileMapCollider(tile_init);
		game_object.AddComponent(tilemap_collider);
	}

	void Stage::Draw()
	{
		Vector3 world_pos = Vector3(transform_->GetWorldPosition(), 0.0f) * PIXEL_PER_UNIT;
		Vector3 draw_pos = Vector3(world_pos.x, -world_pos.y, 0.0f) / Camera::main_->GetZoom();	// スクリーン上の描画位置.まずy軸の方向を変える
		Vector3 screen_center = Vector3(Application::Instance()->GetScreenWidth() / 2, Application::Instance()->GetScreenHeight() / 2, 0.0f);
		draw_pos += screen_center - Vector3(Camera::main_->transform_->position_, 0.0f) * PIXEL_PER_UNIT;

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
				float vertex_left = (x - cell_horizontal / 2.0f)*x_size;
				float vertex_right = vertex_left + x_size;
				float vertex_up = (y - cell_vertical / 2.0f)*y_size;
				float vertex_down = vertex_up + y_size;

				// テクスチャ座標
				tiles_[y * cell_horizontal + x]->vertices_[0].tex_coor_ = uv_offset;
				tiles_[y * cell_horizontal + x]->vertices_[1].tex_coor_ = uv_offset + Vector2(uv_size.x, 0.0f);
				tiles_[y * cell_horizontal + x]->vertices_[2].tex_coor_ = uv_offset + Vector2(0.0f, uv_size.y);
				tiles_[y * cell_horizontal + x]->vertices_[3].tex_coor_ = uv_offset + uv_size;

				// vertex座標
				tiles_[y * cell_horizontal + x]->vertices_[0].vertex_ = draw_pos + Vector3(vertex_left, vertex_up, 0.0f);
				tiles_[y * cell_horizontal + x]->vertices_[1].vertex_ = draw_pos + Vector3(vertex_right, vertex_up, 0.0f);
				tiles_[y * cell_horizontal + x]->vertices_[2].vertex_ = draw_pos + Vector3(vertex_left, vertex_down, 0.0f);
				tiles_[y * cell_horizontal + x]->vertices_[3].vertex_ = draw_pos + Vector3(vertex_right, vertex_down, 0.0f);


				tiles_[y * cell_horizontal + x]->texture_->DrawTriangleStrip(&(tiles_[y * cell_horizontal + x]->vertices_[0]));


			}
		}
	}


	void Stage::LoadStageData(int stageno)
	{
		char text[64];
		int compare;
		errno_t err;

		FILE *fp;
		err = fopen_s(&fp, STAGE_DATA, "r");	// ファイルを開く

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
			fscanf(fp, "%s", text);
			if ((strcmp(text, "Stage")) == 0)
				fscanf(fp, "%d", &compare);

			//fscanf(fp, "Stage%d", &compare);

		} while (stageno != compare);
		fscanf(fp, "%d", &devide_horizontal);
		fscanf(fp, "%d", &devide_vertical);
		fscanf(fp, "%d", &cell_horizontal);
		fscanf(fp, "%d", &cell_vertical);

		fscanf(fp, "%s", file_tileno);
		fscanf(fp, "%s", file_tilepass);


		fclose(fp);							// ファイル操作終了

	}

	Stage::~Stage()
	{
		if (tiles_ != nullptr)
		{
			delete tiles_;
			tiles_ = nullptr;
		}

		if (collision_exist != nullptr)
		{
			delete[] collision_exist;
			collision_exist = nullptr;
		}
	}

}