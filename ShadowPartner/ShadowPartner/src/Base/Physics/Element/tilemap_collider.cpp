//==========================================================
// �T�v  :��`�̓����蔻��
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "tilemap_collider.h"
#include "../World/physics_world.h"

namespace physics
{
	//**********************************************************
	// �}�N��
	//**********************************************************

	//**********************************************************
	// �萔
	//**********************************************************

	// �R���X�g���N�^
	TileMapCollider::TileMapCollider(const TileMapInitializer &ini)
	{
		shape_ = PhysicsShape::kBox;

		b2BodyDef tilemap_body_def;

		tilemap_body_def.type = b2_staticBody;

		tilemap_body_def.position.Set(ini.pos_.x, ini.pos_.y);

		body_ = PhysicsWorld::CreateBody(this, &tilemap_body_def);
		body_->SetUserData((void *)this);

		Vector2 offset = Vector2(ini.pos_.x - ini.width_ * ((float)ini.x_lenght_ / 2.0f - 0.5f),ini.pos_.y + ini.height_ * ((float)ini.y_lenght_ / 2.0f -0.5f));

		for (int y = 0;y < ini.y_lenght_;++y,offset.y -= ini.height_)
		{
			// �I�t�Z�b�g��X���W�̈ʒu�����͂��ɖ߂�
			offset.x = ini.pos_.x - ini.width_ * ((float)ini.x_lenght_ / 2.0f - 0.5f);

			for (int x = 0;x < ini.x_lenght_;++x,offset.x += ini.width_)
			{
				if (ini.collision_exist[y * ini.x_lenght_ + x])
				{
					b2PolygonShape box;
					b2FixtureDef tilemap_fixture_def;

					box.SetAsBox(ini.width_ / 2.0f, ini.height_ / 2.0f, b2Vec2(offset.x, offset.y), 0.0f);

					tilemap_fixture_def.shape = &box;

					tilemap_fixture_def.density = ini.density_;
					tilemap_fixture_def.friction = ini.friction_;

					body_->CreateFixture(&tilemap_fixture_def);
				}
			}
		}
		delete[] ini.collision_exist;
		size_ = Vector2(ini.width_, ini.height_);
	}

	void TileMapCollider::Start()
	{

	}

	//==========================================================
	// �T�v  :TileMapCollider�̏c���̑傫�����L�^����size_��Ԃ��܂��B
	// �߂�l:�c���̑傫��
	//==========================================================
	Vector2 TileMapCollider::GetSize()
	{
		return size_;
	}
}
