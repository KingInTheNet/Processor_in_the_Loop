/**
 * @file CCSDS.h
 * @brief CCSDS通信ラッパーのクラスです。(AOBC用 通常取り込みVer)
 * 
 * CCSDS通信ラッパーは、
 * CCSDSのインターフェースを実現し、
 * CCSDSポートの初期化、データ送信、データ受信を行う、
 * CCSDS通信ラッパーのクラスです。
 * 個々の機器のインターフェースモジュールに継承?せさて使用します。
 * @author 小林 宗太郎
 * @date 2012.10.18
 */

#ifndef CCSDS_INCLUDE_
#define CCSDS_INCLUDE_


/**
 * @class CCSDS_CONFIG_STRUCT
 * @brief CCSDSポートの初期化、データ送信、データ受信の際に必要となる設定情報を格納する構造体です。
 */
typedef	struct {
		unsigned char	onoff;	/**< @protected @brief CCSDS出力のON/OFF(0:OFF 1:ON)*/
		unsigned int	bitrate;	/**< @protected @brief 継承先の機器のビットレート値(キロ)*/
}	CCSDS_CONFIG_STRUCT;


		int				CCSDS_init(void *my_ccsds_v);
		int				CCSDS_RX(void *my_ccsds_v, void *data_v, int count);
		int				CCSDS_TX(void *my_ccsds_v, void *data_v, int count);

#endif // CCSDS_INCLUDE_
