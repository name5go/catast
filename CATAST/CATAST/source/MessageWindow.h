/*****************************************************************//**
 * \file   MessageWindow.h
 * \brief  メッセージが表示されるウィンドウ
 * 
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
class MessageWindow : public ObjectBase
{
public:
	MessageWindow();
	~MessageWindow();
	void Init()override;
	void Update(InputManager& input)override;
	void Render()override;
	void Debug()override;
	bool SetMassage(std::string name,std::string message);
private:

	//表示用にセットする内容
	int _cg;//描画するキャラ画像
	std::string _nameText;//描画する名前
	std::string _message;//描画する全文
	std::array<int, 10> _insetImageList;//文中に挿入できる画像

	//中揃え用情報
	int _messageWidth;//全文の幅px
	int _lineMax;//全文中の行数

	//メッセージ描画中に使用する変数
	int _drawingByte;//何バイト目の文字を描画しているか
	int _drawingPositionX;//描画している文字のX座標px
	int _drawingLine;//描画している文字の行数
	float _time;//最後尾の文字を描画し始めてから経過した時間(sec)
	int _color;//文字色
	float _wait;//文字描画を始めるまでの待機時間(sec)
	int _drawingImage;//文中に挿入される画像

	bool _messageFinished;//全文表示完了フラグ

	int _fontSize;
	int _font;//フォントハンドル

	int _screen;//フレームバッファ


};

