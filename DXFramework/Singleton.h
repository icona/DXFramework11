/*!
@file Singleton.h
@brief インスタンスの唯一性を保証する基底クラスのテンプレートSingletonを定義しています．
@author icona<br>
<https://twitter.com/iconaHimeno><br>
<icona@outlook.jp>
@date 14/05/21
*/

#pragma once

/*! 汎用的なクラスや関数，テンプレートなどを含む名前空間 */
namespace Utl
{
	
	template<typename T>
	/*! インスタンスの唯一性を保証する基底クラスのテンプレート */
	class Singleton
	{
	protected:
		/*! 外部からの生成の禁止 */
		Singleton(){};
		virtual ~Singleton(){};

	public:
		/*!
			インスタンス化とその参照の取得．
			@return インスタンスの参照
		*/
		static T& getInstance()
		{
			static T instance;
			return instance;
		}
	};
}
