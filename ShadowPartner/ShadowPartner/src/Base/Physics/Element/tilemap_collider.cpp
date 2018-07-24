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
	// �֊s�ǐ՗p�\����
	//**********************************************************
	struct ContourTrackingTemp
	{
		bool isChecked;		// �����ς�
		bool isCollider;	// �R���C�_�[������H
		int label;			// �̈�̃��x���B-1�͔w�i

		ContourTrackingTemp()
			:isChecked(false)
			, isCollider(false)
			, label(-1)
		{}
	};


	// �R���X�g���N�^
	TileMapCollider::TileMapCollider(const TileMapInitializer &ini)
	{
		size_ = Vector2(ini.width_, ini.height_);

		shape_ = PhysicsShape::kBox;

		// �^�C���}�b�v�R���C�_�[��body
		b2BodyDef tilemap_body_def;

		tilemap_body_def.type = b2_staticBody;

		tilemap_body_def.position.Set(ini.pos_.x, ini.pos_.y);

		body_ = PhysicsWorld::CreateBody(this, &tilemap_body_def);
		body_->SetUserData((void *)this);

		int current = 0;

		// �֊s�ǐ՗p�̃f�[�^�z��̐���
		ContourTrackingTemp *ctt = new ContourTrackingTemp[ini.x_lenght_ * ini.y_lenght_];

		for (int y = 0;y < ini.y_lenght_;++y)
		{
			for (int x = 0;x < ini.x_lenght_;++x)
			{
				ctt[y * ini.x_lenght_ + x].isCollider = ini.collision_exist[y * ini.x_lenght_ + x];
			}
		}

		int start;	// �֊s�ǐՂ̃X�^�[�g�n�_
		while (-1 != (start = RasterScan(current, ctt, ini.x_lenght_ * ini.y_lenght_)))
		{
			ContourTracking(start, ctt, ini.x_lenght_, ini.y_lenght_);

			current = start + 1;
		}

		delete[] ctt;

		//Vector2 offset = Vector2(-ini.width_ * ((float)ini.x_lenght_ / 2.0f - 0.5f), ini.height_ * ((float)ini.y_lenght_ / 2.0f - 0.5f));

		//for (int y = 0;y < ini.y_lenght_;++y, offset.y -= ini.height_)
		//{
		//	// �I�t�Z�b�g��X���W�̈ʒu�����͂��ɖ߂�
		//	offset.x = -ini.width_ * ((float)ini.x_lenght_ / 2.0f - 0.5f);

		//	for (int x = 0;x < ini.x_lenght_;++x, offset.x += ini.width_)
		//	{
		//		if (ini.collision_exist[y * ini.x_lenght_ + x])
		//		{
		//			b2PolygonShape box;
		//			b2FixtureDef tilemap_fixture_def;

		//			box.SetAsBox(ini.width_ / 2.0f, ini.height_ / 2.0f, b2Vec2(offset.x, offset.y), 0.0f);

		//			tilemap_fixture_def.shape = &box;

		//			tilemap_fixture_def.density = ini.density_;
		//			tilemap_fixture_def.friction = ini.friction_;

		//			body_->CreateFixture(&tilemap_fixture_def);
		//		}
		//	}
		//}
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

	//==========================================================
	// �T�v  :���X�^�[�X�L�����ŃR���C�_�[���������^�C����T���܂�
	// �߂�l:�������^�C���̃C���f�b�N�X
	// ����  :
	//  start   :
	//  ctt     :
	//  tile_max:
	//==========================================================
	int TileMapCollider::RasterScan(int start, ContourTrackingTemp *ctt, int tile_max)
	{
		int current = start;

		while (current < tile_max)
		{
			if (!ctt[current].isChecked && ctt[current].isCollider)
			{
				// �܂��R���C�_�[������Ă��Ȃ��^�C����T��
				return current;
			}

			ctt[current].isChecked = true;

			++current;
		}

		return -1;
	}

	//==========================================================
	// �T�v  :�֊s�ǐՂ��s���܂��B
	// ����  :
	//  start   :���X�^�[�X�L�����Ō������֊s�̍ŏ��ƂȂ�_
	//  ctt     :�֊s�ǐ՗p�̃f�[�^�z��
	//  x_lenght:x�������̉�f��
	//  y_lenght:y�������̉�f��
	//  is_outer:�ǐՂ���֊s�͊O�֊s���H
	//==========================================================
	void TileMapCollider::ContourTracking
		(
			int start, ContourTrackingTemp *ctt,
			int x_length, int y_length, bool is_outer
			)
	{
		std::vector<int> chain_list; // 
		int entry_direction = 3;	// �i������
		int check_direction;

		int x = start % x_length, y = start / x_length;
		int cx = x, cy = y;	// check x y

		// �֊s�ǐ�
		do
		{
			check_direction = (entry_direction + 4 + ((is_outer) ? 1 : -1)) % 4;

			// 2�T�ڈȍ~�p�ɑO��`�F�b�N��ʂ����_��x,y��ݒ肷��
			x = cx;
			y = cy;

			ctt[y * x_length + x].isChecked = true;

			// �i����������_�ɊO�֊s�Ȃ甽���v���A���֊s�Ȃ玞�v����4�ߖT��T������
			for (int i = 0;i < 4;++i)
			{
				switch (check_direction)
				{
				case 0: {cy = y + 1;}break;
				case 1: {cx = x + 1;}break;
				case 2: {cy = y - 1;}break;
				case 3: {cx = x - 1;}break;
				default:
					break;
				}

				if (cx == -1 || cx == x_length)
				{
					cx = x;
					check_direction = (check_direction + 4 + ((is_outer) ? 1 : -1)) % 4;
					continue;
				}
				else if (cy == -1 || cy == y_length)
				{
					cy = y;
					check_direction = (check_direction + 4 + ((is_outer) ? 1 : -1)) % 4;
					continue;
				}

				if (ctt[cy * x_length + cx].isCollider)
				{
					// �`�F�C�����X�g�ɐi��������ǉ�
					chain_list.push_back(check_direction);
					break;
				}

				if (i == 3)
				{
					cx = x;
					cy = y;
				}

				check_direction = (check_direction + 4 + ((is_outer) ? 1 : -1)) % 4;
				cx = x;
				cy = y;
			}

			entry_direction = (check_direction + 2) % 4;

		} while ((y * x_length + x != start) || !ctt[cy * x_length + cx].isChecked);

		if (chain_list.size() > 0)
			chain_list.pop_back();

		CreatePolygonOutLineCollider(start, chain_list, is_outer, x_length, y_length);
	}

	// �R���W�����̒��_���^�C���̒��S���猩�Ăǂ̈ʒu�ɂ���̂�
	enum TileCollisionPoint
	{
		kUpperLeft,
		kUpperRight,
		kLowerLeft,
		kLowerRight,
	};

	//==========================================================
	// �T�v  :�֊s�ǐՂ̌��ʂ���ɗ֊s�ɃG�b�W�R���C�_�[��ǉ����Ă����܂��B
	// ����  :
	//  start     :���X�^�[�X�L�����Ō������֊s�̍ŏ��ƂȂ�_
	//  chain_list:�ǐՂ����ۂ̐i�������̃��X�g
	//  is_outer  :�ǐՂ����֊s�͊O�֊s���H
	//==========================================================
	void TileMapCollider::CreatePolygonOutLineCollider
		(int start, std::vector<int> chain_list, bool is_outer, int x_length, int y_length)
	{
		std::vector<b2Vec2> points;

		Vector2 upper_left_point = Vector2(-size_.x * ((float)x_length / 2.0f - 0.5f), size_.y * ((float)y_length / 2.0f - 0.5f));

		Vector2 p0, p1;	// �G�b�W�̗��[�̓_

		// 4�ߖT�ɗאڂ����^�C�����Ȃ��ꍇ
		if (chain_list.size() == 0)
		{
			p0 = upper_left_point + Vector2((start % x_length) * size_.x - size_.x / 2.0f, -(start / x_length) * size_.y + size_.y / 2.0f);

			points.push_back(p0);

			p0 += Vector2(size_.x, 0.0f);
			points.push_back(p0);
			p0 += Vector2(0.0f, -size_.y);
			points.push_back(p0);
			p0 += Vector2(-size_.x, 0.0f);
			points.push_back(p0);
		}
		else
		{
			TileCollisionPoint currentPoint = TileCollisionPoint::kUpperLeft;

			int start_tile = start;		// �G�b�W�̎n�[�̃^�C��

			int current_chain = chain_list[0];
			int old_chain = -10;

			p1 = upper_left_point + Vector2((start_tile % x_length * size_.x) - size_.x / 2.0f, -(start_tile / x_length * size_.y) + size_.y / 2.0f);

			// points�ɃG�b�W�̒��_��ǉ����Ă���
			for (int i = 0;i < chain_list.size() - 1;++i)
			{
				int length = 1;

				while (i < chain_list.size() - 1)
				{
					if (current_chain == chain_list[i + 1])
					{
						++i;
						++length;
						continue;
					}
					break;
				}

				int end_tile;

				p0 = p1;

				switch (current_chain)
				{
				case 0:
				{
					if (old_chain == 2)
						p0.x -= size_.x;

					p1.x = p0.x;	// �c�̈ړ��Ȃ̂�x���W�ɂ͕ω��Ȃ�

					if (i + 1 >= chain_list.size())
					{
						// ���Ԃ�0�ŏI��邱�Ƃ͂Ȃ�
						if (currentPoint == TileCollisionPoint::kLowerLeft || currentPoint == TileCollisionPoint::kLowerRight)
						{
							p1.y = p0.y - (length)* size_.y;
						}
						else
						{
							p1.y = p0.y - (length + 1) * size_.y;
						}
					}
					else if (currentPoint == TileCollisionPoint::kUpperLeft)
					{
						if (chain_list[i + 1] == 3)
						{
							p1.y = p0.y - (length)* size_.y;
							// currentPoint�͂��̂܂�
						}
						else
						{
							p1.y = p0.y - (length + 1) * size_.y;
							currentPoint = TileCollisionPoint::kLowerLeft;
						}
					}
					else if (currentPoint == TileCollisionPoint::kUpperRight)
					{
						if (chain_list[i + 1] == 1)
						{
							p1.y = p0.y - (length)* size_.y;
							// currentPoint�͂��̂܂�
						}
						else
						{
							if (old_chain == 2)
							{
								currentPoint = TileCollisionPoint::kUpperLeft;
								p1.y = p0.y - (length) * size_.y;
							}
							else
							{
								currentPoint = TileCollisionPoint::kLowerRight;
								p1.y = p0.y - (length + 1) * size_.y;
							}
						}
					}
					else if (currentPoint == TileCollisionPoint::kLowerLeft)
					{
						if (chain_list[i + 1] == 3)
						{
							p1.y = p0.y - (length - 1)* size_.y;
							currentPoint = TileCollisionPoint::kUpperLeft;
						}
						else
						{
							p1.y = p0.y - (length)* size_.y;
							// currentPoint�͂��̂܂�
						}
					}
					else if (currentPoint == TileCollisionPoint::kLowerRight)
					{
						if (chain_list[i + 1] == 1)
						{
							p1.y = p0.y - (length - 1)* size_.y;
							currentPoint = TileCollisionPoint::kUpperRight;
						}
						else
						{
							p1.y = p0.y - (length)* size_.y;
							// currentPoint�͂��̂܂�
						}
					}

					end_tile = start_tile + length * x_length;
				}
				break;
				case 1:
				{
					if (old_chain == 3)
						p0.y -= size_.y;

					p1.y = p0.y;	// ���̈ړ��Ȃ̂�x���W�ɂ͕ω��Ȃ�

					if (i + 1 >= chain_list.size())
					{
						// ���Ԃ�1�ŏI��邱�Ƃ͂Ȃ�

						if (currentPoint == TileCollisionPoint::kUpperRight || currentPoint == TileCollisionPoint::kLowerRight)
						{
							p1.x = p0.x + (length)* size_.x;
						}
						else
						{
							p1.x = p0.x + (length + 1) * size_.x;
						}
					}
					else if (currentPoint == TileCollisionPoint::kUpperLeft)
					{
						if (chain_list[i + 1] == 2)
						{
							p1.x = p0.x + (length)* size_.x;
							// currentPoint�͂��̂܂�
						}
						else
						{
							if (old_chain == 3)
							{
								currentPoint = TileCollisionPoint::kLowerLeft;
								p1.x = p0.x + (length) * size_.x;
							}
							else
							{
								currentPoint = TileCollisionPoint::kUpperRight;
								p1.x = p0.x + (length + 1) * size_.x;
							}
						}
					}
					else if (currentPoint == TileCollisionPoint::kUpperRight)
					{
						if (chain_list[i + 1] == 2)
						{
							p1.x = p0.x + (length - 1)* size_.x;
							currentPoint = TileCollisionPoint::kUpperRight;
						}
						else
						{
							p1.x = p0.x + (length)* size_.x;
							// currentPoint�͂��̂܂�
						}
					}
					else if (currentPoint == TileCollisionPoint::kLowerLeft)
					{
						if (chain_list[i + 1] == 0)
						{
							p1.x = p0.x + (length)* size_.x;
							// currentPoint�͂��̂܂�
						}
						else
						{
							p1.x = p0.x + (length + 1)* size_.x;
							currentPoint = TileCollisionPoint::kLowerRight;
						}
					}
					else if (currentPoint == TileCollisionPoint::kLowerRight)
					{
						if (chain_list[i + 1] == 0)
						{
							p1.x = p0.x + (length - 1)* size_.x;
							currentPoint = TileCollisionPoint::kLowerLeft;
						}
						else
						{
							p1.x = p0.x + (length)* size_.x;
							// currentPoint�͂��̂܂�
						}
					}
					end_tile = start_tile + length;
				}
				break;
				case 2:
				{
					if (old_chain == 0)
						p0.x += size_.x;

					p1.x = p0.x;	// �c�̈ړ��Ȃ̂�x���W�ɂ͕ω��Ȃ�

					if (i + 1 >= chain_list.size())
					{
						if (currentPoint == TileCollisionPoint::kUpperLeft || currentPoint == TileCollisionPoint::kUpperRight)
						{
							p1.y = p0.y + (length)* size_.y;
						}
						else
						{
							p1.y = p0.y + (length + 1) * size_.y;
						}
					}
					else if (currentPoint == TileCollisionPoint::kUpperLeft)
					{
						if (chain_list[i + 1] == 3)
						{
							p1.y = p0.y + (length - 1)* size_.y;
							currentPoint = TileCollisionPoint::kLowerLeft;
						}
						else
						{
							p1.y = p0.y + (length)* size_.y;
							// currentPoint�͂��̂܂�
						}
					}
					else if (currentPoint == TileCollisionPoint::kUpperRight)
					{
						if (chain_list[i + 1] == 1)
						{
							p1.y = p0.y + (length - 1)* size_.y;
							currentPoint = kLowerRight;
						}
						else
						{
							p1.y = p0.y + (length)* size_.y;
							// currentPoint�͂��̂܂�
						}
					}
					else if (currentPoint == TileCollisionPoint::kLowerLeft)
					{
						if (chain_list[i + 1] == 3)
						{
							p1.y = p0.y + (length)* size_.y;
							// currentPoint�͂��̂܂�
						}
						else
						{
							if (old_chain == 0)
							{
								currentPoint = TileCollisionPoint::kLowerRight;
								p1.y = p0.y + (length)* size_.y;
							}
							else
							{
								currentPoint = TileCollisionPoint::kUpperLeft;
								p1.y = p0.y + (length + 1)* size_.y;
							}
						}
					}
					else if (currentPoint == TileCollisionPoint::kLowerRight)
					{
						if (chain_list[i + 1] == 1)
						{
							p1.y = p0.y + (length)* size_.y;
							// currentPoint�͂��̂܂�
						}
						else
						{
							p1.y = p0.y + (length + 1)* size_.y;
							currentPoint = TileCollisionPoint::kUpperRight;
						}
					}

					end_tile = start_tile - length * x_length;
				}
				break;
				case 3:
				{
					if (old_chain == 1)
						p0.y += size_.y;

					p1.y = p0.y;	// ���̈ړ��Ȃ̂�x���W�ɂ͕ω��Ȃ�

					if (i + 1 >= chain_list.size())
					{
						p1.x = p0.x - (length + 1) * size_.x;

						if (currentPoint == TileCollisionPoint::kUpperLeft || currentPoint == TileCollisionPoint::kLowerLeft)
						{
							p1.x = p0.x - (length)* size_.x;
						}
						else
						{
							p1.x = p0.x - (length + 1) * size_.x;
						}
					}
					else if (currentPoint == TileCollisionPoint::kUpperLeft)
					{
						if (chain_list[i + 1] == 2)
						{
							p1.x = p0.x - (length - 1)* size_.x;
							currentPoint = TileCollisionPoint::kUpperRight;
						}
						else
						{
							p1.x = p0.x - (length)* size_.x;
							// currentPoint�͂��̂܂�
						}
					}
					else if (currentPoint == TileCollisionPoint::kUpperRight)
					{
						if (chain_list[i + 1] == 2)
						{
							p1.x = p0.x - (length)* size_.x;
							// currentPoint�͂��̂܂�
						}
						else
						{
							p1.x = p0.x - (length + 1)* size_.x;
							currentPoint = TileCollisionPoint::kUpperLeft;
						}
					}
					else if (currentPoint == TileCollisionPoint::kLowerLeft)
					{
						if (chain_list[i + 1] == 0)
						{
							p1.x = p0.x - (length - 1)* size_.x;
							currentPoint = TileCollisionPoint::kLowerRight;
						}
						else
						{
							p1.x = p0.x - (length)* size_.x;
							// currentPoint�͂��̂܂�
						}
					}
					else if (currentPoint == TileCollisionPoint::kLowerRight)
					{
						if (chain_list[i + 1] == 0)
						{
							p1.x = p0.x - (length)* size_.x;
							//currentPoint�͂��̂܂�
						}
						else
						{
							if (old_chain == 1)
							{
								currentPoint = TileCollisionPoint::kUpperRight;
								p1.x = p0.x - (length)* size_.x;
							}
							else
							{
								currentPoint = TileCollisionPoint::kLowerLeft;
								p1.x = p0.x - (length + 1)* size_.x;
							}
						}
					}

					end_tile = start_tile - length;
				}
				break;
				default:
					break;
				}

				if (start_tile == start || abs(current_chain - old_chain) == 2)
					points.push_back(p0);

				points.push_back(p1);

				if (i + 1 >= chain_list.size())
					break;

				old_chain = current_chain;	// �O�̃`�F�[����ێ�����
				current_chain = chain_list[i + 1];

				start_tile = end_tile;
			}
		}

		if (b2DistanceSquared(points[0], points[points.size() - 1]) < 0.01f)
		{
			points.pop_back();
		}

		b2ChainShape chain;
		chain.CreateLoop(points.data(), points.size());

		b2FixtureDef fixture_def;
		fixture_def.shape = &chain;

		fixture_def.density = 0.0f;
		fixture_def.friction = 0.6f;

		body_->CreateFixture(&fixture_def);
	}

}
