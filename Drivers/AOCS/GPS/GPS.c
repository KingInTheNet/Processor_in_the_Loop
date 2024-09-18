/**
 * @file GPS.c
 * @brief GPSとのインターフェースモジュール群です。
 * 
 * GPSインターフェースモジュールは、AxelSpace社AXELNAV-1とのインターフェースを実現し、
 * 初期化、データリクエスト、データ取得を行うモジュール群です。
 * @author 小林 宗太郎
 * @date 2012.10.18
 */

#include "utility.h"	// Printf()使用時には必要

#include "GPS.h"

//#define	GPS_DEBUG


int				GPS_Data_Conv(GPS_STRUCT *my_gps);
void			seven2eight(void* bef, void* aft, int size_bef, int size_aft, char sig_flag);
unsigned int	psmod(unsigned int xp, unsigned int xq);
long long		utc(unsigned char year_c, unsigned char mon, unsigned char day, unsigned char time, unsigned char min, unsigned char sec);


#define GPS_CONF_FRAME_SIZE	21	/**< @brief 出力データ設定コマンドの長さ*/
static unsigned int		gps_dummy1;
static unsigned char	gps_conf_cmd_data_standard_default[GPS_CONF_FRAME_SIZE] = 
{0xC6,									// ヘッダ
 0x00, 0x00, 0x00, 0x00,				// 推定緯度-未入力
 0x00, 0x00, 0x00, 0x00,				// 推定経度-未入力
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// UTC-未入力
 0x00, 0x00, 0x00,						// 回転楕円体高-未入力
 0x00,									// N/A
 0x00,									// (bit0)コールドスタート-しない,
 										// (bit1)初期化-しない,
 										// (bit2～4)入力値使用-しない,
 										// (bit5)マスターリセット-しない,
 										// (bit6)コマンドタイプ-標準コマンド
 0xDA};									// ターミネータ
  /**< @brief 出力データ設定コマンド(標準)*/
 
#define	GPS_CONF_STANDARD_CMD	gps_conf_cmd_data_standard_default	/**< @brief 出力データ設定コマンド(標準)*/

static unsigned int	gps_dummy2;
static unsigned char	gps_conf_cmd_data_expansion_default[GPS_CONF_FRAME_SIZE + 3] = 
{0x00, 0x00, 0x00,	// 「ヘッダ」のアドレスを4の倍数にするためのオフセット部
 0xC6,			// ヘッダ
 0x01,			// 測位モード-3D
 0x01,			// 仰角マスク角度-1
 0x00,			// 電離層・対流圏の地上用補正切り替えフラグ-補正なし
 0x40,			// PDOP上限リミット-128(設定値=64)
 0x02,			// 平滑化レベル-弱
 0x00,			// 測位座標系-WGS-84
 0x00,			// 使用禁止衛星①の衛星番号-使用禁止しない
 0x00,			// 使用禁止衛星②の衛星番号-使用禁止しない
 0x00,			// 使用禁止衛星③の衛星番号-使用禁止しない
 0x00,			// 使用禁止衛星④の衛星番号-使用禁止しない
 0x00,			// 使用禁止衛星⑤の衛星番号-使用禁止しない
 0x00,			// 使用禁止衛星⑥の衛星番号-使用禁止しない
 0x00,			// 出力フォーマット-標準出力
 0x00,			// エフェメリス出力する衛星番号-未入力
 0x00,			// コールドスタート要求-しない
 0x00,			// DGPS測位要求-しない
 0x00, 0x00,	// N/A
 0x40,			// (bit6)コマンドタイプ-拡張コマンド
 0xDA};			// ターミネータ
  /**< @brief 出力データ設定コマンド(拡張)*/

#define	GPS_CONF_EXPANSION_CMD	gps_conf_cmd_data_expansion_default + 3	/**< @brief 出力データ設定コマンド(拡張)*/


//#define GPS_RX_FRAME_SIZE			225
#define GPS_RX_FRAME_SIZE			99	/**< @brief 受信フレームの長さ*/

static unsigned char	gps_rx_header[1] = {0xC6};	/**< @brief 受信フレームのヘッダ*/
static unsigned char	gps_rx_footer[1] = {0xDA};	/**< @brief 受信フレームのフッタ*/

