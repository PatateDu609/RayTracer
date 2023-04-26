#include "scene.hpp"


SceneBlockObject::SceneBlockObject(const std::string &id) : identifier(id) {
	if (id.empty()) {
		identifier.reset();
	}
}


const std::optional<std::string> &SceneBlockObject::getIdentifier() const {
	return identifier;
}