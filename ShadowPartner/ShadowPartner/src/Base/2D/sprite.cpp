//==========================================================
// �T�v  :2D�I�u�W�F�N�g�̕`��p�N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#include "sprite.h"
#include "camera.h"
#include "../../Game/Application/application.h"

namespace shadowpartner
{
	//**********************************************************
	// �}�N��
	//**********************************************************

		//**********************************************************
		// �萔
		//**********************************************************

		// �R���X�g���N�^
	Sprite::Sprite(const char *file_name)
		:anchor_(Sprite::Anchor::kMiddleCenter)
		, offset_(Vector2::zero())
		, uv_offset_(Vector2::zero())
		, uv_size_(Vector2::one())
		, order_in_layer_(0)
		, flip_x_(false)
		, flip_y_(false)
		, is_square_(true)
	{
		texture_ = new Texture(file_name);

		MakeVertex();

		for (int i = 0;i < NUM_TEXTURE_VERTEX;++i)
		{
			custom_rhw_[i] = 1.0f;
		}
	}

	// �R�s�[�R���X�g���N�^
	Sprite::Sprite(const Sprite &copy)
	{
		*this = copy;
	}

	// �f�X�g���N�^
	Sprite::~Sprite()
	{
		if (texture_ != nullptr)
		{
			delete texture_;
		}
	}

	// �`�揈��
	void Sprite::Draw()
	{
		float zoom = Camera::main_->GetZoom();
		Vector2 world_scale = transform_->GetWorldScale();
		float width, height;
		width = texture_->GetWidth() * world_scale.x / zoom * PIXEL_PER_UNIT;
		height = texture_->GetHeight() * world_scale.y / zoom * PIXEL_PER_UNIT;

		Vector3 world_pos = (Vector3(transform_->GetWorldPosition(), 0.0f) + Vector3(offset_, 0.0f)) * PIXEL_PER_UNIT;

		switch (anchor_)
		{
		case shadowpartner::Sprite::kUpperRight:
			world_pos += Vector3(-width / 2.0f, -height / 2.0f, 0.0f);
			break;
		case shadowpartner::Sprite::kUpperCenter:
			world_pos += Vector3(0.0f, -height / 2.0f, 0.0f);
			break;
		case shadowpartner::Sprite::kUpperLeft:
			world_pos += Vector3(width / 2.0f, -height / 2.0f, 0.0f);
			break;
		case shadowpartner::Sprite::kMiddleRight:
			world_pos += Vector3(-width / 2.0f, 0.0f, 0.0f);
			break;
		case shadowpartner::Sprite::kMiddleCenter:
			break;
		case shadowpartner::Sprite::kMiddleLeft:
			world_pos += Vector3(width / 2.0f, 0.0f, 0.0f);
			break;
		case shadowpartner::Sprite::kLowerRight:
			world_pos += Vector3(-width / 2.0f, height / 2.0f, 0.0f);
			break;
		case shadowpartner::Sprite::kLowerCenter:
			world_pos += Vector3(0.0f, height / 2.0f, 0.0f);
			break;
		case shadowpartner::Sprite::kLowerLeft:
			world_pos += Vector3(width / 2.0f, height / 2.0f, 0.0f);
			break;
		case shadowpartner::Sprite::kAnchorCount:
			break;
		default:
			break;
		}

		Vector3 draw_pos = Vector3(world_pos.x, -world_pos.y, 0.0f) / Camera::main_->GetZoom();	// �X�N���[����̕`��ʒu.�܂�y���̕�����ς���
		Vector3 screen_center = Vector3(Application::Instance()->GetScreenWidth() / 2, Application::Instance()->GetScreenHeight() / 2, 0.0f);
		draw_pos += screen_center - Vector3(Camera::main_->transform_->position_, 0.0f) * PIXEL_PER_UNIT;

		SetVertex(draw_pos, width, height, transform_->GetWorldRotation());

		texture_->DrawTriangleStrip(&vertices_[0]);
	}

	//==========================================================
	// �T�v  :�X�v���C�g�̐F��ύX���܂��B
	// ����  :�ύX�������F�B
	//==========================================================
	void Sprite::SetColor(const D3DCOLOR &color)
	{
		for (int i = 0; i < NUM_TEXTURE_VERTEX;++i)
		{
			vertices_[i].diffuse_ = color;
		}
	}

	//==========================================================
	// �T�v  :Transform��scale����Ƃ����傫����Ԃ��܂��B
	// ����  :�Ȃ�
	//==========================================================
	Vector2 Sprite::Size()
	{
		return Vector2(texture_->GetWidth(), texture_->GetHeight());
	}

	//==========================================================
	// �T�v  :�`��̈ʒu���摜�̂ǂ̈ʒu����Ƃ���̂���ݒ肷��B
	// ����  :��Ƃ���Anchor
	//==========================================================
	void Sprite::SetAnchor(const Anchor &anchor)
	{
		anchor_ = anchor;
	}

