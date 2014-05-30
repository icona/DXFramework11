/*!
 @file App.h
 @brief ウィンドウクラスを包括し，ゲームループを含みメインとなるAppクラスを定義しています
 @author icona<br>
		 <https://twitter.com/iconaHimeno><br>
		 <icona@outlook.jp>
 @date 14/05/09
*/

#pragma once

#include "Wnd.h"
#include "ScreenResolution.h"
#include "Utility.h"


#define SHADER_LEVEL_4_1
#include "ShaderLevelDefine.h"

#include <string>
#include <memory>

namespace DxFramework
{
	class App
		: Utl::Uncopyable,
		public Utl::Singleton<App>
	{
	protected:
		std::unique_ptr<WndStuff::Wnd> wnd;

	public:
		App(Utl::tstring title, RECT rc = Utl::ScrRes::VGA);
		virtual ~App();

	public:
		HWND getHWnd(){ return wnd->getHWND(); };
		std::shared_ptr <ID2D1HwndRenderTarget> getRenderTarget() const
		{ return wnd->getRenderTarget(); };

	public:
		template<typename Functor>
		int Gameloop(Functor f)
		{
			MSG msg = { 0 };
			ZeroMemory(&msg, sizeof(msg));
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					// gamemain
					f();
					Sleep(1);
				}
			}

			return msg.wParam;
		}

		virtual int Run() = 0;
	};
}
