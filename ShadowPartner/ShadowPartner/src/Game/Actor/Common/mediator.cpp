#include <vector>

#include "../../../Base/Element/gameobject.h"

namespace shadowpartner
{
	class ActorMediator
	{
	public:
		void AddObject(GameObject *object)
		{
			actors_.push_back(object);
		}

	private:
		std::vector<GameObject*> actors_;
	};
}