/**
 * @file PA.h
 * @brief PA(PassiveAnalog)ラッパーのクラスです。(AOBC用)
 * 
 * PA(PassiveAnalog)ラッパーは、
 * PAのインターフェースを実現し、
 * PAポートの初期化、電流値取得を行う、
 * PAラッパーのクラスです。
 * 個々の機器のインターフェースモジュールに継承?せさて使用します。
 * @author 小林 宗太郎
 * @date 2013.06.20
 */

#ifndef PA_INCLUDE_
#define PA_INCLUDE_


/**
 * @class PA_CONFIG_STRUCT
 * @brief PAポートの初期化、電流値取得の際に必要となる設定情報を格納する構造体です。
 */
typedef	struct {
		unsigned short	ch;	/**< @protected @brief  チャネル指定のbit0がポート1に、bit15がポート16に対応し、1を設定したポートの電圧値だけを取得します。*/
}	PA_CONFIG_STRUCT;


int PA_init(void *my_pa_v);
int PA_Middlewear_RX(unsigned char call_counter);
int PA_RX(void *my_pa_v, void *data_v, int count);
int PA_TX(void *my_pa_v, void *data_v, int count);

#endif // PA_INCLUDE_
