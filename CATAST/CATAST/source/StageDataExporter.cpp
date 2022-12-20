/*****************************************************************//**
 * \file   StageDataExporter.cpp
 * \brief  ステージデータのエクスポート機能を持つクラス
 * 
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/

void StageDataExporter::Export(ObjectServer& objectServer,int stageNumber)
{
	picojson::array gimmcikList;

	for (auto&& object : objectServer.GetObjects()) {
		picojson::object gimmick;
		if (object->GetName() == "gimmick") {
			int type{ 1 };
			if (object->CheckType<DummySpike>()) {
				type = 2;
			}else if (object->CheckType<DummyBounce>()) {
				type = 3;
			}else if (object->CheckType<DummyWarp>()) {
				type = 4;
			}
			else if (object->CheckType<DummyBlink>()) {
				type = 5;
			}
			gimmick.insert(std::make_pair("type",picojson::value(static_cast<double>(type))));
			auto position=object->GetPosition();
			gimmick.insert(std::make_pair("positionX", picojson::value(static_cast<double>(position.x))));
			gimmick.insert(std::make_pair("positionY", picojson::value(static_cast<double>(position.y))));
			gimmick.insert(std::make_pair("positionZ", picojson::value(static_cast<double>(position.z))));
			auto rotation = object->GetRotation();
			gimmick.insert(std::make_pair("rotationX", picojson::value(static_cast<double>(rotation.x))));
			gimmick.insert(std::make_pair("rotationY", picojson::value(static_cast<double>(rotation.y))));
			gimmick.insert(std::make_pair("rotationZ", picojson::value(static_cast<double>(rotation.z))));
			auto scale = object->GetScale();
			gimmick.insert(std::make_pair("scaleX", picojson::value(static_cast<double>(scale.x))));
			gimmick.insert(std::make_pair("scaleY", picojson::value(static_cast<double>(scale.y))));
			gimmick.insert(std::make_pair("scaleZ", picojson::value(static_cast<double>(scale.z))));

			gimmcikList.emplace_back(gimmick);
		}
	}
	std::ofstream ofs("res/Stage/Stage"+ std::to_string(stageNumber) + ".json");
	ofs << picojson::value(gimmcikList).serialize(true)<<std::endl;
}
