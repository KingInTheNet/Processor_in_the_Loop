/**
 * @file DC.h
 * @brief DC(Discrete)ラッパーのクラスです。(AOBC用)
 * 
 * DC(Discrete)ラッパーは、
 * DCのインターフェースを実現し、
 * DCポートの初期化、DC信号入出力を行う、
 * DCラッパーのクラスです。
 * 個々の機器のインターフェースモジュールに継承?せさて使用します。
 * @author 小林 宗太郎
 * @date 2013.06.20
 */

#ifndef DC_INCLUDE_
#define DC_INCLUDE_


/**
 * @class DC_CONFIG_STRUCT
 * @brief DCポートの初期化、DC信号入出力の際に必要となる設定情報を格納する構造体です。
 */
typedef	struct {
		unsigned short	ch_in;	/**< @protected @brief  チャネル指定のbit0がポート1に、bit15がポート16に対応し、1を設定したポートのDC信号だけを取得します。*/
		unsigned short	ch_out;	/**< @protected @brief  チャネル指定のbit0がポート1に、bit15がポート16に対応し、1を設定したポートのDC信号だけを出力します。*/
}	DC_CONFIG_STRUCT;


int DC_init(void *my_dc_v);
int DC_Middlewear_RX(unsigned char call_counter);
int DC_RX(void *my_dc_v, void *data_v, int count);
int DC_TX(void *my_dc_v, void *data_v, int count);

extern	unsigned short	dc_val_out;	/**< @public @brief 最新のDC出力値データを格納する変数です(テレメトリ用)。*/
extern	unsigned short	dc_val_in;	/**< @public @brief 最新のDC入力値データを格納する変数です(テレメトリ用)。*/

#endif // DC_INCLUDE_
