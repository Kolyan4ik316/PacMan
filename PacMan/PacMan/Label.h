#ifndef LABEL_H
#define LABEL_H
#include "Widget.h"
class Label : public Widget
{
public:
	Label();
	void Update(const float dt) override;
	void Render(HGE *hge) override;
	virtual ~Label();
};
#endif