#include "StageDataExporter.h"
#include <fstream>

void StageDataExporter::Export(ObjectServer& objectServer,int stageNumber)
{
	picojson::array gimmcikList;

	for (auto&& object : objectServer.GetObjects()) {
		picojson::object gimmick;
		if (object->GetName() == "gimmick") {
			gimmick.insert(std::make_pair("type",picojson::value(static_cast<double>(1))));
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
