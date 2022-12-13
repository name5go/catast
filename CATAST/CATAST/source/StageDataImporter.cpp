#include "StageDataImporter.h"
#include <fstream>

bool StageDataImporter::Import(int stage, std::vector<GimmickData>& container)
{
	// ファイルからjsonデータの読み込み
	std::ifstream ifs("res/Stage/Stage" + std::to_string(stage) + ".json");
	picojson::value json;
	ifs >> json;

	const std::string err = picojson::get_last_error();

	if (!err.empty()) {
		return false;
	}

	container.clear();

	picojson::array root = json.get<picojson::array>();
	for (int i = 0; i < root.size(); ++i) {
		auto objectData = root[i].get<picojson::object>();
		GimmickData data;
		data.Type = static_cast<int>(objectData["type"].get<double>());
		data.Position.x = static_cast<float>(objectData["positionX"].get<double>());
		data.Position.y = static_cast<float>(objectData["positionY"].get<double>());
		data.Position.z = static_cast<float>(objectData["positionZ"].get<double>());
		data.Rotation.x = static_cast<float>(objectData["rotationX"].get<double>());
		data.Rotation.y = static_cast<float>(objectData["rotationY"].get<double>());
		data.Rotation.z = static_cast<float>(objectData["rotationZ"].get<double>());
		data.Scale.x = static_cast<float>(objectData["scaleX"].get<double>());
		data.Scale.y = static_cast<float>(objectData["scaleY"].get<double>());
		data.Scale.z = static_cast<float>(objectData["scaleZ"].get<double>());

		container.push_back(data);
	}

	return true;
}
