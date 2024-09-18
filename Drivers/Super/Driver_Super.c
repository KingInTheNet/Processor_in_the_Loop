/**
 * @file Driver_Super.c
 * @brief 各制御センサ・アクチュエータ等とのインターフェースモジュール群のスーパークラスです。
 * 
 * Driver_Superインターフェースモジュールは、
 * 各制御センサ・アクチュエータ等とのインターフェースを実現し、
 * 初期化、データリクエスト(定期)、データ取得(定期)、非定期設定コマンド・レスポンス受信を行う、
 * モジュール群のスーパークラスです。
 * 個々の機器のインターフェースモジュールに継承?せさて使用します。
 * @date 2013.06.29
 */

#include "utility.h"

#include "Driver_Super.h"

//#define	DRIVER_SUPER_DEBUG

int		DRIVER_SUPER_TX(DRIVER_SUPER_STRUCT *my_super, DRIVER_SUPER_CONFIG_STRUCT *config, void *if_config);
int		DRIVER_SUPER_RX(DRIVER_SUPER_STRUCT *my_super, DRIVER_SUPER_CONFIG_STRUCT *config, void *if_config, unsigned char *frame);
int		DRIVER_SUPER_Analyze(unsigned char data, DRIVER_SUPER_CONFIG_STRUCT *config, unsigned char *frame);
int		DRIVER_SUPER_Analyze_variable(unsigned char data, DRIVER_SUPER_CONFIG_STRUCT *config, unsigned char *frame);
int		DRIVER_SUPER_Analyze_variable_not_fsd(unsigned char data, DRIVER_SUPER_CONFIG_STRUCT *config, unsigned char *frame);


//*****************************************************************************
//	インターフェースモジュール
//*****************************************************************************
/**
 * @memberof DRIVER_SUPER_STRUCT
 * @protected
 * @brief DRIVER_SUPER構造体をグローバルインスタンスとして定義し、ポインタを渡すことでポートを初期化します。
 * 
 * そして、構造体内の初期化が必要な変数を初期化します。
 * @note Driver_Superインターフェースモジュールを使用する時は起動時に必ず実施してください。
 * @param DRIVER_SUPER_STRUCT *my_super : 初期化するDRIVER_SUPER構造体へのポインタ
 * @param void *if_config : 使用するIFの設定値構造体へのポインタ
 * @return 0 : 正常終了
 * @return 0以外 : 異常終了(詳細は 対象IF_init() の戻り値を参照)
 */
int		DRIVER_Super_init(DRIVER_SUPER_STRUCT *my_super, void *if_config){
    int				i_ret = 0;
	
	if((i_ret = (*IF_init[my_super->inter_face])(if_config)) != 0){	// Error
		return(i_ret);
	}
	
	my_super->tx_count = 0;
	my_super->rx_count = 0;
	my_super->update_flg = 0;
	my_super->cmd_time = 0;
	my_super->update_time = 0;
	
	my_super->periodic_config.rx_frame_count = 0;
	
	// rx_frame_size数が負(可変データバイト長)の時
	if(my_super->periodic_config.rx_frame_size < 0){
		// 何もしない
	}else{
		my_super->periodic_config.rx_except_footer_size
		 = my_super->periodic_config.rx_frame_size - my_super->periodic_config.rx_footer_size;
	}
	return (0);
}

/**
 * @memberof DRIVER_SUPER_STRUCT
 * @protected
 * @brief 継承先の機器に対して定期コマンドを送信します。
 * @note この関数を実行する度に DRIVER_SUPER_STRUCT.update_flg , DRIVER_SUPER_STRUCT.tx_count をインクリメントし、
 *  DRIVER_SUPER_STRUCT.cmd_time に実行時のOBC時刻を格納します。
 * @warning この関数を実行する前にDRIVER_SUPER構造体内の定期コマンド送信関係の設定値を設定しておく必要があります。
 * @param DRIVER_SUPER_STRUCT *my_super : 対象とするDRIVER_SUPER構造体へのポインタ
 * @param void *if_config : 使用するIFの設定値構造体へのポインタ
 * @return 0 : 正常終了
 * @return 0以外 : 異常終了(詳細は DRIVER_SUPER_TX() の戻り値を参照)
 */
