#pragma once

/*!
 @file tstring.h
 @brief tcharを扱うstring，tstringを用意します．
 @author icona<br>
		 <https://twitter.com/iconaHimeno><br>
		 <icona@outlook.jp>
 @date 14/05/09
*/

#include <string>
#include <Windows.h>

/*! basic_stringをTCHARで特殊化し，tstringと名前付けします． */
namespace Utl
{
	typedef std::basic_string<TCHAR> tstring;
}
