/**
 * @file MOBC.h
 * @brief MOBCとのインターフェースモジュール群です。
 * 
 * MOBCインターフェースモジュールは、MHI社MOBCとのインターフェースを実現し、
 * データ取得・コマンド送信を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2012.11.01
 */

#ifndef	MOBC_INCLUDE_
#define	MOBC_INCLUDE_


#include "../../../IF_Wrapper/RS422.h"


/**
 * @class MOBC_STRUCT
 * @extends RS422_CONFIG_STRUCT
 * @brief MOBCの情報を格納する構造体です。
 * 
 * MOBC1台に対して、1つのグローバルインスタンスとして定義します。
 *  MOBC_init() により初期化して使用します。
 */
typedef	struct {
	RS422_CONFIG_STRUCT	rs422_config;	/**< @private @brief RS422クラスの構造体*/
}	MOBC_STRUCT;


int MOBC_init(MOBC_STRUCT *my_mobc, unsigned char ch);
int MOBC_RS422_Data_Send(MOBC_STRUCT *my_mobc, void *data_v, int size);
int MOBC_RS422_Data_Receive(MOBC_STRUCT *my_mobc, void *data_v, int size);

#endif // MOBC_INCLUDE_
