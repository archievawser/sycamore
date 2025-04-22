FYI - this project isn't completed yet, it's for personal use only currently.

# Example scene

```cpp
class TPrototypeScene : public scm::TScene
{
	typedef scm::TScene Super;

public:
	void BeginPlay() override
	{
		// Load assets
		scm::TAssetManager::Directory = "../assets/";
		auto material = scm::TAssetManager::Load<scm::TMaterial>("flat.glsl");

		// Create cube
		auto geom (scm::TAssetManager::Load<scm::TGeometry>("cube.obj"));
		auto mesh = std::make_shared<scm::TMeshComponent>(geom, material);
		cube = new scm::TMesh(mesh);

		Super::BeginPlay();
	}

	void Update(float deltaTime) override
	{
		constexpr float rotSpeed = 0.5f;

		// Spin cube
		cube->Transform.Rotate(glm::vec3(1.0f), rotSpeed * deltaTime);

		Super::Update(deltaTime);
	}

	void Render() override
	{
		Renderer.Draw(*cube);
	}

	scm::TMesh* cube;
};
```
```cpp
class TGame : public scm::TApp
{
	typedef scm::TApp Super;

public:
	TGame(const char* name, unsigned int width, unsigned int height)
		: Super(name, width, height)
	{	}
};


int main()
{
	std::cout << "Running game" << std::endl;

	TGame* game = new TGame("Hello Cube", 1920U, 1080U);
	game->UseScene<TPrototypeScene>();
	game->Start();
}
```