int		DRIVER_Super_cycle(DRIVER_SUPER_STRUCT *my_super, void *if_config){
	my_super->update_flg++;
	my_super->tx_count++;
	my_super->cmd_time = my_time();
		#ifdef	DRIVER_SUPER_DEBUG
			Printf("DRIVER_SUPER: *** DATA Req. ***\n");
		#endif
	return(DRIVER_SUPER_TX(my_super, &(my_super->periodic_config), if_config));
}

/**
 * @memberof DRIVER_SUPER_STRUCT
 * @protected
 * @brief 継承先の機器より定期受信データを受信します。
 * 
 * 継承先の機器のデータ出力周期より早い周期で定期的に実行してください。
 * @note データについては DRIVER_SUPER_RX() を使用して受信し、その中で DRIVER_SUPER_Analyze() を使用してフレーム同期をとり、
 * フレーム同期がとれた場合、 DRIVER_SUPER_STRUCT.update_flg を0にクリアし、 
 *  DRIVER_SUPER_STRUCT.rx_count をインクリメントし、 DRIVER_SUPER_STRUCT.update_time にその時のOBC時刻を格納します。
 * @warning この関数を実行する前にDRIVER_SUPER構造体内の定期データ受信関係の設定値を設定しておく必要があります。
 * @param DRIVER_SUPER_STRUCT *my_super : 対象とするDRIVER_SUPER構造体へのポインタ
 * @param void *if_config : 使用するIFの設定値構造体へのポインタ
 * @return 1 : フレーム同期完了
 * @return 1以外 : データが受信されなかった等(詳細は DRIVER_SUPER_RX() の戻り値を参照)
 */
int		DRIVER_Super_rec(DRIVER_SUPER_STRUCT *my_super, void *if_config){
	int		ret;
	
	if((ret = DRIVER_SUPER_RX(my_super, &(my_super->periodic_config), if_config, my_super->periodic_rx_frame)) == 1){
		my_super->update_flg = 0;
		my_super->rx_count++;
		my_super->update_time = my_time();
	}
	return(ret);
}

/**
 * @memberof DRIVER_SUPER_STRUCT
 * @protected
 * @brief 継承先の機器より非定期コマンドを発行し、そのレスポンスを受信します。
 * 
 * 継承先の機器のデータ出力周期より早い周期で定期的に実行してください。
 * @note レスポンスデータについては DRIVER_SUPER_RX() を使用して受信し、その中で DRIVER_SUPER_Analyze() を使用してフレーム同期をとっています。
 * @warning この関数を実行する前にDRIVER_SUPER構造体内の非定期コマンド発行・レスポンス受信関係の設定値を設定しておく必要があります。
 * @param DRIVER_SUPER_STRUCT *my_super : 対象とするDRIVER_SUPER構造体へのポインタ
 * @param void *if_config : 使用するIFの設定値構造体へのポインタ
 * @return 1 : 正常終了
 * @return 0 : タイムアウト(200msec)
 * @return 上記以外 : データが不正だった等(詳細は DRIVER_SUPER_RX() の戻り値を参照)
 */
