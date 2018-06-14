#ifndef _GAME_ACTOR_PLAYER_PLAYERCONTROLLER_H_
#define _GAME_ACTOR_PLAYER_PLAYERCONTROLLER_H_

#include "../../../Base/Element/component.h"

namespace shadowpartner {

	class PlayerController : public Component
	{
	public:
		PlayerController();
		~PlayerController();
		void SetPlayer(GameObject *player);
		void Update() override;

	private:
		GameObject *player_;
	};

}

#endif