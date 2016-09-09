#pragma once
#include "ScriptWindow.h"
class RmvTermSepScript : public ScriptWindow
{
public:
	RmvTermSepScript(int x, int y, int width, int height, char* title);
	~RmvTermSepScript();

private:
	inline void cb_generate();

	//create input boxes
	Fl_Multiline_Input* psq_number;
	Fl_Multiline_Input* user_name;//add to window
	Fl_Multiline_Input* date;
	Fl_Multiline_Input* employee_id;

};

