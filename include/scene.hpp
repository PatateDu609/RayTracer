#ifndef RAYTRACER_INCLUDE_SCENE_HPP
#define RAYTRACER_INCLUDE_SCENE_HPP

#include <optional>
#include <string>

namespace yy {
	class parser;
}

class SceneBlockObject {
public:
	SceneBlockObject() = default;
	SceneBlockObject(const SceneBlockObject &other) = default;
	SceneBlockObject &operator=(const SceneBlockObject &other) = default;
	virtual ~SceneBlockObject() = default;

	[[nodiscard]] const std::optional<std::string> &getIdentifier() const;

protected:
	explicit SceneBlockObject(const std::string &identifier);
	std::optional<std::string> identifier;
};

#endif //RAYTRACER_INCLUDE_SCENE_HPP
