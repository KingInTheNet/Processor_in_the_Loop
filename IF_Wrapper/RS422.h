/**
 * @file RS422.h
 * @brief RS422(UART)通信ラッパーのクラスです。(AOBC用)
 * 
 * RS422(UART)通信ラッパーは、
 * RS422のインターフェースを実現し、
 * RS422ポートの初期化、データ送信、データ受信を行う、
 * RS422通信ラッパーのクラスです。
 * 個々の機器のインターフェースモジュールに継承?せさて使用します。
 * @note RS422(UART)のチャンネルはch0～21あり、今回はそのうちch0～16の計16chが外部へ出ています。
 * @author 小林 宗太郎
 * @date 2013.03.13
 */

#ifndef RS422_INCLUDE_
#define RS422_INCLUDE_


/**
 * @class RS422_CONFIG_STRUCT
 * @brief RS422ポートの初期化、データ送信、データ受信の際に必要となる設定情報を格納する構造体です。
 */
typedef	struct {
		unsigned char	ch;	/**< @protected @brief 継承先の機器がつながっているポート番号*/
		unsigned int	baudrate;	/**< @protected @brief 継承先の機器のボーレート値*/
		unsigned char	stop_bit;	/**< @protected @brief 継承先の機器のストップビット数*/
}	RS422_CONFIG_STRUCT;


int RS422_init(void *my_rs422_v);
int RS422_Middlewear_TRX(unsigned char call_counter);
int RS422_RX(void *my_rs422_v, void *data_v, int count);
int RS422_TX(void *my_rs422_v, void *data_v, int count);

#endif // RS422_INCLUDE_
