/*****************************************************************//**
 * \file   EditorUICreater.h
 * \brief  ステージエディタ用のUIを配置するクラス
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#include "EditorUICreater.h"
#include "EditorButton.h"
#include "ObjectListWindow.h"
#include "Dummy.h"
#include "DummySpike.h"
#include "DummyBounce.h"
#include "DummyWarp.h"
#include "DummyBlink.h"
#include "StageDataExporter.h"
#include "StageDataImporter.h"
#include "EditStageSelectWindow.h"
#include "EditorCamera.h"
#include "XYZLine.h"
#include "EditorSelectMarker.h"
#include <windows.h>

void EditorUICreater::CreateUI(ObjectServer& objectServer)
{

	objectServer.Add(std::make_unique<XYZLine>());


	auto list = std::make_unique<ObjectListWindow>();

	objectServer.Add(std::make_unique<EditorCamera>(*list));
	objectServer.Add(std::make_unique<EditorSelectMarker>(*list));

	auto upButton = std::make_unique<EditorButton>(*list);
	upButton->SetPosition({ 1890.0f,16.0f,0.0f });
	upButton->SetText("↑");
	auto upList = [&](ObjectListWindow* list) {
		list->ScrollUp();
	};
	upButton->SetActivateFunction(upList);
	objectServer.Add(std::move(upButton));

	auto downButton = std::make_unique<EditorButton>(*list);
	downButton->SetPosition({ 1890.0f,400.0f,0.0f });
	downButton->SetText("↓");
	auto downList = [&](ObjectListWindow* list) {
		list->ScrollDown();
	};
	downButton->SetActivateFunction(downList);
	objectServer.Add(std::move(downButton));


	AddObjectUI(objectServer, *list);
	TransformUI(objectServer,*list);
	FileUI(objectServer, *list);
	End(objectServer, *list);

	auto stageSelect = std::make_unique<EditStageSelectWindow>(*list);
	stageSelect->SetPosition({0.0f, 30.0f, 0.0f});
	stageSelect->SetVisible(false);
	objectServer.Add(std::move(stageSelect));

	auto deleteButton = std::make_unique<EditorButton>(*list);
	deleteButton->SetPosition({ 1400.0f,0.0f,0.0f });
	deleteButton->SetText("選択オブジェクト削除");
	auto deleteObject = [&](ObjectListWindow* list) {
		auto deletePtr =objectServer.Get(list->GetSelectID());
		if (deletePtr != nullptr) {
			deletePtr->Dead();
		}
	};
	deleteButton->SetActivateFunction(deleteObject);
	objectServer.Add(std::move(deleteButton));

	auto button13 = std::make_unique<EditorButton>(*list);
	button13->SetPosition({ 75.0f,0.0f,0.0f });
	button13->SetText("ステージ選択");
	button13->SetUnpushedMessage("stageSelectOff");
	auto selectFileOn = [&](ObjectListWindow* list) {
		for (auto&& object:objectServer.GetObjects()) {
			object->MessageEvent(nullptr, "stageSelectOn");
			object->MessageEvent(nullptr, "fileOff");
			object->MessageEvent(nullptr, "systemOff");
			object->MessageEvent(nullptr, "objectOff");
		}
	};
	auto selectFileOff = [&](ObjectListWindow* list) {
		for (auto&& object : objectServer.GetObjects()) {
			object->MessageEvent(nullptr, "stageSelectOff");
		}
	};
	button13->SetToggle(true);
	button13->SetActivateFunction(selectFileOn);
	button13->SetNonActivateFunction(selectFileOff);
	objectServer.Add(std::move(button13));

	objectServer.Add(std::move(list));
}

void EditorUICreater::DeleteUI(ObjectServer& objectServer)
{
}

void EditorUICreater::AddObjectUI(ObjectServer& objectServer, ObjectListWindow& list)
{
	float x{182.0f};

	auto buttonSystem = std::make_unique<EditorButton>(list);
	buttonSystem->SetPosition({ x,0.0f,0.0f });
	buttonSystem->SetText("オブジェクト追加");
	buttonSystem->SetUnpushedMessage("objectOff");
	auto systemOpen = [&](ObjectListWindow* list) {
		for (auto&& object : objectServer.GetObjects()) {
			object->MessageEvent(nullptr, "objectOn");
			object->MessageEvent(nullptr, "systemOff");
			object->MessageEvent(nullptr, "stageSelectOff");
			object->MessageEvent(nullptr, "fileOff");
		}
	};
	auto systemClose = [&](ObjectListWindow* list) {
		for (auto&& object : objectServer.GetObjects()) {
			object->MessageEvent(nullptr, "objectOff");
		}
	};
	buttonSystem->SetToggle(true);
	buttonSystem->SetActivateFunction(systemOpen);
	buttonSystem->SetNonActivateFunction(systemClose);
	objectServer.Add(std::move(buttonSystem));

	auto button = std::make_unique<EditorButton>(list);
	button->SetVisible(false);
	button->SetVisibleMessage("objectOn");
	button->SetInvisibleMessage("objectOff");
	button->SetPosition({ x,20.0f,0.0f });
	button->SetText("ターゲット");
	auto addObject = [&](ObjectListWindow*) {objectServer.Add(std::make_unique<Dummy>()); };
	button->SetActivateFunction(addObject);
	objectServer.Add(std::move(button));

	auto button2 = std::make_unique<EditorButton>(list);
	button2->SetVisible(false);
	button2->SetVisibleMessage("objectOn");
	button2->SetInvisibleMessage("objectOff");
	button2->SetPosition({ x,40.0f,0.0f });
	button2->SetText("一方向");
	auto addSpike = [&](ObjectListWindow*) {objectServer.Add(std::make_unique<DummySpike>()); };
	button2->SetActivateFunction(addSpike);
	objectServer.Add(std::move(button2));

	auto bounce = std::make_unique<EditorButton>(list);
	bounce->SetVisible(false);
	bounce->SetVisibleMessage("objectOn");
	bounce->SetInvisibleMessage("objectOff");
	bounce->SetPosition({ x,60.0f,0.0f });
	bounce->SetText("反射");
	auto addBounce = [&](ObjectListWindow*) {objectServer.Add(std::make_unique<DummyBounce>()); };
	bounce->SetActivateFunction(addBounce);
	objectServer.Add(std::move(bounce));

	auto warp = std::make_unique<EditorButton>(list);
	warp->SetVisible(false);
	warp->SetVisibleMessage("objectOn");
	warp->SetInvisibleMessage("objectOff");
	warp->SetPosition({ x,80.0f,0.0f });
	warp->SetText("ワープ");
	auto addWarp = [&](ObjectListWindow*) {objectServer.Add(std::make_unique<DummyWarp>()); };
	warp->SetActivateFunction(addWarp);
	objectServer.Add(std::move(warp));

	auto blink = std::make_unique<EditorButton>(list);
	blink->SetVisible(false);
	blink->SetVisibleMessage("objectOn");
	blink->SetInvisibleMessage("objectOff");
	blink->SetPosition({ x,100.0f,0.0f });
	blink->SetText("透明");
	auto addBlink = [&](ObjectListWindow*) {objectServer.Add(std::make_unique<DummyBlink>()); };
	blink->SetActivateFunction(addBlink);
	objectServer.Add(std::move(blink));
}

void EditorUICreater::TransformUI(ObjectServer& objectServer, ObjectListWindow& list)
{
	float xPosition{ 1650.0f };
	float yPosition{ 400.0f };

	auto button2 = std::make_unique<EditorButton>(list);
	button2->SetPosition({ xPosition,yPosition+30.0f,0.0f });
	button2->SetText("X+");
	auto addX = [&](ObjectListWindow* list) {
		auto obj = objectServer.Get(list->GetSelectID());
		if (obj == nullptr) { return; }
		obj->SetPosition(VAdd(obj->GetPosition(), { 10.0f,0.0f,0.0f }));
	};
	button2->SetActivateFunction(addX);
	objectServer.Add(std::move(button2));

	
	auto button3 = std::make_unique<EditorButton>(list);
	button3->SetPosition({ xPosition+40.0f,yPosition+30.0f,0.0f });
	button3->SetText("X-");
	auto subX = [&](ObjectListWindow* list) {
		auto obj = objectServer.Get(list->GetSelectID());
		if (obj == nullptr) { return; }
		obj->SetPosition(VAdd(obj->GetPosition(), { -10.0f,0.0f,0.0f }));
	};
	button3->SetActivateFunction(subX);
	objectServer.Add(std::move(button3));
	
	auto button4 = std::make_unique<EditorButton>(list);
	button4->SetPosition({ xPosition+40.0f,yPosition+50.0f,0.0f });
	button4->SetText("Y+");
	auto addY = [&](ObjectListWindow* list) {
		auto obj = objectServer.Get(list->GetSelectID());
		if (obj == nullptr) { return; }
		obj->SetPosition(VAdd(obj->GetPosition(), { 0.0f,10.0f,0.0f }));
	};
	button4->SetActivateFunction(addY);
	objectServer.Add(std::move(button4));

	auto button5 = std::make_unique<EditorButton>(list);
	button5->SetPosition({ xPosition,yPosition+50.0f,0.0f });
	button5->SetText("Y-");
	auto subY = [&](ObjectListWindow* list) {
		auto obj = objectServer.Get(list->GetSelectID());
		if (obj == nullptr) { return; }
		obj->SetPosition(VAdd(obj->GetPosition(), { 0.0f,-10.0f,0.0f }));
	};
	button5->SetActivateFunction(subY);
	objectServer.Add(std::move(button5));

	auto button6 = std::make_unique<EditorButton>(list);
	button6->SetPosition({ xPosition+40.0f,yPosition+70.0f,0.0f });
	button6->SetText("Z+");
	auto addZ = [&](ObjectListWindow* list) {
		auto obj = objectServer.Get(list->GetSelectID());
		if (obj == nullptr) { return; }
		obj->SetPosition(VAdd(obj->GetPosition(), { 0.0f,0.0f,10.0f }));
	};
	button6->SetActivateFunction(addZ);
	objectServer.Add(std::move(button6));

	auto button7 = std::make_unique<EditorButton>(list);
	button7->SetPosition({ xPosition,yPosition+70.0f,0.0f });
	button7->SetText("Z-");
	auto subZ = [&](ObjectListWindow* list) {
		auto obj = objectServer.Get(list->GetSelectID());
		if (obj == nullptr) { return; }
		obj->SetPosition(VAdd(obj->GetPosition(), { 0.0f,0.0f,-10.0f }));
	};
	button7->SetActivateFunction(subZ);
	objectServer.Add(std::move(button7));

	auto button8 = std::make_unique<EditorButton>(list);
	button8->SetPosition({ xPosition,yPosition+90.0f,0.0f });
	button8->SetText("+X方向");
	auto rotX = [&](ObjectListWindow* list) {
		auto obj = objectServer.Get(list->GetSelectID());
		if (obj == nullptr) { return; }
		obj->SetRotation({ 0.0f,3.1415 / 2,0.0f });
	};
	button8->SetActivateFunction(rotX);
	objectServer.Add(std::move(button8));

	auto Xminus = std::make_unique<EditorButton>(list);
	Xminus->SetPosition({ xPosition+60.0f,yPosition + 90.0f,0.0f });
	Xminus->SetText("-X方向");
	auto rotXminus = [&](ObjectListWindow* list) {
		auto obj = objectServer.Get(list->GetSelectID());
		if (obj == nullptr) { return; }
		obj->SetRotation({ 0.0f,-3.1415 / 2,0.0f });
	};
	Xminus->SetActivateFunction(rotXminus);
	objectServer.Add(std::move(Xminus));

	auto button9 = std::make_unique<EditorButton>(list);
	button9->SetPosition({ xPosition,yPosition+110.0f,0.0f });
	button9->SetText("+Y方向");
	auto rotY = [&](ObjectListWindow* list) {
		auto obj = objectServer.Get(list->GetSelectID());
		if (obj == nullptr) { return; }
		obj->SetRotation({ -3.1415 / 2,0.0f,0.0f });
	};
	button9->SetActivateFunction(rotY);
	objectServer.Add(std::move(button9));

	auto Yminus = std::make_unique<EditorButton>(list);
	Yminus->SetPosition({ xPosition + 60.0f,yPosition + 110.0f,0.0f });
	Yminus->SetText("-Y方向");
	auto rotYminus = [&](ObjectListWindow* list) {
		auto obj = objectServer.Get(list->GetSelectID());
		if (obj == nullptr) { return; }
		obj->SetRotation({ 3.1415 / 2,0.0f,0.0f });
	};
	Yminus->SetActivateFunction(rotYminus);
	objectServer.Add(std::move(Yminus));

	auto button10 = std::make_unique<EditorButton>(list);
	button10->SetPosition({ xPosition,yPosition+130.0f,0.0f });
	button10->SetText("+Z方向");
	auto rotZ = [&](ObjectListWindow* list) {
		auto obj = objectServer.Get(list->GetSelectID());
		if (obj == nullptr) { return; }
		obj->SetRotation({ 0.0f,0.0f,0.0f });
	};
	button10->SetActivateFunction(rotZ);
	objectServer.Add(std::move(button10));

	auto Zminus = std::make_unique<EditorButton>(list);
	Zminus->SetPosition({ xPosition+60,yPosition + 130.0f,0.0f });
	Zminus->SetText("-Z方向");
	auto rotZminus = [&](ObjectListWindow* list) {
		auto obj = objectServer.Get(list->GetSelectID());
		if (obj == nullptr) { return; }
		obj->SetRotation({ 0.0f,3.1415,0.0f });
	};
	Zminus->SetActivateFunction(rotZminus);
	objectServer.Add(std::move(Zminus));
	
}

void EditorUICreater::FileUI(ObjectServer& objectServer, ObjectListWindow& list)
{
	auto button11 = std::make_unique<EditorButton>(list);
	button11->SetPosition({ 0.0f,20.0f,0.0f });
	button11->SetText("ファイル書き出し");
	button11->SetVisibleMessage("fileOn");
	button11->SetInvisibleMessage("fileOff");
	button11->SetVisible(false);
	auto selectFile = [&](ObjectListWindow* list) {
		StageDataExporter exporter;
		exporter.Export(objectServer, list->GetSelectStage());
	};
	button11->SetActivateFunction(selectFile);
	objectServer.Add(std::move(button11));

	auto button12 = std::make_unique<EditorButton>(list);
	button12->SetPosition({ 0.0f,40.0f,0.0f });
	button12->SetText("ファイル読み込み");
	button12->SetVisibleMessage("fileOn");
	button12->SetInvisibleMessage("fileOff");
	button12->SetVisible(false);
	auto loadFile = [&](ObjectListWindow* list) {
		StageDataImporter importer;
		std::vector<StageDataImporter::GimmickData> gimmickData;
		importer.Import(list->GetSelectStage(), gimmickData);
		for (auto&& gimmick : gimmickData) {
			if (gimmick.Type == 1) {
				auto target = std::make_unique<Dummy>();
				target->SetPosition(gimmick.Position);
				target->SetRotation(gimmick.Rotation);
				target->SetScale(gimmick.Scale);
				objectServer.Add(std::move(target));
			}
		}
	};
	button12->SetActivateFunction(loadFile);
	objectServer.Add(std::move(button12));

	auto button = std::make_unique<EditorButton>(list);
	button->SetPosition({ 0.0f,0.0f,0.0f });
	button->SetText("ファイル");
	button->SetUnpushedMessage("fileOff");
	auto selectFileOn = [&](ObjectListWindow* list) {
		for (auto&& object : objectServer.GetObjects()) {
			object->MessageEvent(nullptr, "fileOn");
			object->MessageEvent(nullptr, "stageSelectOff");
			object->MessageEvent(nullptr, "systemOff");
			object->MessageEvent(nullptr, "objectOff");
		}
	};
	auto selectFileOff = [&](ObjectListWindow* list) {
		for (auto&& object : objectServer.GetObjects()) {
			object->MessageEvent(nullptr, "fileOff");
		}
	};
	button->SetToggle(true);
	button->SetActivateFunction(selectFileOn);
	button->SetNonActivateFunction(selectFileOff);
	objectServer.Add(std::move(button));
}

void EditorUICreater::End(ObjectServer& objectServer, ObjectListWindow& list)
{
	float x{ 321.0f };
	auto buttonSystem = std::make_unique<EditorButton>(list);
	buttonSystem->SetPosition({ x,0.0f,0.0f });
	buttonSystem->SetText("システム");
	buttonSystem->SetUnpushedMessage("systemOff");
	auto systemOpen = [&](ObjectListWindow* list) {
		for (auto&& object : objectServer.GetObjects()) {
			object->MessageEvent(nullptr, "systemOn");
			object->MessageEvent(nullptr, "stageSelectOff");
			object->MessageEvent(nullptr, "fileOff");
			object->MessageEvent(nullptr, "objectOff");
		}
	};
	auto systemClose = [&](ObjectListWindow* list) {
		for (auto&& object : objectServer.GetObjects()) {
			object->MessageEvent(nullptr, "systemOff");
		}
	};
	buttonSystem->SetToggle(true);
	buttonSystem->SetActivateFunction(systemOpen);
	buttonSystem->SetNonActivateFunction(systemClose);
	objectServer.Add(std::move(buttonSystem));

	auto buttonEnd = std::make_unique<EditorButton>(list);
	buttonEnd->SetPosition({ x,20.0f,0.0f });
	buttonEnd->SetText("エディター終了");
	buttonEnd->SetVisibleMessage("systemOn");
	buttonEnd->SetInvisibleMessage("systemOff");
	buttonEnd->SetVisible(false);
	auto endFunc = [&](ObjectListWindow* list) {
		for (auto&& object : objectServer.GetObjects()) {
			if (object->GetName() == "editor") {
				object->Dead();
			}
		}
	};
	buttonEnd->SetActivateFunction(endFunc);
	objectServer.Add(std::move(buttonEnd));
}