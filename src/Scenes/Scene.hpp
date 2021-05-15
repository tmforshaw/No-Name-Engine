#pragma once

namespace Scene
{
	class Scene
	{
	public:
		Scene() {}
		virtual ~Scene() {}

		virtual void OnUpdate( const float& deltaTime ) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

} // namespace Scene