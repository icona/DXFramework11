#include "DXFramework.h"

class Game :
	public DxFramework::App
{
private:
public:
	// コンストラクタ
	Game(const Utl::tstring& title, RECT rc = Utl::ScrRes::VGA)
		: App(title, rc)
	{

	}

	// デストラクタ
	~Game()
	{

	}

	// メイン（ここにコードを追加）
	int Run()
	{
		// 初期化
		auto target = wnd->getRenderTarget();
		auto earth = DX11::D2D::CreateBitmap(__TEXT("earth.jpg"), target.get());

		// ゲームループ
		Gameloop(
			[target, earth]() mutable
		{
			auto size = earth->GetSize();
			float x = 10.0f, y = 10.0f;

			target->BeginDraw();
			target->Clear(::D2D1::ColorF(::D2D1::ColorF::SkyBlue));
			target->DrawBitmap(earth.get(), ::D2D1::Rect<float>(x, y, x + size.width, y + size.height));
			target->EndDraw();
		}
		);

		return 0;
	}
};

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszStr, INT nCmdShow)
{
	Game game(__TEXT("title"));
	game.Run();
	
	return 0;
}
