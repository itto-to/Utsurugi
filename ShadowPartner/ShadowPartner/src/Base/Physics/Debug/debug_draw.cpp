//==========================================================
// �T�v  :�f�o�b�O�p�̕`��N���X
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================
#ifdef _DEBUG

#include "debug_draw.h"
#include "../../../Game/Application/application.h"
#include "../../Debug/debugger.h"
#include "../../Math/math.h"
#include <d3dx9.h>
#include "../../2D/texture.h"
#include "../../2D/camera.h"


using namespace shadowpartner;
using namespace math;

namespace
{
	//==========================================================
	// ���[���h���W����X�N���[�����W�֕ϊ�
	//==========================================================
	Vector2 ToScreenPos(const Vector2 &world_pos)
	{
		Vector2 pixel_world_pos = world_pos * PIXEL_PER_UNIT;
		Vector2 draw_pos = Vector2(pixel_world_pos.x, -pixel_world_pos.y) / Camera::main_->GetZoom();
		Vector2 screen_center = Vector2(Application::Instance()->GetScreenWidth() / 2, Application::Instance()->GetScreenHeight() / 2);
		draw_pos += screen_center - Vector2(Camera::main_->transform_->position_) * PIXEL_PER_UNIT;

		return draw_pos;
	}
}

namespace physics
{
	//**********************************************************
	// ���C���\����
	//**********************************************************
#define FVF_WIREFRAME (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define DEBUG_CIRCLE_VERTEX_NUM (60)
#define DEBUG_PARTICLE_VERTEX_NUM (8)


	DebugDraw::DebugDraw()
		:line_count_(0)
		,settings_()
	{
	}

	DebugDraw::~DebugDraw()
	{
	}

	// ����������
	void DebugDraw::Init()
	{
		LPDIRECT3DDEVICE9 device = Application::Instance()->device;

		D3DXCreateLine(device, &line_object_);
		HRESULT hr;

		// ���_�o�b�t�@�̍쐬
		hr = device->CreateVertexBuffer
			(
				sizeof(DebugVertex) * PHYSICS_DEBUG_LINE_MAX * 2,
				D3DUSAGE_WRITEONLY,
				FVF_WIREFRAME,
				D3DPOOL_MANAGED,
				&vertex_buff_,
				NULL
				);

		if (FAILED(hr))
			debug::Debug::WarningBox("���_�o�b�t�@�̍쐬�Ɏ��s");

		// �C���f�b�N�X�o�b�t�@�̍쐬
		hr = device->CreateIndexBuffer
			(
				sizeof(WORD) * PHYSICS_DEBUG_LINE_MAX * 2,
				D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16,
				D3DPOOL_MANAGED,
				&index_buff_,
				NULL
				);

		if (FAILED(hr))
			debug::Debug::WarningBox("�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s");

		//SetDrawFlags(settings_);
	}

	// �I������
	void DebugDraw::Uninit()
	{
		line_object_->Release();
		line_object_ = nullptr;
	}

	// �`�揈��
	void DebugDraw::Draw()
	{

		if (line_count_ == 0)
			return;

		if (line_count_ > PHYSICS_DEBUG_LINE_MAX)
		{
			debug::Debug::WarningBox("Line�̏���l�𑝂₵�Ă��������B(physics::DebugDraw::Draw())");
		}

		{
			DebugVertex *vtx;
			vertex_buff_->Lock(0, 0, (void**)&vtx, 0);

			for (int i = 0; i < line_count_ * 2;++i)
			{
				if (i % 2 == 0)
					vtx[i] = lines_[i / 2].p1;
				else
					vtx[i] = lines_[i / 2].p2;
			}

			vertex_buff_->Unlock();
		}

		{
			WORD *idx;
			index_buff_->Lock(0, 0, (void**)&idx, 0);

			for (int i = 0;i < line_count_ * 2;++i)
			{
				idx[i] = i;
			}

			index_buff_->Unlock();
		}

		LPDIRECT3DDEVICE9 device = Application::Instance()->device;

		device->SetStreamSource(0, vertex_buff_, 0, sizeof(DebugVertex));
		device->SetIndices(index_buff_);

		device->SetFVF(FVF_WIREFRAME);

		device->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, line_count_ * 2, 0, line_count_);
		//if (FAILED(device->DrawPrimitiveUP(D3DPT_LINELIST, line_count_, lines_, sizeof(DebugVertex))))
		//	debug::Debug::WarningBox("�����蔻��̕`�掸�s");

