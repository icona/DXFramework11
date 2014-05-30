#pragma once

/*!
 @file ScreenResolution.h
 @brief ��ʉ𑜓x�Ɋւ���萔�Ȃǂ��`���Ă��܂��D
 @author icona<br>
		 <https://twitter.com/iconaHimeno><br>
		 <icona@outlook.jp>
 @date 14/05/09
*/

#include <Windows.h>

/*! �ėp�I�ȃN���X��֐��C�e���v���[�g�Ȃǂ��܂ޖ��O��� */
namespace Utl
{
	/*! ��ʉ𑜓x�Ɋւ��閼�O��� */
	namespace ScrRes{
		/*! �e���ʉ𑜓x�̒萔�DHVGA�͏c���ɂȂ��Ă��邱�Ƃɒ��ӁD*/
		const RECT HVGA = { 0, 0, 480, 320 };
		const RECT VGA = { 0, 0, 640, 480 };
		const RECT WVGA = { 0, 0, 800, 480 };
		const RECT SVGA = { 0, 0, 800, 600 };
		const RECT XGA = { 0, 0, 1024, 768 };
		const RECT SPLASH = { 0, 0, 620, 300};

	}
}