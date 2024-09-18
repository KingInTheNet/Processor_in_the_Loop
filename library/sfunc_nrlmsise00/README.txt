とにもかくにもbuild_sfunc_nrlmsise00.mdlをたちあげてブロックをクリックしてビルド
(sfunc_nrlmsise00.wmex32ができます)

・check_sfunc_nrlmsise00.mdl
   Simulinkの組み込みの大気密度を計算するブロックとCコードから生成したブロックを
   フルで比較するもの

・check_sfunc_nrlmsise00_2.mdl
   上記のものでLST, F107, aphをSimulinkの組み込みブロックの内部変数を使うようにして
   Cコードから生成したブロックと比較するもの

・check_sfunc_nrlmsise00_3.mdl
   上記のものを綺麗なsubsystemのブロックにしたもの

・test_rapidaccel_sfunc_nrlmsise00.mdl
   S-Functionがラピッドアクセラレータで動くかチェックするもの

・test_rapidaccel_sfunc_nrlmsise00_2.mdl
   上記のものを綺麗なsubsystemのブロックにしたもの

20120530_MATLAB_SimulinkでのS-functionの作り方と使い方.docxも参照してください。