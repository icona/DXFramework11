/*!
 \file Uncopyable.h
 \brief コピーと代入を禁止する基底クラスUncopyableを定義しています．<br>
		Effective C++ 第三版, Scott Meyers, p32-p33に記載されているコードです.
 \author icona<br>
		 <https://twitter.com/iconaHimeno><br>
		 <icona@outlook.jp>
 \date 14/05/09
*/

#pragma once

//! 汎用的なクラスや関数，テンプレートなどを含む名前空間
namespace Utl
{
	/*!
	 コピーと代入を禁止する基底クラス．
	 private継承して用いる．
	*/
	class Uncopyable
	{
	protected:
		/*! 生成と破棄の許可 */
		Uncopyable(){}
		~Uncopyable(){}

	private:
		/*! コピー(コンストラクタ)の禁止 */
		Uncopyable(const Uncopyable&);

		/*! 代入の禁止 */
		Uncopyable& operator=(const Uncopyable&);
	};
}