	//==========================================================
	// �T�v  :�X�v���C�g�̕`��ʒu��position���炸�炷�������擾���܂��B
	// �߂�l:���炷��
	//==========================================================
	Sprite::Anchor Sprite::GetAnchor()
	{
		return anchor_;
	}

	//==========================================================
	// �T�v  :�X�v���C�g�̕`��ʒu��position���炸�炷������ݒ肵�܂��B
	// ����  :���炷��
	//==========================================================
	void Sprite::SetOffset(const Vector2 &offset)
	{
		offset_ = offset;
	}

	//==========================================================
	// �T�v  :�X�v���C�g�̕`��ʒu��position���炸�炷�������擾���܂��B
	// �߂�l:���炷��
	//==========================================================
	Vector2 Sprite::GetOffset()
	{
		return offset_;
	}

	//==========================================================
	// �T�v  :Transform��scale����Ƃ����傫�����w�肵�܂��B
	// ����  :�L�k�̊���
	//==========================================================
	void Sprite::SetSize(const Vector2 &size)
	{
		texture_->SetWidth(size.x);
		texture_->SetHeight(size.y);
	}

	//==========================================================
	// �T�v  :�e�N�X�`���[��uv���W�̍�����擾���܂��B
	// ����  :�Ȃ�
	//==========================================================
	Vector2 Sprite::UvOffset() const
	{
		return uv_offset_;
	}

	//==========================================================
	// �T�v  :�e�N�X�`���[��uv���W�̍����ݒ肵�܂��B
	// ����  :����̍��W
	//==========================================================
	void Sprite::SetUvOffset(const Vector2 &offset)
	{
		uv_offset_ = offset;
	}

	//==========================================================
	// �T�v  :uv�̑傫����ݒ肵�܂��B
	// ����  :�e�N�X�`���[��uv���W�̍��ォ��E���܂ł̃x�N�g��
	//==========================================================
	void Sprite::SetUvSize(const Vector2 &size)
	{
		uv_size_ = size;
	}

	//==========================================================
	// �T�v  :�`�揇��ݒ肵�܂��B��������������`�悵�܂��B
	// ����  :�`��̏���
	//==========================================================
	void Sprite::SetOrderInLayer(const int &layer)
	{
		order_in_layer_ = layer;
	}

	//==========================================================
	// �T�v  :���_���쐬���܂��B
	//==========================================================
	void Sprite::MakeVertex()
	{
		vertices_[0].rhw_ =
			vertices_[1].rhw_ =
			vertices_[2].rhw_ =
			vertices_[3].rhw_ = 1.0f;

		vertices_[0].diffuse_ =
			vertices_[1].diffuse_ =
			vertices_[2].diffuse_ =
			vertices_[3].diffuse_ = D3DCOLOR_RGBA(255, 255, 255, 255);

		float left, right, up, down;

		left = !flip_x_ ? 0.0f : 1.0f;
		right = 1.0f - left;
		up = !flip_y_ ? 0.0f : 1.0f;
		down = 1.0f - up;

		vertices_[0].tex_coor_ = Vector2(left, up);
		vertices_[1].tex_coor_ = Vector2(right, up);
		vertices_[2].tex_coor_ = Vector2(left, down);
		vertices_[3].tex_coor_ = Vector2(right, down);
	}

	//==========================================================
	// �T�v  :���_�̐ݒ���s���܂��B
	// ����  :
	//	center  :Sprite�̒��S
	//	width   :����
	//	height  :�c��
	//	rotition:��]
	//==========================================================
	void Sprite::SetVertex(const Vector3 &center, const float &width,
		const float &height, const float &rotation)
	{
		float rad = D3DXToRadian(rotation);

		if (is_square_)
		{
			float hw = width / 2.0f, hh = height / 2.0f;

			float xsin = hw * sinf(rad), xcos = hw * cosf(rad);
			float ysin = hh * sinf(rad), ycos = hh * cosf(rad);

			vertices_[0].vertex_ = center + Vector3(-xcos + ysin, -xsin - ycos, 0.0f);
			vertices_[1].vertex_ = center + Vector3(xcos + ysin, xsin - ycos, 0.0f);
			vertices_[2].vertex_ = center + Vector3(-xcos - ysin, -xsin + ycos, 0.0f);
			vertices_[3].vertex_ = center + Vector3(xcos - ysin, xsin + ycos, 0.0f);

			vertices_[0].rhw_ =
				vertices_[1].rhw_ =
				vertices_[2].rhw_ =
				vertices_[3].rhw_ = 1.0f;
		}
		else
		{
			float lx, ly;
			float c = cosf(rad), s = sinf(rad);

			Vector2 ws = transform_->GetWorldScale();

			for (int i = 0;i < NUM_TEXTURE_VERTEX;++i)
			{
				lx = custom_vertices_[i].x * PIXEL_PER_UNIT * ws.x;
				ly = -(custom_vertices_[i].y * PIXEL_PER_UNIT * ws.y);

				vertices_[i].vertex_ = center + Vector3(c * lx - s * ly, s * lx + c * ly, 0.0f);
			}

			vertices_[0].rhw_ = custom_rhw_[0];
			vertices_[1].rhw_ = custom_rhw_[1];
			vertices_[2].rhw_ = custom_rhw_[2];
			vertices_[3].rhw_ = custom_rhw_[3];
		}

		// �e�N�X�`���[���̕`��̈�̐ݒ�
		float left, right, up, down;

		left = !flip_x_ ? uv_offset_.x : uv_offset_.x + uv_size_.x;
		right = (uv_offset_.x * 2.0f + uv_size_.x) - left;
		up = !flip_y_ ? uv_offset_.y : uv_offset_.y + uv_size_.y;
		down = (uv_offset_.y * 2.0f + uv_size_.y) - up;

		vertices_[0].tex_coor_ = Vector2(left, up);
		vertices_[1].tex_coor_ = Vector2(right, up);
		vertices_[2].tex_coor_ = Vector2(left, down);
		vertices_[3].tex_coor_ = Vector2(right, down);
	}

