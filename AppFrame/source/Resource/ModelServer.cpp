#include "DxLib.h"
#include "ModelServer.h"

	std::unordered_map<std::string, int> ModelServer::_mapGraph;

	void ModelServer::Init() {
		_mapGraph.clear();
	}

	void ModelServer::Release() {
		ClearModel();
	}

	void ModelServer::ClearModel() {
		for (auto&& graph : _mapGraph) {
			DeleteGraph(graph.second);
		}
		_mapGraph.clear();
	}

	int ModelServer::Find(std::string filename)
	{
		auto itr = _mapGraph.find(filename);
		if (itr != _mapGraph.end()) {
			return itr->second;
		}
		return -1;
	}

	int ModelServer::Erase(std::string filename)
	{
		auto itr = _mapGraph.find(filename);
		if (itr != _mapGraph.end()) {
			_mapGraph.erase(itr);
			return 1;
		}
		return -1;
	}

	int ModelServer::LoadModel(std::string filename)
	{
		int cg = Find(filename);
		if (cg == -1) {
			cg = ::MV1LoadModel(filename.c_str());
			_mapGraph[filename] = cg;
		}
		cg = MV1DuplicateModel(cg);
		return cg;
	}