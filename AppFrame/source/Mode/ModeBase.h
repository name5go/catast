#pragma once
#include <memory>
#include <string>

class InputManager;
class ObjectServer;

class ModeServer;

	class		ModeBase
	{
	public:
		ModeBase();
		virtual ~ModeBase();

		virtual bool	Initialize();
		virtual bool	Terminate();
		virtual bool	Update(InputManager& input);
		virtual bool	Render();
		virtual bool	Debug();

		//このモードが始まってからのカウンタ
		int	GetModeCount() { return _cntMode; }			
		//このモードが始まってからの時間ms
		unsigned long GetModeTime() { return _tmMode; }	
		//前フレームからの経過時間ms
		unsigned long GetStepTime() { return _tmStep; }	
		// 何フレームに1回Process()を呼ぶか(def:1)
		void SetCallPerFrame(int frame) { _callPerFrame = _callPerFrame_cnt = frame; }	
		// 1回の呼び出しに何回Process()を呼ぶか(def:1)
		void SetCallOfCount(int count) { _callOfCount = count; }	
		// 何フレームに1回Process()を呼ぶか(def:1)
		int GetCallPerFrame() { return _callPerFrame; }
		// 1回の呼び出しに何回Process()を呼ぶか(def:1)
		int GetCallOfCount() { return _callOfCount; }

		int GetLayer() { return _layer; }
		void SetLayer(int value) { _layer = value; }
		int GetUID() { return _uid; }
		void SetUID(int value) { _uid = value; }
		std::string GetSZName() { return _szName; }
		void SetSZName(std::string string) { _szName = string; }

		// 時間経過をさせる
		void StepTime(unsigned long tmNow);
		// カウントを進める
		void StepCount();

		std::unique_ptr<ObjectServer>& GetObjectServer() { return _objectServer; }

	private:
		// ModeServer用
		std::string		_szName;
		int				_uid;
		int				_layer;

		// モード内処理用
		int		_cntMode;	// 本モードに入ってからのカウンタ, 0スタート
		unsigned long	_tmMode;	// 本モードに入ってからの時間。ms
		unsigned long	_tmStep;	// 前フレームからの経過時間。ms
		unsigned long	_tmModeBase;	// このモードが始まった時間。ms
		unsigned long	_tmPauseBase;	// ポーズ中のベース時間。ms
		unsigned long	_tmPauseStep;	// ポーズ中の積算時間。ms 動作中、この値を _tmMode に用いる
		unsigned long	_tmOldFrame;	// 前フレームの時間。ms

		// CallPerFrame / CallOfCount用
		int		_callPerFrame, _callPerFrame_cnt;
		int		_callOfCount;

	protected:
		std::unique_ptr<ObjectServer> _objectServer;
	};