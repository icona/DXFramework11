#pragma once

/*!
 @file tstring.h
 @brief tchar������string�Ctstring��p�ӂ��܂��D
 @author icona<br>
		 <https://twitter.com/iconaHimeno><br>
		 <icona@outlook.jp>
 @date 14/05/09
*/

#include <string>
#include <Windows.h>

/*! basic_string��TCHAR�œ��ꉻ���Ctstring�Ɩ��O�t�����܂��D */
namespace Utl
{
	typedef std::basic_string<TCHAR> tstring;
}
