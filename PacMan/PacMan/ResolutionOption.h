#ifndef RESOLUTIONOPTION_H
#define RESOLUTIONOPTION_H
#include "Menu.h"
class ResolutionOption : public Menu
{
public:
	ResolutionOption(std::stack<State*>* states_in, HGE* hge_in);
	//Update
	virtual void Update(const float& dt) override;
	//Render
	virtual void Render() override;
	
	virtual void UpdateInput(const float& dt) override;
	virtual ~ResolutionOption();
private:
	void SetPreference(const int& width, const int& height, const std::string& resol);
	void ChangeResolution();
	bool isWindowed;
	bool tempWindowed;
	int tempWidth;
	int tempHeight;
	std::string tempRes;
};
#endif
