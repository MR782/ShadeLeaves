#pragma once
#include"Object.h"

class ClearGaugeFream : public Object {
	int gauge_fream_graph;
	int fream_accessories;//ƒtƒŒ[ƒ€‚Ì‘•ü•”
public:
	void initialize()override;
	void finalize()override;
	void draw(bool a_blend = false);
};