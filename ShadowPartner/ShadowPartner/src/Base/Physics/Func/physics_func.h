//==========================================================
// �T�v  :�����֌W�̊֐�
// Author:Itsuki Namito
// Copyright(c) Utsurugi.All right reserved.
//==========================================================

#ifndef _BASE_PHYSICS_FUNC_PHYSICS_FUNC_H_
#define _BASE_PHYSICS_FUNC_PHYSICS_FUNC_H_

//**********************************************************
// �C���N���[�h�t�@�C��
//**********************************************************
#include "../Element/collider.h"
#ifdef _DEBUG
#include "../Debug/debug_draw.h"
#endif

namespace physics
{
	struct RaycastHit
	{
		RaycastHit()
			:collider(nullptr)
			, hit_point(Vector2::zero())
		{
		}
		Collider *collider;
		Vector2 hit_point;
	};

	//==========================================================
	// �T�v  :�����֌W�̊֐�
	//==========================================================
	class PhysicsFunc
	{
	public:
		// variables
		
		// methods
		static RaycastHit Raycast(Vector2 start,Vector2 direction,
			float distance = FLT_MAX,Layer layer_mask = Layer::kDefault);

	private:

	};
}

#endif