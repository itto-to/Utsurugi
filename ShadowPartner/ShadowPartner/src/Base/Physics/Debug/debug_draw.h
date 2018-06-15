//==========================================================
// 概要  :デバッグ用の描画クラス
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_DEBUG_DEBUG_DRAW_H_
#define _BASE_PHYSICS_DEBUG_DEBUG_DRAW_H_

#ifdef _DEBUG

//**********************************************************
// インクルードファイル
//**********************************************************
#include <Box2D\Box2D.h>
#include <d3dx9.h>

namespace physics
{
#define PHYSICS_DEBUG_LINE_MAX (10000)

//#define B2_TO_D3DX_COLOR(b2) D3DCOLOR_RGBA((int)(b2.r * 255.0f),(int)(b2.g * 255.0f),(int)(b2.b * 255.0f),255)
#define B2_TO_D3D_COLOR(b2) D3DCOLOR_RGBA(255,255,255,255)

	struct DebugVertex
	{
		inline DebugVertex()
			:rhw_(1.0f)
		{
		}
		inline DebugVertex(const b2Vec2 &v,const b2Color &c)
		{
			pos_[0] = v.x;
			pos_[1] = v.y;
			pos_[2] = 0.0f;
			rhw_ = 1.0f;
			color_ = B2_TO_D3D_COLOR(c);
		}
		inline DebugVertex(const b2Vec2 &v, const D3DCOLOR &c)
		{
			pos_[0] = v.x;
			pos_[1] = v.y;
			pos_[2] = 0.0f;
			rhw_ = 1.0f;
			color_ = c;
		}
		inline DebugVertex(const float32 &x,const float32 &y, const D3DCOLOR &c)
		{
			pos_[0] = x;
			pos_[1] = y;
			pos_[2] = 0.0f;
			rhw_ = 1.0f;
			color_ = c;
		}

		float pos_[3];
		float rhw_;
		D3DCOLOR color_;
	};

	struct DebugLine
	{
		DebugVertex p1, p2;
		
		DebugLine()
		{
		}
	};

	struct DebugCircle
	{
		b2Vec2 center;
		b2Color color;
		
		DebugCircle()
			:center(b2Vec2_zero)
			,color(b2Color())
		{
		}
	};

	struct DrawSettings
	{
		DrawSettings()
			:draw_shapes_(1)
			,draw_particles_(1)
			,draw_joints_(1)
			,draw_aabbs_(0)
			,draw_coms_(0)
		{
		}

		int draw_shapes_;
		int draw_particles_;
		int draw_joints_;
		int draw_aabbs_;
		int draw_coms_;
	};

	//==========================================================
	// 概要  :デバッグ用の描画クラス
	//==========================================================
	class DebugDraw : public b2Draw
	{
	public:
		// コンストラクタ
		DebugDraw();
		~DebugDraw();

		void Init();
		void Uninit();
		void Draw();

		void SetDrawFlags(DrawSettings settings);

		void DrawPolygon(const b2Vec2 *vertices, int vertex_count, const b2Color &color);
		void DrawFlatPolygon(const b2Vec2 *vertices, int vertex_count, const b2Color &color);
		void DrawSolidPolygon(const b2Vec2 *vertices, int vertex_count, const b2Color &color);

		void DrawCircle(const b2Vec2 &center, float radius, const b2Color &color);
		void DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color);

		void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color);

		void DrawParticles(const b2Vec2 *centers, float radius, const b2ParticleColor *colors, int count);

		void DrawTransform(const b2Transform& xf);

		void DrawPoint(const b2Vec2 &p, float size, const b2Color &color);

		void DrawString(int x, int y, const char *string, ...);
		void DrawString(const b2Vec2 &p, const char *string, ...);

		void DrawAABB(b2AABB *aabb, const b2Color &color);

	private:
		LPDIRECT3DVERTEXBUFFER9 vertex_buff_;
		LPDIRECT3DINDEXBUFFER9 index_buff_;

		int line_count_;
		DebugLine lines_[PHYSICS_DEBUG_LINE_MAX];

		DrawSettings settings_;
		int flags_;
	};
	void LoadOrtho2DMatrix(double left, double right, double bottom, double top);
}

#endif	// end of _DEBUG

#endif