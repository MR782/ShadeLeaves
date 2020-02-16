//メモリリークを調べる
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
#include<Windows.h>

#include "./dxlib/DxLib.h"
#include"SceneManager.h"
#include"KeyBoard.h"
#include"Mouse.h"
#include"ScreenSystem.h"
#include"ScreenFunction.h"

SceneManager* scene_manager;

// WinMain関数
int WINAPI WinMain(
	_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//メモリリーク確認
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//log.txtを作成しない
	SetOutApplicationLogValidFlag(FALSE);
	//バックグラウンドでも実行状態にする
	SetAlwaysRunFlag(TRUE);

	//画面サイズ設定
	{
		int id = MessageBox(NULL, TEXT("フルスクリーンモードで起動しますか？"),
			TEXT("初回起動時は「いいえ」をおススメします"), MB_YESNO | MB_ICONQUESTION);
		switch (id)
		{
		case IDYES:
			GetDefaultState(&ScreenData::width, &ScreenData::height, NULL);//フルスク設定
			break;
		case IDNO:
			ScreenData::width = 1024;
			ScreenData::height = 768;
			break;
		}
		SetGraphMode(ScreenData::width, ScreenData::height, 32);//ウィンドウのサイズを決める
		ChangeWindowMode(TRUE);// ウィンドウモード変更
	}
	//ウィンドウタイトル
	SetMainWindowText("ShadeLeaves");

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) { return -1; };//dxlibがないなら終了

	scene_manager = new SceneManager();//全てのシーンを総括するオブジェクトのインスタンス生成
	//-------------------------------------------------
	SetDrawScreen(DX_SCREEN_BACK);//裏画面設定

	//エラーが発生しているなら即座に終了
	try {
		ScreenFunction::initialize();//フェードアウト・インの初期化
		KeyBoard::initialize();//キーボード入力に必要なメモリ確保
		Mouse::initialize();//マウス入力をとるために必要な初期化処理
		if (scene_manager == nullptr) throw("scene_manager is null_ptr");
		scene_manager->initialize();//一部の画像や音楽ファイルを読み込む
		//画面更新＆メッセージ処理&画面殺害
		while ((ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)) {
			//ESCキーが押されたら終了
			if (KeyBoard::key_down(KEY_INPUT_ESCAPE))break;
			//入力関係---------------------------------------
			KeyBoard::update();//キーボード
			Mouse::update();//マウス
			//ゲーム内の更新と描画--------------------------
			if (scene_manager != nullptr) {
				scene_manager->update();
				scene_manager->draw();
			}
		}
		scene_manager->finalize();//データの中身削除
	}
	catch (const char* msg) {
		//なぜ例外が投げられたか知らせる
		MessageBox(NULL, msg, "ERROR", MB_OK);//WindowsAPI機能
	}
	KeyBoard::finalize();//使用したメモリの開放
	InitGraph();//dxlibの読み込んだ画像を全削除する関数
	InitFontToHandle();//dxlibの作成したフォントを全削除する関数
	InitSoundMem();//dxlibの読み込んだ音データを全削除する関数
	delete scene_manager;

	DxLib_End();			// ＤＸライブラリ使用の終了処理
	return 0;				// ゲーム終了
}