		line_count_ = 0;
	}

	// �`����e��ݒ肷��
	void DebugDraw::SetDrawFlags(DrawSettings settings)
	{
		flags_ = 0;
		flags_ += settings.draw_shapes_    * b2Draw::e_shapeBit;
		flags_ += settings.draw_particles_ * b2Draw::e_particleBit;
		flags_ += settings.draw_joints_    * b2Draw::e_jointBit;
		flags_ += settings.draw_aabbs_     * b2Draw::e_aabbBit;
		flags_ += settings.draw_coms_      * b2Draw::e_centerOfMassBit;

		SetFlags(flags_);
	}

	//==========================================================
	// �T�v  :�|���S����\��
	//==========================================================
	void DebugDraw::DrawPolygon(const b2Vec2 *vertices, int vertex_count, const b2Color &color)
	{
		Vector2 *vertex_list = new Vector2[vertex_count + 1];

		for (int i = 0; i < vertex_count; i++)
		{
			vertex_list[i] = ToScreenPos(Vector2(vertices[i].x, vertices[i].y));
		}
		vertex_list[vertex_count] = vertex_list[0];

		line_object_->Draw(vertex_list, vertex_count + 1, D3DXCOLOR(color.r, color.g, color.b, 1.0f));
		delete[] vertex_list;

		//D3DCOLOR c = B2_TO_D3D_COLOR(color);
		//D3DCOLOR c = D3DCOLOR_RGBA(0x00, 0xff, 0x00, 0xff);

		//DebugLine line;
		//for (int i = 0;i < vertex_count - 1;++i)
		//{
		//	line.p1 = DebugVertex(vertices[i], c);
		//	line.p2 = DebugVertex(vertices[i + 1], c);
		//	//line.p1 = DebugVertex(vertices[i].x,-vertices[i].y, c);
		//	//line.p2 = DebugVertex(vertices[i + 1].x, -vertices[i + 1].y, c);

		//	lines_[line_count_++] = line;
		//}

		//line.p1 = DebugVertex(vertices[vertex_count - 1], c);
		//line.p2 = DebugVertex(vertices[0], c);

		//lines_[line_count_++] = line;
	}

	void DebugDraw::DrawFlatPolygon(const b2Vec2 *vertices, int vertex_count, const b2Color &color)
	{
		DrawPolygon(vertices, vertex_count, color);
	}

	void DebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int vertex_count, const b2Color &color)
	{
		DrawPolygon(vertices, vertex_count, color);
	}

	//==========================================================
	// �T�v  :�~��`��
	//==========================================================
	void DebugDraw::DrawCircle(const b2Vec2 &center, float radius, const b2Color &color)
	{
		const int kDegreeBetweenVertex = 6;
		const int kNumVertex = 360 / kDegreeBetweenVertex + 1;

		Vector2 *vertex_list = new Vector2[kNumVertex];
		for (int i = 0; i < kNumVertex; i++)
		{
			float rad = D3DXToRadian(i * kDegreeBetweenVertex);
			vertex_list[i] = ToScreenPos(Vector2(center.x, center.y) + radius * Vector2(cosf(rad), sinf(rad)));
		}
		//vertex_list[kNumVertex] = vertex_list[0];

		line_object_->Draw(vertex_list, kNumVertex, D3DXCOLOR(color.r, color.g, color.b, 1.0f));
		////D3DCOLOR c = B2_TO_D3D_COLOR(color);
		//D3DCOLOR c = D3DCOLOR_RGBA(0x00, 0xff, 0x00, 0xff);

		//DebugLine line;
		//float theta;		// �~�̒��S�ƐV�K�ɓo�^���钸�_���Ȃ��������Ȃ��p�x

		//line.p1 = DebugVertex(center + b2Vec2(radius, 0.0f), c);
		//theta = b2_pi / DEBUG_CIRCLE_VERTEX_NUM;
		//line.p2 = DebugVertex(center + b2Vec2(cosf(theta) * radius, sinf(theta) * radius),c);

		//lines_[line_count_++] = line;

		//for (int i = 1;i < DEBUG_CIRCLE_VERTEX_NUM - 1;++i)
		//{
		//	line.p1 = line.p2;
		//	theta = b2_pi * (float)(i + 1) / DEBUG_CIRCLE_VERTEX_NUM;
		//	line.p2 = DebugVertex(center + b2Vec2(cosf(theta) * radius, sinf(theta) * radius), c);

		//	lines_[line_count_++] = line;
		//}

		//line.p1 = line.p2;
		//line.p2 = DebugVertex(center + b2Vec2(radius, 0.0f), c);

		//lines_[line_count_++] = line;
	}

	void DebugDraw::DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color)
	{
		DrawCircle(center, radius, color);
	}

	//==========================================================
	// �T�v  :
	//==========================================================
	void DebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color)
	{
		Vector2 vertex[2];
		vertex[0] = Vector2(p1.x, p1.y);
		vertex[1] = Vector2(p2.x, p2.y);
		line_object_->Draw(vertex, 2, D3DXCOLOR(color.r, color.g, color.b, 1.0f));

	}

	//==========================================================
	// �T�v  :�p�[�e�B�N����\��
	//==========================================================
	void DebugDraw::DrawParticles(const b2Vec2 *centers, float radius, const b2ParticleColor *colors, int count)
	{
		for (int i = 0;i < count;++i)
		{
			//D3DCOLOR c = B2_TO_D3D_COLOR(color);
			D3DCOLOR c = D3DCOLOR_RGBA(0x00, 0xff, 0x00, 0xff);

			DebugLine line;
			float theta;		// �~�̒��S�ƐV�K�ɓo�^���钸�_���Ȃ��������Ȃ��p�x

			line.p1 = DebugVertex(centers[i] + b2Vec2(radius, 0.0f), c);
			theta = b2_pi / DEBUG_PARTICLE_VERTEX_NUM;
			line.p2 = DebugVertex(b2Vec2(cosf(theta) * radius, sinf(theta) * radius), c);

			lines_[line_count_++] = line;

			for (int j = 1;j < DEBUG_PARTICLE_VERTEX_NUM - 1;++j)
			{
				line.p1 = line.p2;
				theta = b2_pi * (float)(j + 1) / DEBUG_PARTICLE_VERTEX_NUM;
				line.p2 = DebugVertex(b2Vec2(cosf(theta) * radius, sinf(theta) * radius), c);

				lines_[line_count_++] = line;
			}

			line.p1 = line.p2;
			line.p2 = DebugVertex(centers[i] + b2Vec2(radius, 0.0f), c);

			lines_[line_count_++] = line;
		}
	}

	//==========================================================
	// �T�v  :
	//==========================================================
	void DebugDraw::DrawTransform(const b2Transform& xf)
	{

	}

	//==========================================================
	// �T�v  :
	//==========================================================
	void DebugDraw::DrawPoint(const b2Vec2 &p, float size, const b2Color &color)
	{

	}

	//==========================================================
	// �T�v  :
	//==========================================================
	void DebugDraw::DrawString(int x, int y, const char *string, ...)
	{

	}

	//==========================================================
	// �T�v  :
	//==========================================================
	void DebugDraw::DrawString(const b2Vec2 &p, const char *string, ...)
	{

	}

	//==========================================================
	// �T�v  :
	//==========================================================
	void DebugDraw::DrawAABB(b2AABB *aabb, const b2Color &color)
	{

	}
}

#endif
