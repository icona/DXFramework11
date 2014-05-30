/*!
@file Wnd.cpp
@brief Windowsプログラミングにおけるウィンドウ関連を取り扱っています．<br>
		ウィンドウプロシージャとWndクラスの実装が含まれています．<br>
		テスト用に作成しているだけで全面的に廃止・改善予定です．
@author icona<br>
<https://twitter.com/iconaHimeno><br>
<icona@outlook.jp>
@date 14/05/09
*/

#include "Wnd.h"


namespace WndStuff{
	namespace{
		/*!
		ウィンドウプロシージャ
		@param hWnd ウィンドウハンドル
		@param message メッセージコード
		@param wParam メッセージに関する追加情報
		@param lParam メッセージに関する追加情報
		*/
		LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			case WM_CLOSE:
				PostQuitMessage(0);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			return 0;
		}

		/*!
		ウィンドウの初期化・生成を行う．
		@param classname ウィンドウクラス名
		@param hIcon = nullptr アイコンのハンドル(デフォルトでnullptr)
		@param hCursor = nullptr カーソルのハンドル(デフォルトでnullptr)
		@return ウィンドウ生成の成否
		*/
		ATOM MyRegisterClass(Utl::tstring classname, HICON hIcon = nullptr, HCURSOR hCursor = nullptr)
		{
			WNDCLASSEX wcex;

			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.style = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc = WndProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = GetModuleHandle(NULL);
			wcex.hIcon = hIcon;
			wcex.hCursor = hCursor;
			wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wcex.lpszMenuName = NULL;
			wcex.lpszClassName = classname.c_str();
			wcex.hIconSm = nullptr;

			return RegisterClassEx(&wcex);
		}
	}

	Wnd::Wnd(const Utl::tstring& classname, const Utl::tstring& title, const RECT& rc)
	{
		InitWnd(classname, title, rc);
		renderTarget = DX11::D2D::init::CreateRenderTarget(hWnd);
	}

	Wnd::~Wnd()
	{

	}

	bool Wnd::InitWnd(const Utl::tstring& classname, const Utl::tstring& title, RECT rc)
	{
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		MyRegisterClass(classname);

		hWnd = CreateWindow(
			classname.c_str(), title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			(rc.right - rc.left), (rc.bottom - rc.top),
			NULL,
			NULL,
			GetModuleHandle(NULL),
			NULL
			);

		if (!hWnd)
		{
			return FALSE;
		}

		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);

		return true;
	}

}
