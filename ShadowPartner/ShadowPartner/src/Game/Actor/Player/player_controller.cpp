#include "player_controller.h"

namespace shadowpartner {

	PlayerController::PlayerController() : player_(nullptr) {}

	PlayerController::~PlayerController() {}

	void PlayerController::SetPlayer(GameObject *player)
	{
		player_ = player;
	}

	void PlayerController::Update()
	{
		
	}

}	// namespace shadowpartner