int		DRIVER_Super_conf(DRIVER_SUPER_STRUCT *my_super, void *if_config){
	int				ret;
	unsigned long	start_time;
	
	my_super->non_periodic_config.rx_frame_count = 0;
	my_super->non_periodic_config.rx_except_footer_size
	 = my_super->non_periodic_config.rx_frame_size - my_super->non_periodic_config.rx_footer_size;
	
	//DRIVER_SUPER_RX(my_super, &(my_super->non_periodic_config), my_super->non_periodic_rx_frame);
	
		#ifdef	DRIVER_SUPER_DEBUG
			Printf("DRIVER_SUPER: *** Conf Cmd. ***\n");
		#endif
	DRIVER_SUPER_TX(my_super, &(my_super->non_periodic_config), if_config);
	
	if(my_super->non_periodic_config.rx_frame_size == 0){
		return(1);
	}
	
	ret = 0;
	start_time  = my_time();
	while(((my_time() - start_time) < 200) && ((my_time() - start_time) > 0)){
		if((ret = DRIVER_SUPER_RX(my_super, &(my_super->non_periodic_config), if_config, my_super->non_periodic_rx_frame)) == 1){
			return (ret);
		}
		MilliSleep(1);
	}
	
	return(ret);
}

/**
 * @memberof DRIVER_SUPER_STRUCT
 * @protected
 * @brief DRIVER_SUPER_STRUCT.tx_count, rx_count, cmd_time, update_timeをデバッグコンソール上に表示します。
 * 
 * @param DRIVER_SUPER_STRUCT *my_super : 対象とするDRIVER_SUPER構造体へのポインタ
 * @return 0 : 正常終了
 */
int		DRIVER_Super_debug_message(DRIVER_SUPER_STRUCT *my_super){
	if(my_super->periodic_config.rx_frame_size != 0){
		Printf("RX_Time:%ld ", my_super->update_time);
		Printf("RX:%d ", my_super->rx_count);
	}
	if(my_super->periodic_config.tx_frame_size != 0){
		Printf("TX_Time:%lu ", my_super->cmd_time);
		Printf("TX:%d ", my_super->tx_count);
	}
	
	
	return (0);
}

//*****************************************************************************
//	内部モジュール
//*****************************************************************************
/**
 * @memberof DRIVER_SUPER_STRUCT
 * @private
 * @brief DRIVER_SUPER_CONFIG構造体にて定期/非定期の指定された方のコマンドを発行します。
 * 
 * 送信データフレームサイズが0の場合には何もしません。
 * @param DRIVER_SUPER_STRUCT *my_super : 対応するDRIVER_SUPER構造体へのポインタ
 * @param DRIVER_SUPER_CONFIG_STRUCT *config : 対応するDRIVER_SUPER_CONFIG構造体へのポインタ
 * @param void *if_config : 使用するIFの設定値構造体へのポインタ
 * @return 0 : 正常終了
 * @return 0以外 : 異常終了(詳細は 対象IF_TX() の戻り値を参照)
 */
int		DRIVER_SUPER_TX(DRIVER_SUPER_STRUCT *my_super, DRIVER_SUPER_CONFIG_STRUCT *config, void *if_config){
	if(config->tx_frame_size == 0){
		return(0);
	}
	
		#ifdef	DRIVER_SUPER_DEBUG
			Printf("DRIVER_SUPER: *** DATA Tx. ***\n");
		#endif
	return((*IF_TX[my_super->inter_face])(if_config, config->tx_frame, config->tx_frame_size));
}