	void Sprite::SetUvNormal()
	{
		vertices_[0].tex_coor_ = uv_offset_;
		vertices_[1].tex_coor_ = uv_offset_ + Vector2(uv_size_.x, 0.0f);
		vertices_[2].tex_coor_ = uv_offset_ + Vector2(0.0f, uv_size_.y);
		vertices_[3].tex_coor_ = uv_offset_ + uv_size_;
	}

	void Sprite::SetUvInvertX()
	{
		vertices_[0].tex_coor_ = uv_offset_ + Vector2(uv_size_.x, 0.0f);	// ����
		vertices_[1].tex_coor_ = uv_offset_;	// �E��
		vertices_[2].tex_coor_ = uv_offset_ + uv_size_; 	// ����
		vertices_[3].tex_coor_ = uv_offset_ + Vector2(0.0f, uv_size_.y);	// �E��
	}

	void Sprite::SetUvInvertY()
	{
		vertices_[0].tex_coor_ = uv_offset_ + Vector2(0.0f, uv_size_.y);
		vertices_[1].tex_coor_ = uv_offset_ + uv_size_;
		vertices_[2].tex_coor_ = uv_offset_;
		vertices_[3].tex_coor_ = uv_offset_ + Vector2(uv_size_.x, 0.0f);
	}

	void Sprite::SetUvInvertXY()
	{
		vertices_[0].tex_coor_ = uv_offset_ + uv_size_;
		vertices_[1].tex_coor_ = uv_offset_ + Vector2(0.0f, uv_size_.y);
		vertices_[2].tex_coor_ = uv_offset_ + Vector2(uv_size_.x, 0.0f);
		vertices_[3].tex_coor_ = uv_offset_;
	}


	void Sprite::SetFlipX(bool enable_flip)
	{
		flip_x_ = enable_flip;
	}


	void Sprite::SetFlipY(bool enable_flip)
	{
		flip_y_ = enable_flip;
	}

	bool Sprite::GetFlipX() const
	{
		return flip_x_;
	}

	bool Sprite::GetFlipY() const
	{
		return flip_y_;
	}

	void Sprite::SetAsTrapezoid(float height, float upper_base, float lower_base, Sprite::TrapezoidAxis trapezoid_axis)
	{
		float rhw = lower_base / upper_base;

		if (trapezoid_axis == Sprite::TrapezoidAxis::kYaxis)
		{
			custom_vertices_[0] = Vector2(-upper_base / 2.0f, height / 2.0f);
			custom_vertices_[1] = Vector2(upper_base / 2.0f, height / 2.0f);
			custom_vertices_[2] = Vector2(-lower_base / 2.0f, -height / 2.0f);
			custom_vertices_[3] = Vector2(lower_base / 2.0f, -height / 2.0f);

			custom_rhw_[0] = 1.0f;
			custom_rhw_[1] = 1.0f;
			custom_rhw_[2] = rhw;
			custom_rhw_[3] = rhw;
		}
		else
		{
			custom_vertices_[0] = Vector2(-height / 2.0f, upper_base / 2.0f);
			custom_vertices_[1] = Vector2(height / 2.0f, lower_base / 2.0f);
			custom_vertices_[2] = Vector2(-height / 2.0f, -upper_base / 2.0f);
			custom_vertices_[3] = Vector2(height / 2.0f, -lower_base / 2.0f);

			custom_rhw_[0] = 1.0f;
			custom_rhw_[1] = rhw;
			custom_rhw_[2] = 1.0f;
			custom_rhw_[3] = rhw;
		}

		is_square_ = false;
	}

	void Sprite::CustomShape(const Vector2 &p0, const Vector2 &p1, const Vector2 &p2, const Vector2 &p3)
	{
		custom_vertices_[0] = p0;
		custom_vertices_[1] = p1;
		custom_vertices_[2] = p2;
		custom_vertices_[3] = p3;

		custom_rhw_[0] = 1.0f;
		custom_rhw_[1] = 1.0f;
		custom_rhw_[2] = 1.0f;
		custom_rhw_[3] = 1.0f;

		is_square_ = false;
	}

	void Sprite::EnableSquare()
	{
		is_square_ = true;
	}
}
