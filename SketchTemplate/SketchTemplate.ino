/**
 * 自分のシグネチャを決めましょう
 *
 * Author : kwaka1208
 * URL    : http://kwaka1208.net/
*/
//#include <library.h>	// ライブラリを使う場合は、ヘッダーのインクルードが必要。

#define CONST_VALUE 0	// プログラム中で使う値は、定数として定義しましょう。リテラル（値をそのまま記述すること）はできるだけ避ける。

/**
 * グローバル変数・定数定義
*/
enum {
	GREEN = 1,				// 連続した値を定義する時は、enumが便利
	YELLOW,					// GREENが"1"なので、YELLOWはGREENに"1"を足した"2"となる。
	RED
};

int global_var;				// グローバル変数は、関数の外に記述。
volatile int interupt_var;	// 割り込み処理で使う変数には、"volatile"を付ける。

/**
 * @brief 初期化処理
*/
void setup() {
	/*
		ここは起動時に一回だけ実行される。
		メモリーやポート（ピン）の初期化を行う。
	*/


	/**
	 * 割り込み処理を使う場合は、対応するピンの初期化と割り込み処理関数の登録を行う。
	 * 割り込み処理に対応するピンは2と3のみ。それぞれ以下の通り対応する。
	 * デジタルピン2：割り込み処理0
	 * デジタルピン3：割り込み処理1
	*/

	pinMode(2, INPUT_PULLUP);				// デジタルピン2の初期化
	attachInterrupt(0, interupt0, FALLING);	// 割り込み0（デジタルピン3が変化した時）の処理関数登録。

	pinMode(3, INPUT_PULLUP);				// デジタルピン3の初期化
	attachInterrupt(1, interupt1, FALLING);	// 割り込み1（デジタルピン3が変化した時）の処理関数登録。
}

/**
 * @brief メイン処理
*/
void loop() {

}

/**
 * @brief 割り込み0用処理
*/
void interupt0() {

}

/**
 * @brief 割り込み1用処理
*/
void interupt1() {

}
