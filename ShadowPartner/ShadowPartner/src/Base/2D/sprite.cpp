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
		:uv_offset_(Vector2::zero())
		,uv_size_(Vector2::one())
		,order_in_layer_(0)
	{
		texture_ = new Texture(file_name);

		MakeVertex();
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
		Vector3 world_pos = Vector3(transform_->GetWorldPosition(), 0.0f);
		Vector3 draw_pos = Vector3(world_pos.x,-world_pos.y,0.0f) / Camera::main_->GetZoom();	// �X�N���[����̕`��ʒu.�܂�y���̕�����ς���
		Vector3 screen_center = Vector3(Application::Instance()->GetScreenWidth() / 2, Application::Instance()->GetScreenHeight() / 2,0.0f);
		draw_pos += screen_center - Vector3(Camera::main_->transform_->position_, 0.0f);

		float zoom = Camera::main_->GetZoom();
		Vector2 world_scale = transform_->GetWorldScale();
		float width, height;
		width = texture_->GetWidth() * world_scale.x / zoom;
		height = texture_->GetHeight() * world_scale.y / zoom;

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
	// �T�v  :Transform��scale����Ƃ����傫�����w�肵�܂��B
	// ����  :�L�k�̊���
	//==========================================================
	void Sprite::SetSize(const Vector2 &size)
	{
		texture_->SetWidth(size.x);
		texture_->SetHeight(size.y);
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

		vertices_[0].tex_coor_ = Vector2::zero();
		vertices_[1].tex_coor_ = Vector2(1.0f,0.0f);
		vertices_[2].tex_coor_ = Vector2(0.0f,1.0f);
		vertices_[3].tex_coor_ = Vector2::one();
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
		float hw = width / 2.0f, hh = height / 2.0f;

		float rad = D3DXToRadian(rotation);

		float xsin = hw * sinf(rad), xcos = hw * cosf(rad);
		float ysin = hh * sinf(rad), ycos = hh * cosf(rad);

		vertices_[0].vertex_ = center + Vector3(-xcos + ysin, -xsin - ycos,0.0f);
		vertices_[1].vertex_ = center + Vector3(xcos + ysin, xsin - ycos,0.0f);
		vertices_[2].vertex_ = center + Vector3(-xcos - ysin, -xsin + ycos,0.0f);
		vertices_[3].vertex_ = center + Vector3(xcos - ysin, xsin + ycos,0.0f);

		vertices_[0].tex_coor_ = uv_offset_;
		vertices_[1].tex_coor_ = uv_offset_ + Vector2(uv_size_.x, 0.0f);
		vertices_[2].tex_coor_ = uv_offset_ + Vector2(0.0f, uv_size_.y);
		vertices_[3].tex_coor_ = uv_offset_ + uv_size_;
	}
}
