#pragma once
namespace dae
{
	class SceneObject
	{
	public:
		virtual void Update() = 0;
		virtual void Render() const;

		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;
	};

	inline void SceneObject::Render() const
	{
	}
}
