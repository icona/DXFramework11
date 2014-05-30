#pragma once

/*!
 @file ScreenResolution.h
 @brief 画面解像度に関する定数などを定義しています．
 @author icona<br>
		 <https://twitter.com/iconaHimeno><br>
		 <icona@outlook.jp>
 @date 14/05/09
*/

#include <Windows.h>

/*! 汎用的なクラスや関数，テンプレートなどを含む名前空間 */
namespace Utl
{
	/*! 画面解像度に関する名前空間 */
	namespace ScrRes{
		/*! 各種画面解像度の定数．HVGAは縦長になっていることに注意．*/
		const RECT HVGA = { 0, 0, 480, 320 };
		const RECT VGA = { 0, 0, 640, 480 };
		const RECT WVGA = { 0, 0, 800, 480 };
		const RECT SVGA = { 0, 0, 800, 600 };
		const RECT XGA = { 0, 0, 1024, 768 };
		const RECT SPLASH = { 0, 0, 620, 300};

	}
}