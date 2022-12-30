
bool StageDataImporter::Import(int stage, ObjectServer& objectServer)
{
	// ファイルからjsonデータの読み込み
	std::ifstream ifs("res/Stage/Stage" + std::to_string(stage) + ".json");
	picojson::value json;
	ifs >> json;

	const std::string err = picojson::get_last_error();

	if (!err.empty()) {
		return false;
	}

	picojson::array root = json.get<picojson::array>();
	for (int i = 0; i < root.size(); ++i) {
		auto objectData = root[i].get<picojson::object>();

		int type = static_cast<int>(objectData["type"].get<double>());
		std::unique_ptr<ObjectBase> data;
		
		switch (type) {
		case 1:
			data.reset(new Dummy());
			break;
		case 2:
			data.reset(new DummySpike());
			break;
		case 3:
			data.reset(new DummyBounce());
			break;
		case 4:
			data.reset(new DummyWarp());
			break;
		case 5:
			data.reset(new DummyBlink());
			break;
		}
		float posX = static_cast<float>(objectData["positionX"].get<double>());
		float posY = static_cast<float>(objectData["positionY"].get<double>());
		float posZ = static_cast<float>(objectData["positionZ"].get<double>());
		data->SetPosition({ posX, posY, posZ });
		float rotX = static_cast<float>(objectData["rotationX"].get<double>());
		float rotY = static_cast<float>(objectData["rotationY"].get<double>());
		float rotZ = static_cast<float>(objectData["rotationZ"].get<double>());
		data->SetRotation({rotX,rotY,rotZ});
		float scaleX = static_cast<float>(objectData["scaleX"].get<double>());
		float scaleY = static_cast<float>(objectData["scaleY"].get<double>());
		float scaleZ = static_cast<float>(objectData["scaleZ"].get<double>());
		data->SetScale({scaleX,scaleY,scaleZ });

		objectServer.Add(std::move(data));
	}

	return true;
}