/**
 * @memberof DRIVER_SUPER_STRUCT
 * @private
 * @brief 受信データがあるか確認します。
 * 
 * 受信データがなければ0でリターンします。
 * 受信データがあれば、固定長データの時は、 DRIVER_SUPER_STRUCT.rx_buffer[] に格納し、1バイトずつ DRIVER_SUPER_Analyze() にて、定期/非定期の指定された方の状態遷移にかけます。
 * 可変長データでフレームサイズデータが存在する時は、 DRIVER_SUPER_STRUCT.rx_buffer[] に格納し、1バイトずつ DRIVER_SUPER_Analyze_variable() にて、定期/非定期の指定された方の状態遷移にかけます。
 * 可変長データでフレームサイズデータが存在しない時は、 DRIVER_SUPER_STRUCT.rx_buffer[] に格納し、1バイトずつ DRIVER_SUPER_Analyze_variable_not_fsd() にて、定期/非定期の指定された方の状態遷移にかけます。
 * 受信データフレームサイズが0の場合には何もしません。
 * @param DRIVER_SUPER_STRUCT *my_super : 対応するDRIVER_SUPER構造体へのポインタ
 * @param DRIVER_SUPER_CONFIG_STRUCT *config : 対応するDRIVER_SUPER_CONFIG構造体へのポインタ
 * @param void *if_config : 使用するIFの設定値構造体へのポインタ
 * @param unsigned char *frame : 対応する受信データフレーム
 * @return 1 : 正常終了
 * @return 0 : 受信データなし
 * @return 上記以外(固定長データの時) : 最後に実行した DRIVER_SUPER_Analyze() 戻り値(詳細は DRIVER_SUPER_Analyze() の戻り値を参照)
 * @return 上記以外(可変長データでフレームサイズデータが存在する時) : 最後に実行した DRIVER_SUPER_Analyze_variable() 戻り値(詳細は DRIVER_SUPER_Analyze_variable() の戻り値を参照)
 * @return 上記以外(可変長データでフレームサイズデータが存在しない時) : 最後に実行した DRIVER_SUPER_Analyze_variable_not_fsd() 戻り値(詳細は DRIVER_SUPER_Analyze_variable_not_fsd() の戻り値を参照)
 */
int		DRIVER_SUPER_RX(DRIVER_SUPER_STRUCT *my_super, DRIVER_SUPER_CONFIG_STRUCT *config, void *if_config, unsigned char *frame){
	int				ret;
	int				count;
	unsigned char	*data = my_super->rx_buffer;
	
	if(config->rx_frame_size == 0){
		return(1);
	}
	
	//	RX
	if((count = (*IF_RX[my_super->inter_face])(if_config, data, DRIVER_SUPER_RX_BUFFER_SIZE_MAX)) <= 0){
		return(0);
	}
	
		//	RX Process
	if(config->rx_frame_size < 0){	// 可変長データの時
		if(config->rx_framelength_place > 0){	// フレームサイズデータが存在する時
			while (count > 0){
				if((ret = DRIVER_SUPER_Analyze_variable(*data, config, frame)) == 1){
					return(ret);
				}
				data++;
				count--;
			}
		}else{	// フレームサイズデータが存在しない時
			while (count > 0){
				if((ret = DRIVER_SUPER_Analyze_variable_not_fsd(*data, config, frame)) == 1){
					return(ret);
				}
				data++;
				count--;
			}
		}
	}else{	// 固定長データの時
		while (count > 0){
			if((ret = DRIVER_SUPER_Analyze(*data, config, frame)) == 1){
				return(ret);
			}
			data++;
			count--;
		}
	}
	
	return(ret);
}

/**
 * @memberof DRIVER_SUPER_STRUCT
 * @private
 * @brief dataの値によってrx_frame_countの状態遷移を行います。(固定長データ用)
 * 
 * ヘッダとフッタのエラーを検出します。検出した場合データを更新せずに戻ります。
 * 受信ヘッダサイズが0の場合はヘッダのチェックは行いません。
 * 受信フッタサイズが0の場合はフッタのチェックは行いません。
 * フレームが確定したら1をリターンします。
 * 状態遷移則はソースファイル内のコメントを参照ください。
 * @param unsigned char data : 受信データ
 * @param DRIVER_SUPER_CONFIG_STRUCT *config : 対応するDRIVER_SUPER_CONFIG構造体へのポインタ
 * @param unsigned char *frame : 対応する受信データフレーム
 * @return 1 : フレーム確定
 * @return 100番台 : ヘッダ受信中(-100した値が現在の受信バイト数)
 * @return 200番台 : ステータスデータ受信中(-200した値が現在の受信バイト数)
 * @return 300番台 : フッタ受信中(-300した値が現在の受信バイト数)
 * @return -100番台 : ヘッダエラー(-1を掛けて-100した値のバイト数目でエラー)
 * @return -300番台 : フッタエラー(-1を掛けて-300した値のバイト数目でエラー)
 * @return -1 : その他エラー
 */
