#pragma once
class FollowCameraComponent final : public Component<FollowCameraComponent>
{
private:
	sf::View view;
	TransformComponent* transform = nullptr;

public:
	void start() override
	{
		transform = gameObject->getComponent<TransformComponent>();

		auto const * const renderTarget = SystemLocator::getSystem<RenderSystem>()->getRenderTarget();
		view = renderTarget->getDefaultView();
	}

	void update(const int64_t deltaTime) override
	{
		auto * const renderTarget = SystemLocator::getSystem<RenderSystem>()->getRenderTarget();
		view.setCenter(transform->position);
		renderTarget->setView(view);
	}
};
