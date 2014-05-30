/*!
 @file Wnd.h
 @brief Windowsプログラミングにおけるウィンドウ関連を取り扱っています．
 @author icona<br>
		 <https://twitter.com/iconaHimeno><br>
		 <icona@outlook.jp>
 @date 14/05/09
*/

#pragma once

#include "tstring.h"
#include "ScreenResolution.h"
#include "Direct2D.h"
#include "Direct3D.h"

/*! ウィンドウに関するクラス・関数群を含む名前空間 */
namespace WndStuff
{
	/*! ウィンドウの生成・管理を行うクラス */
	class Wnd
	{
	private: /* プロパティ */
		HWND hWnd;
		std::shared_ptr <ID2D1HwndRenderTarget> renderTarget;

	public: /* コンストラクタ・デストラクタ */
		/*!
		 コンストラクタ．
		 @param classname ウィンドウクラス名
		 @param title ウィンドウ名
		 @param rc = Utl::ScrRes::VGA ウィンドウサイズ(デフォルトでVGA)
		 */
		Wnd(const Utl::tstring& classname, const Utl::tstring& title, const RECT& rc = Utl::ScrRes::VGA);
		~Wnd();

	public: /* アクセサ */
		/*!
		 アクセサ．
		 @return ウィンドウハンドル
		 */
		HWND getHWND() const
		{
			return hWnd;
		};

		/*!
		アクセサ．
		@return レンダリングターゲットサーフェイス
		*/
		std::shared_ptr <ID2D1HwndRenderTarget> getRenderTarget() const
		{
			return renderTarget;
		};

	public: /* 操作 */
		/*!
		ウィンドウの初期化・生成を行う．
		@param classname ウィンドウクラス名
		@param title ウィンドウ名
		@param rc ウィンドウサイズ(デフォルトでVGA)
		@return ウィンドウ生成の成否
		*/
		bool InitWnd(const Utl::tstring& classname, const Utl::tstring& title, RECT rc);

	};
}