int		DRIVER_SUPER_Analyze(unsigned char data, DRIVER_SUPER_CONFIG_STRUCT *config, unsigned char *frame){
	int		ret;
	
	// frame_count数が"ヘッダ受信中数"の場合
	if(config->rx_frame_count < config->rx_header_size){
		// ヘッダのチェック
		if(data == config->rx_header[config->rx_frame_count]){
			frame[config->rx_frame_count] = data;
			ret = config->rx_frame_count + 1;
			config->rx_frame_count++;
			return(100 + ret);
		}else{
			ret = config->rx_frame_count + 1;
			config->rx_frame_count = 0;
				#ifdef	DRIVER_SUPER_DEBUG
						Printf("DRIVER_SUPER: +++ Error Data in %d byte +++\n", ret);
				#endif
			return(-(100 + ret));
		}
	// frame_count数が"データ受信中数"の場合
	}else if(config->rx_frame_count < config->rx_except_footer_size){
		frame[config->rx_frame_count] = data;
		ret = config->rx_frame_count + 1;
		config->rx_frame_count++;
		// フッタがない場合で、かつframe_count数が"フレーム取得完了数"の場合
		if((config->rx_footer_size == 0) && (config->rx_frame_count == config->rx_frame_size)){
				#ifdef	DRIVER_SUPER_DEBUG
					Printf("DRIVER_SUPER: *** FRAME ***\n");
				#endif
			config->rx_frame_count = 0;
			return(1);
		// それ以外
		}else{
			return(200 + ret);
		}
	// frame_count数が"データ終了数"の場合
	}else if(config->rx_frame_count < config->rx_frame_size){
		// フッタのチェック
		if(data == config->rx_footer[config->rx_frame_count - config->rx_except_footer_size]){
			frame[config->rx_frame_count] = data;
			ret = config->rx_frame_count + 1;
			config->rx_frame_count++;
			// frame_count数が"フレーム取得完了数"の場合
			if(config->rx_frame_count == config->rx_frame_size){
					#ifdef	DRIVER_SUPER_DEBUG
						Printf("DRIVER_SUPER: *** FRAME ***\n");
					#endif
				config->rx_frame_count = 0;
				return(1);
			}else{
				return(300 + ret);
			}
		}else{
			ret = config->rx_frame_count + 1;
			config->rx_frame_count = 0;
				#ifdef	DRIVER_SUPER_DEBUG
						Printf("DRIVER_SUPER: +++ Error Data in %d byte +++\n", ret);
				#endif
			return(-(300 + ret));
		}
	}else{
		config->rx_frame_count = 0;
		return(-1);
	}
	return(0);
}

/**
 * @memberof DRIVER_SUPER_STRUCT
 * @private
 * @brief dataの値によってrx_frame_countの状態遷移を行います。(可変長データでフレームサイズデータが存在する時用)
 * 
 * ヘッダとフッタとフレームサイズデータのエラーを検出します。検出した場合データを更新せずに戻ります。
 * フレームが確定したら1をリターンします。
 * 状態遷移則はソースファイル内のコメントを参照ください。
 * @param unsigned char data : 受信データ
 * @param DRIVER_SUPER_CONFIG_STRUCT *config : 対応するDRIVER_SUPER_CONFIG構造体へのポインタ
 * @param unsigned char *frame : 対応する受信データフレーム
 * @return 1 : フレーム確定
 * @return 100番台 : ヘッダ受信中(-100した値が現在の受信バイト数)
 * @return 200番台 : ステータスデータ受信中(フレームサイズデータ未受信)(-200した値が現在の受信バイト数)
 * @return 300番台 : ステータスデータ受信中(フレームサイズデータ受信時)(-300した値が現在の受信バイト数)
 * @return 400番台 : ステータスデータ受信中(フレームサイズデータ受信後)(-400した値が現在の受信バイト数)
 * @return 500番台 : フッタ受信中(-500した値が現在の受信バイト数)
 * @return -100番台 : ヘッダエラー(-1を掛けて-100した値のバイト数目でエラー)
 * @return -500番台 : フッタエラー(-1を掛けて-500した値のバイト数目でエラー)
 * @return -1 : フレームサイズデータの存在する場所がヘッダ内に設定されている時
 * @return -2 : その他エラー
 */