//*****************************************************************************
//	インターフェースモジュール
//*****************************************************************************
/**
 * @memberof GPS_STRUCT
 * @public
 * @brief GPS構造体をグローバルインスタンスとして定義し、ポインタを渡すことでポートを初期化します。
 * 
 * そして、 GPS_STRUCT.driver_super に定期受信部のヘッダ,フッタ,フレームサイズ、定期コマンド発行部の情報を記録します。
 * また、初期化と同時に、GPSに対して出力を「標準出力」のみにするようにコマンドを発行します。
 * @note GPSインターフェースモジュールを使用する時は起動時に必ず実施してください。
 * @param GPS_STRUCT *my_gps : 初期化するGPS構造体へのポインタ
 * @param unsigned char ch : GPSが接続されているUARTポート番号
 * @return 0 : 正常終了
 * @return 100番台 : 異常終了(詳細は DRIVER_Super_init() の戻り値を参照)
 * @return 1000番台 : 異常終了(詳細は GPS_Conf() の戻り値を参照)
 */
int		GPS_init(GPS_STRUCT* my_gps, unsigned char ch){
    int		i_ret;
	
	my_gps->rs422_config.ch = ch;
	my_gps->rs422_config.baudrate = 4800;
	my_gps->rs422_config.stop_bit = 2;
	
	my_gps->driver_super.inter_face = RS422;
	
	my_gps->driver_super.periodic_config.rx_header_size = sizeof(gps_rx_header);
	my_gps->driver_super.periodic_config.rx_header = gps_rx_header;
	
	my_gps->driver_super.periodic_config.rx_footer_size = sizeof(gps_rx_footer);
	my_gps->driver_super.periodic_config.rx_footer = gps_rx_footer;
	
	my_gps->driver_super.periodic_config.rx_frame_size = GPS_RX_FRAME_SIZE;
	
	my_gps->driver_super.periodic_config.tx_frame_size = 0;
	
	if((i_ret = DRIVER_Super_init(&(my_gps->driver_super), &(my_gps->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	
	/*
	pif((i_ret = GPS_Conf(my_gps)) != 0){	// Error
		return(i_ret);
	}
	*/
	
	return(0);
}

/**
 * @memberof GPS_STRUCT
 * @public
 * @brief GPSに対して定期コマンドを送信します。
 * 
 * 本GPSは定期コマンド送信が不要なので、この関数は実行しても何も起きません
 * @param GPS_STRUCT *my_gps : 対象とするGPS構造体へのポインタ
 * @return 0 : 正常終了
 * @return 0以外 : 異常終了(詳細は DRIVER_Super_cycle() の戻り値を参照)
 */
int		GPS_cycle(GPS_STRUCT* my_gps){
	int		i_ret;
	
		#ifdef	GPS_DEBUG
			Printf("GPS: *** DATA Req. ***\n");
		#endif
	if((i_ret = DRIVER_Super_cycle(&(my_gps->driver_super), &(my_gps->rs422_config))) != 0){	// Error
		return(i_ret);
	}
	return(0);
}

/**
 * @memberof GPS_STRUCT
 * @public
 * @brief GPSからのデータパケットを監視し、受信した内容を GPS_STRUCT に格納します。
 * 
 * GPSのデータ出力周期である、1秒より早い周期で定期的に実行してください。
 * @note データパケットについては DRIVER_Super_rec() を使用してフレーム同期をとり、
 * フレーム同期がとれた場合に受信内容を GPS_STRUCT に格納します。
 * @param GPS_STRUCT *my_gps : 対象とするGPS構造体へのポインタ
 * @return 1 : フレーム同期完了
 * @return 1以外 : データが受信されなかった等(詳細は DRIVER_Super_rec() の戻り値を参照)
 */
int		GPS_rec(GPS_STRUCT* my_gps){
	int		i_ret;
	
	i_ret = DRIVER_Super_rec(&(my_gps->driver_super), &(my_gps->rs422_config));
	if(i_ret == 1){
			#ifdef	GPS_DEBUG
				Printf("GPS: *** Frame ***\n");
			#endif
		GPS_Data_Conv(my_gps);
	}
	
	return(i_ret);
}

/**
 * @memberof GPS_STRUCT
 * @public
 * @brief GPS構造体のデータをデバッグコンソール上に表示します。
 * 
 * @param GPS_STRUCT *my_gas : 対象とするGPS構造体へのポインタ
 * @return 0 : 正常終了
 */
int		GPS_debug_message(GPS_STRUCT* my_gps){
	Printf("X:%lld ", my_gps->vector_x);
	Printf("Y:%lld ", my_gps->vector_y);
	Printf("Z:%lld ", my_gps->vector_z);
	//Printf("PDOP:%d ", my_gps->pdop);
	Printf("UTC:");
	Printf("20%02d/", my_gps->utc.year);
	Printf("%02d/", my_gps->utc.month);
	Printf("%02d ", my_gps->utc.day);
	Printf("%02d:", my_gps->utc.hour);
	Printf("%02d:", my_gps->utc.min);
	Printf("%02d ", my_gps->utc.sec);
	//Printf("aSat:%d ", my_gps->alive_sat);
	Printf("vSat:%d ", my_gps->visible_sat);
	//Printf("Delay:%d ", my_gps->delay_time);
	//Printf("PPS:%d ", my_gps->pps);
	//Printf("Sts1:%d ", my_gps->status1.byte);
	
	DRIVER_Super_debug_message(&(my_gps->driver_super));
	
	
	return(0);
}

/**
 * @memberof GPS_STRUCT
 * @public
 * @brief GPS出力データ設定コマンド発行関数です。
 * 
 * 出力データ設定コマンド(標準)を発行し、その1秒後に出力データ設定コマンド(拡張)を発行します。
 * @note aosc_superに非定期コマンド発行部と、そのコマンドに対するレスポンス受信部の情報を書き込み、
 *  DRIVER_Super_conf()を実行しています。
 * @param GPS_STRUCT *my_gps : 対象とするGPS構造体へのポインタ
 * @return 0 : 正常終了
 * @return 1000番台 : 出力データ設定コマンド(標準)発行部での異常終了(詳細は-1000をして DRIVER_Super_conf() の戻り値を参照)
 * @return 2000番台 : 出力データ設定コマンド(拡張)発行部での異常終了(詳細は-2000をして DRIVER_Super_conf() の戻り値を参照)
 */
int		GPS_Conf(GPS_STRUCT *my_gps){
	int		i_ret;	/**< @brief DRIVER_Super_conf()の戻り値格納*/
	
	my_gps->driver_super.non_periodic_config.rx_frame_size = 0;
	
	my_gps->driver_super.non_periodic_config.tx_frame_size = GPS_CONF_FRAME_SIZE;
	my_gps->driver_super.non_periodic_config.tx_frame = GPS_CONF_STANDARD_CMD;
	if((i_ret = DRIVER_Super_conf(&(my_gps->driver_super), &(my_gps->rs422_config))) != 1){	// Error
			#ifdef	GPS_DEBUG
				Printf("GPS: +++ Error Config Cmd 1 +++\n");
			#endif
		return (1000 + i_ret);
	}
	MilliSleep(1000);	//1sec wait
	
	my_gps->driver_super.non_periodic_config.tx_frame_size = GPS_CONF_FRAME_SIZE;
	my_gps->driver_super.non_periodic_config.tx_frame = GPS_CONF_EXPANSION_CMD;
	if((i_ret = DRIVER_Super_conf(&(my_gps->driver_super), &(my_gps->rs422_config))) != 1){	// Error
			#ifdef	GPS_DEBUG
				Printf("GPS: +++ Error Config Cmd 2 +++\n");
			#endif
		return (2000 + i_ret);
	}
	//MilliSleep(1000);	//1sec wait
	
	return(0);
}

//*****************************************************************************
//	内部モジュール
//*****************************************************************************
/**
 * @memberof GPS_STRUCT
 * @private
 * @brief フレームデータをGPS構造体のデータ内容に変換します。
 * 
 * 工学値変換が必要な場合はここに書き込みます。
 * @param GPS_STRUCT *my_gps : 対象とするGPS構造体へのポインタ
 * @return 0 : 正常終了
 */
int		GPS_Data_Conv(GPS_STRUCT *my_gps){
	/** @brief フレームデータのヘッダ分をオフセットしたポインタ*/
	unsigned char *gps_rx_data = my_gps->driver_super.periodic_rx_frame + sizeof(gps_rx_header);
	
	seven2eight(gps_rx_data + 0, &(my_gps->latitude), 4, sizeof(my_gps->latitude), 1);
	seven2eight(gps_rx_data + 4, &(my_gps->longitude), 4, sizeof(my_gps->longitude), 1);
	seven2eight(gps_rx_data + 8, &(my_gps->altitude), 3, sizeof(my_gps->altitude), 0);
	
	seven2eight(gps_rx_data + 11, &(my_gps->vector_x), 6, sizeof(my_gps->vector_x), 1);
	seven2eight(gps_rx_data + 17, &(my_gps->vector_y), 6, sizeof(my_gps->vector_y), 1);
	seven2eight(gps_rx_data + 23, &(my_gps->vector_z), 6, sizeof(my_gps->vector_z), 1);
	
	seven2eight(gps_rx_data + 29, &(my_gps->speed), 2, sizeof(my_gps->speed), 0);
	seven2eight(gps_rx_data + 31, &(my_gps->direction), 2, sizeof(my_gps->direction), 0);
	
	seven2eight(gps_rx_data + 33, &(my_gps->pdop), 2, sizeof(my_gps->pdop), 0);
	
	seven2eight(gps_rx_data + 35, &(my_gps->utc.year), 1, sizeof(my_gps->utc.year), 0);
	seven2eight(gps_rx_data + 36, &(my_gps->utc.month), 1, sizeof(my_gps->utc.month), 0);
	seven2eight(gps_rx_data + 37, &(my_gps->utc.day), 1, sizeof(my_gps->utc.day), 0);
	seven2eight(gps_rx_data + 38, &(my_gps->utc.hour), 1, sizeof(my_gps->utc.hour), 0);
	seven2eight(gps_rx_data + 39, &(my_gps->utc.min), 1, sizeof(my_gps->utc.min), 0);
	seven2eight(gps_rx_data + 40, &(my_gps->utc.sec), 1, sizeof(my_gps->utc.sec), 0);
	
	seven2eight(gps_rx_data + 41, &(my_gps->alive_sat), 1, sizeof(my_gps->alive_sat), 0);
	
	seven2eight(gps_rx_data + 42, &(my_gps->visible_sat), 1, sizeof(my_gps->visible_sat), 0);
	
	seven2eight(gps_rx_data + 43, &(my_gps->delay_time), 1, sizeof(my_gps->delay_time), 0);
	
	seven2eight(gps_rx_data + 44, &(my_gps->pps), 1, sizeof(my_gps->pps), 0);
	
	seven2eight(gps_rx_data + 95, &(my_gps->status1.byte), 1, sizeof(my_gps->status1.byte), 0);
	
	return(0);
}

/**
 * @memberof GPS_STRUCT
 * @private
 * @brief 7ビット形式(AXELNAV-1ユーザーズマニュアル参照)を8ビット形式に変換します。
 * @note ビッグエンディアン環境で実行のこと
 * @param void *bef : 変換前のデータ
 * @param void *aft : 変換後のデータ格納先
 * @param int size_bef : 変換前のデータサイズ
 * @param int size_aft : 変換後のデータ格納先サイズ
 * @param char sig_flag : 変換データが符号付きかどうか
 * @return なし
 */
void	seven2eight(void* bef, void* aft, int size_bef, int size_aft, char sig_flag){
#define S2E_TMP 8
	
	unsigned char* before = (unsigned char*)bef;	// 取得元アドレス
	unsigned char* after = (unsigned char*)aft;		// 格納先アドレス
	unsigned char tmp[S2E_TMP * 8 + 1];		// tmp[0]は使用しない, bool代数列として使用
	unsigned char sig_data;					// 正負のデータ
	int i, j, cnt;
	int i_offset;
	
	size_bef = size_bef - 1;	// バイトサイズ値は1～8では使用しづらいので0～7に変更
	size_aft = size_aft - 1;	// バイトサイズ値は1～8では使用しづらいので0～7に変更
	
	// 取得元からtmp[]へLSByte,LSBitから格納(各バイトのMSBitは無効データなのでスキップ)
	cnt = S2E_TMP * 8;
	for(i = size_bef; i >= 0; i--){		// LSByetより順に取得元のバイトサイズ数でループ
		for(j = 0; j < 7; j++){				// LSBitより順に7ビット分だけ格納
			tmp[cnt] = *(before + i);			// 対象バイトをまるごとコピー
			tmp[cnt] &= (1 << j);				// 対象バイト中の対象ビット以外にマスクがけ
			tmp[cnt] >>= j;						// 対象ビットの値がchar型でbool代数値に
			cnt--;								// 						なるようにシフト
		}
	}
	// signedフラグがあれば取得元のMSByte,MSBit-1の値で正負を判断し、sig_dataへ
	// signedフラグがなければそのまま
	// その後格納先サイズに合うようにtmp[]の値未格納部を埋める
	if(sig_flag != 0){		// もしsignedフラグが立っていれば
		cnt++;
		sig_data = tmp[cnt];
			//tmp[((S2E_TMP - size_aft) * 8) - 7] = sig_data;
		if(sig_data == 0){		// 正の場合
			for(cnt--; cnt > 0; cnt--){
				tmp[cnt] = 0;		// 値未格納部は0で埋める
			}
		}else{					// 負の場合
			for(cnt--; cnt > 0; cnt--){
				tmp[cnt] = 1;		// 値未格納部は1で埋める
			}
		}
	}else{					// もしsignedフラグがなければ
		for(; cnt > 0; cnt--){
			tmp[cnt] = 0;		// 値未格納部は0で埋める
		}
	}
	
	// 格納先の初期化
	for(i = 0; i <= size_aft; i++){
		*(after + i) = 0;
	}
	
	// 格納先へデータを格納
	for(i = 0; i <= size_aft; i++){
		i_offset = i + (S2E_TMP - (size_aft + 1));
		for(j = 1; j <= 8; j++){
			*(after + i) |= (tmp[(i_offset * 8) + j] << (8 - j));	//ビッグエンディアン時
			//*(after + (size_aft - i)) |= (tmp[(i_offset * 8) + j] << (8 - j));	//リトルエンディアン時
		}
	}
	
	return;
}

/**
 * @memberof GPS_STRUCT
 * @private
 * @brief 負の数の除算時の余りも計算します。
 * @note UTC算出時に使用します
 * @param unsigned int xp : 割られる数(整数)
 * @param unsigned int xq : 割る数(1以上の整数)
 * @return 余り
 */
unsigned int psmod(unsigned int xp, unsigned int xq){
	if(xp < 0){
		return ((xp % xq) + xq) % xq;
	}else{
		return (xp % xq);
	}
}//xqは1以上の整数、xpを整数とせよ。

/**
 * @memberof GPS_STRUCT
 * @private
 * @brief UTCを計算します。
 * @param unsigned char year_c : 年(下2桁)
 * @param unsigned char mon : 月
 * @param unsigned char day : 日
 * @param unsigned char time : 時
 * @param unsigned char min : 分
 * @param unsigned char sec : 秒
 * @return UTC
 */
long long utc(unsigned char year_c, unsigned char mon, unsigned char day, unsigned char time, unsigned char min, unsigned char sec){
	long long x;	/**< @brief UTC*/
	unsigned int year = 2000 + (unsigned int)year_c;	/**< @brief 年*/
	
	x = 31556952 * (year - 1970 - (psmod((year - 1970), 400)));
	year = 1970 + psmod((year - 1970), 400);
	while(year != 1970){
		if((psmod(year, 4) == 0 && psmod(year, 100) != 0) || psmod(year, 400) == 0){
			x += 31622400;
		}else{
			x += 31536000;
		}
		year -= 1;
	}
	switch((int)mon){
		case 12:
			day += 30;
		case 11:
			day += 31;
		case 10:
			day += 30;
		case 9:
			day += 31;
		case 8:
			day += 31;
		case 7:
			day += 30;
		case 6:
			day += 31;
		case 5:
			day += 30;
		case 4:
			day += 31;
		case 3:
			day += 28;
		case 2:
			day += 31;
			break;
		default:
			break;
	}
	x += (day - 1) * 86400 + time * 3600 + min * 60 + sec;
	
	return (x);
}
