#pragma once
#include <DxLib.h>
	class ObjectBase;

	class ComponentBase{
	public:
		ComponentBase();
		~ComponentBase();
		virtual bool Init();
		virtual void Update();
		virtual void Render();
		virtual void Debug();

		void SetParent(ObjectBase* parent) { _parent = parent; }
	protected:
		ObjectBase* _parent;
	};