int		DRIVER_SUPER_Analyze_variable(unsigned char data, DRIVER_SUPER_CONFIG_STRUCT *config, unsigned char *frame){
	int		ret;
	
	// フレームサイズデータの存在する場所がヘッダ内に設定されている時
	if(config->rx_framelength_place <= config->rx_header_size){
			#ifdef	DRIVER_SUPER_DEBUG
					Printf("DRIVER_SUPER: +++ config Erroe +++ (v)\n", ret);
			#endif
		return(-1);
	}
	
	// frame_count数が"ヘッダ受信中数"の場合
	if(config->rx_frame_count < config->rx_header_size){
		// ヘッダのチェック
		if(data == config->rx_header[config->rx_frame_count]){
			frame[config->rx_frame_count] = data;
			ret = config->rx_frame_count + 1;
			config->rx_frame_count++;
			return(100 + ret);
		}else{
			ret = config->rx_frame_count + 1;
			config->rx_frame_count = 0;
				#ifdef	DRIVER_SUPER_DEBUG
						Printf("DRIVER_SUPER: +++ Error Data in %d byte +++ (v)\n", ret);
				#endif
			return(-(100 + ret));
		}
	// frame_count数がフレームサイズデータの存在する場所よりも小さい場合
	}else if(config->rx_frame_count < (config->rx_framelength_place - 1)){
		frame[config->rx_frame_count] = data;
		ret = config->rx_frame_count + 1;
		config->rx_frame_count++;
		return(200 + ret);
	// frame_count数がフレームサイズデータの存在する場所となった場合
	}else if(config->rx_frame_count == (config->rx_framelength_place - 1)){
		frame[config->rx_frame_count] = data;
		ret = config->rx_frame_count + 1;
		config->rx_frame_count++;
		config->rx_frame_size_v = frame[config->rx_framelength_place - 1] + config->rx_framelength_offset;
		config->rx_except_footer_size = config->rx_frame_size_v - config->rx_footer_size;
		return(300 + ret);
	// frame_count数がフレームサイズデータの存在する場所よりも大きい場合
	}else if(config->rx_frame_count > (config->rx_framelength_place - 1)){
		// frame_count数が"データ受信中数"の場合
		if(config->rx_frame_count < config->rx_except_footer_size){
			frame[config->rx_frame_count] = data;
			ret = config->rx_frame_count + 1;
			config->rx_frame_count++;
			// フッタがない場合で、かつframe_count数が"フレーム取得完了数"の場合
			if((config->rx_footer_size == 0) && (config->rx_frame_count == config->rx_frame_size_v)){
					#ifdef	DRIVER_SUPER_DEBUG
						Printf("DRIVER_SUPER: *** FRAME *** (v)\n");
					#endif
				config->rx_frame_count = 0;
				return(1);
			// それ以外
			}else{
				return(400 + ret);
			}
		// frame_count数が"データ終了数"の場合
		}else if(config->rx_frame_count < config->rx_frame_size_v){
			// フッタのチェック
			if(data == config->rx_footer[config->rx_frame_count - config->rx_except_footer_size]){
				frame[config->rx_frame_count] = data;
				ret = config->rx_frame_count + 1;
				config->rx_frame_count++;
				// frame_count数が"フレーム取得完了数"の場合
				if(config->rx_frame_count == config->rx_frame_size_v){
						#ifdef	DRIVER_SUPER_DEBUG
							Printf("DRIVER_SUPER: *** FRAME *** (v)\n");
						#endif
					config->rx_frame_count = 0;
					return(1);
				}else{
					return(500 + ret);
				}
			}else{
				ret = config->rx_frame_count + 1;
				config->rx_frame_count = 0;
					#ifdef	DRIVER_SUPER_DEBUG
							Printf("DRIVER_SUPER: +++ Error Data in %d byte +++ (v)\n", ret);
					#endif
				return(-(500 + ret));
			}
		}else{
			config->rx_frame_count = 0;
			return(-2);
		}
	}
	return(0);
}

