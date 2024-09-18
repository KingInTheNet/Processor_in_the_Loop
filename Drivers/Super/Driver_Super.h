/**
 * @file Driver_Super.h
 * @brief 各制御センサ・アクチュエータ等とのインターフェースモジュール群のスーパークラスです。
 * 
 * Driver_Superインターフェースモジュールは、
 * 各制御センサ・アクチュエータ等とのインターフェースを実現し、
 * 初期化、データリクエスト(定期)、データ取得(定期)、非定期設定コマンド・レスポンス受信を行う、
 * モジュール群のスーパークラスです。
 * 個々の機器のインターフェースモジュールに継承?せさて使用します。
 * @date 2013.06.29
 */

#ifndef	DRIVER_SUPER_INCLUDE_
#define	DRIVER_SUPER_INCLUDE_


#include "../../IF_Wrapper/IF_list.h"


#define	DRIVER_SUPER_RX_BUFFER_SIZE_MAX	512	/**< @brief 受信データバッファの最大長*/
#define	DRIVER_SUPER_RX_FRAME_SIZE_MAX	512	/**< @brief 受信データフレームの最大長*/


/**
 * @brief コマンド発行・データ受信の際に必要となる設定情報を格納する構造体です。
 * 
 * DRIVER_SUPER構造体内において、定期/非定期それぞれにおいて定義しています。
 * @warning rx_frame_sizeが負(受信データが可変長の場合) かつ rx_framelength_placeが0(フレームサイズデータがない場合)において、ヘッダ,フッタが0ということは許されません。
 */
typedef	struct {
	//【継承先まで公開】
		/** @name コマンド発行設定*/
		/** @{*/
		unsigned char	*tx_frame;		/**< @protected @brief 送信データフレーム*/
		int				tx_frame_size;	/**< @protected @brief 送信データサイズ
										 * 
										 * 送信データがない場合は0に設定します。
										 */
		/** @}*/
		
		/** @name データ受信設定*/
		/** @{*/
		unsigned char	*rx_header;		/**< @protected @brief 受信データのヘッダ*/
		int				rx_header_size;	/**< @protected @brief 受信データのヘッダサイズ
										 * 
										 * ヘッダがない場合は0に設定します(この場合にはrx_frame_sizeが負(受信データが可変長)は許されません)。
										 */
		unsigned char	*rx_footer;		/**< @protected  @brief 受信データのフッタ*/
		int				rx_footer_size;	/**< @protected @brief 受信データのフッタサイズ
										 * 
										 * フッタがない場合は0に設定します(この場合にはrx_frame_sizeが負(受信データが可変長)は許されません)。
										 */
		int				rx_frame_size;	/**< @protected @brief 受信データフレームサイズ
										 * 
										 * 受信データが可変長の場合は負の値に設定します。
										 * また、受信データがない場合は0に設定します。
										 */
		unsigned char	rx_framelength_place;	/**< @protected @brief 受信データ内のフレームサイズデータの存在する場所(先頭(1バイト)から数えて何バイト目に位置するか)
												 * 
												 * 受信データが可変長の場合にのみ使用される設定値であります。
												 * フレームサイズデータの存在する場所(先頭(1バイト)から数えて何バイト目に位置するか)を指定します。
												 * フレームサイズデータがない場合には0に設定します(この場合にはrx_header_sizeとrx_footer_sizeが0ということは許されません)。
												 */
		unsigned char	rx_framelength_offset;	/**< @protected @brief 受信データ内のフレームサイズデータへのオフセット値
												 * 
												 * 受信データが可変長の場合にのみ使用される設定値であります。
												 * フレームサイズデータによる可変長データの解析は「フレームの全サイズ」により行われますが、
												 * 機器の中にはヘッダとフッタの分は除いたデータ数として表現されている場合があります。
												 * そのような場合にこの変数に対して、除かれているデータ数分を設定してやることで、受信されるフレームサイズデータに対して加算され、正常に解析することができます。
												 * フレームサイズデータが「フレームの全サイズ」を示している場合には0に設定します。
												 */
		/** @}*/
		
		
	//【非公開】
		int				rx_frame_count;	/**< @private @brief 受信データフレームカウンタ*/
		int				rx_except_footer_size;	/**< @private @brief フッタを除いた受信フレームデータサイズ*/
		int				rx_frame_size_v;	/**< @private @brief 可変長の場合の受信データフレームサイズ( DRIVER_SUPER_Analyze_variable() でのみ使用)*/
		int 			rx_footer_flag;	/**< @private @brief フッタ発見フラグカウンタ( DRIVER_SUPER_Analyze_variable_not_fsd() でのみ使用)*/
}	DRIVER_SUPER_CONFIG_STRUCT;


/**
 * @class DRIVER_SUPER_STRUCT
 * @brief 各機器全てで共通に必要となる情報を格納する構造体です。
 * 
 * DRIVER_SUPER構造体は、各センサの1つのグローパルインスタンスの中に含ませて定義します。
 *  Driver_Super_init() により初期化してから使用します。
 */
typedef	struct {
	//【全てに公開】
		int				tx_count;	/**< @public @brief 定期データリクエスト送信回数*/
		int				rx_count;	/**< @public @brief 定期データパケット受信回数*/
		int				update_flg;	/**< @public @brief 定期応答が得られなかったデータリクエスト送信の回数
									 * 
									 * 0以外の場合データは最新でない危険性があります。
									 * この数値が3である場合、現在のデータは3制御周期の間更新されていません。
									 */
		unsigned long	cmd_time;	/**< @public @brief 定期データリクエストを送信した時刻(msec)*/
		unsigned long	update_time;	/**< @public @brief 定期データパケットを受信した時刻(msec)*/
		
		
	//【継承先まで公開】
		/** @name ハードの設定*/
		/** @{*/
		IF_LIST_ENUM	inter_face;	/**< @protected @brief 継承先の機器の使用IF*/
		/** @}*/
		
		/** @name 定期コマンド発行・データ受信関係*/
		/** @{*/
		DRIVER_SUPER_CONFIG_STRUCT	periodic_config;	/**< @protected @brief 定期関係の設定データ構造体*/
		unsigned char		periodic_rx_frame[DRIVER_SUPER_RX_FRAME_SIZE_MAX];	/**< @protected @brief 定期受信データ*/
		/** @}*/
		
		/** @name 非定期コマンド発行・データ受信関係*/
		/** @{*/
		DRIVER_SUPER_CONFIG_STRUCT	non_periodic_config;	/**< @protected @brief 非定期関係の設定データ構造体*/
		unsigned char		non_periodic_rx_frame[DRIVER_SUPER_RX_FRAME_SIZE_MAX];	/**< @protected @brief 非定期受信データ*/
		/** @}*/
		
		
	//【非公開】
		unsigned char	rx_buffer[DRIVER_SUPER_RX_BUFFER_SIZE_MAX];	/**< @private @brief データ受信バッファ*/
}	DRIVER_SUPER_STRUCT;


int DRIVER_Super_init(DRIVER_SUPER_STRUCT *my_super, void *if_config);
int DRIVER_Super_cycle(DRIVER_SUPER_STRUCT *my_super, void *if_config);
int DRIVER_Super_rec(DRIVER_SUPER_STRUCT *my_super, void *if_config);
int DRIVER_Super_conf(DRIVER_SUPER_STRUCT *my_super, void *if_config);
int DRIVER_Super_debug_message(DRIVER_SUPER_STRUCT *my_super);

#endif // DRIVER_SUPER_INCLUDE_
