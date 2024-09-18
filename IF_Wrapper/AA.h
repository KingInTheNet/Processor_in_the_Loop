/**
 * @file AA.h
 * @brief AA(ActiveAnalog)ラッパーのクラスです。
 * 
 * AA(ActiveAnalog)ラッパーは、
 * AAのインターフェースを実現し、
 * AAポートの初期化、電圧値取得を行う、
 * AAラッパーのクラスです。
 * 個々の機器のインターフェースモジュールに継承?せさて使用します。
 * @author 小林 宗太郎
 * @date 2012.10.26
 */

#ifndef AA_INCLUDE_
#define AA_INCLUDE_


/**
 * @class AA_CONFIG_STRUCT
 * @brief AAポートの初期化、電圧値取得の際に必要となる設定情報を格納する構造体です。
 */
typedef	struct {
		unsigned char	ch;	/**< @protected @brief  チャネル指定のbit0がポート1に、bit7がポート8に対応し、1を設定したポートの電圧値だけを取得します。*/
}	AA_CONFIG_STRUCT;


int AA_init(void *my_aa_v);
int AA_RX(void *my_aa_v, void *data_v, int count);
int AA_TX(void *my_aa_v, void *data_v, int count);

#endif // AA_INCLUDE_
