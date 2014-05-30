#include "App.h"

/*!
@file App.cpp
@brief Appクラスの実装
@author icona<br>
<https://twitter.com/iconaHimeno><br>
<icona@outlook.jp>
@date 14/05/09
*/

namespace DxFramework
{
	App::App(Utl::tstring title, RECT rc) :
		wnd( new WndStuff::Wnd(title, title, rc) )
		// 初期化リストで例外が発生するとAppのデストラクタは呼ばれません．
	{
	}

	
	App::~App()
	{
	}
}