/**
 * @memberof DRIVER_SUPER_STRUCT
 * @private
 * @brief dataの値によってrx_frame_countの状態遷移を行います。(可変長データでフレームサイズデータが存在しない時用)
 * 
 * ヘッダのエラーを検出します。検出した場合データを更新せずに戻ります。
 * フッタに相当するデータ列が発見された場合に「フレーム確定」とします。
 * フレームが確定したら1をリターンします。
 * 状態遷移則はソースファイル内のコメントを参照ください。
 * @warning ヘッダ, フッタが0の場合において、本関数を使用する状況(可変長データ)は許されません
 * @param unsigned char data : 受信データ
 * @param DRIVER_SUPER_CONFIG_STRUCT *config : 対応するDRIVER_SUPER_CONFIG構造体へのポインタ
 * @param unsigned char *frame : 対応する受信データフレーム
 * @return 1 : フレーム確定
 * @return 100番台 : ヘッダ受信中(-100した値が現在の受信バイト数)
 * @return 200番台 : ステータスデータ受信中(-200した値が現在の受信バイト数)
 * @return -100番台 : ヘッダエラー(-1を掛けて-100した値のバイト数目でエラー)
 * @return -1 : フレームカウント数オーバー(ヘッダは来たが、いつまでたってもフッタがこなかった時)
 */
int		DRIVER_SUPER_Analyze_variable_not_fsd(unsigned char data, DRIVER_SUPER_CONFIG_STRUCT *config, unsigned char *frame){
	int		ret;
	
	// フレームカウント数オーバー
	if(config->rx_frame_count >= DRIVER_SUPER_RX_FRAME_SIZE_MAX){
			#ifdef	DRIVER_SUPER_DEBUG
					Printf("DRIVER_SUPER: +++ frame_count Over +++ (v_n_fsd)\n", ret);
			#endif
		config->rx_frame_count = 0;
		return(-1);
	}
	
	// frame_count数が"ヘッダ受信中数"の場合
	if(config->rx_frame_count < config->rx_header_size){
		// ヘッダのチェック
		if(data == config->rx_header[config->rx_frame_count]){
			frame[config->rx_frame_count] = data;
			ret = config->rx_frame_count + 1;
			config->rx_frame_count++;
			config->rx_footer_flag = 0;	//ヘッダのチェック時にrx_footer_flagを初期化しておく
			return(100 + ret);
		}else{
			ret = config->rx_frame_count + 1;
			config->rx_frame_count = 0;
				#ifdef	DRIVER_SUPER_DEBUG
						Printf("DRIVER_SUPER: +++ Error Data in %d byte +++ (v_n_fsd)\n", ret);
				#endif
			return(-(100 + ret));
		}
	// frame_count数が"ヘッダ受信中数"以外の場合
	}else{
		frame[config->rx_frame_count] = data;
		ret = config->rx_frame_count + 1;
		config->rx_frame_count++;
		// フッタチェック
		if(data == config->rx_footer[config->rx_footer_flag]){
			config->rx_footer_flag++;
			if(config->rx_footer_flag == config->rx_footer_size){
					#ifdef	DRIVER_SUPER_DEBUG
						Printf("DRIVER_SUPER: *** FRAME *** (v_n_fsd)\n");
					#endif
				config->rx_frame_count = 0;
				config->rx_footer_flag = 0;
				return(1);
			}
		}else{
			config->rx_footer_flag = 0;
		}
		return(200 + ret);
	}
	return(0);
}
