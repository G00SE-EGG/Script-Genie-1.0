#pragma once
#include "ScriptWindow.h"
class ReactHSAScript : public ScriptWindow
{
public:
	ReactHSAScript(int x, int y, int width, int height, char* title);
	~ReactHSAScript();

private:
	inline void cb_generate();

	//create input boxes
	Fl_Multiline_Input* psq_number;
	Fl_Multiline_Input* user_name;//add to window
	Fl_Multiline_Input* date;
	Fl_Multiline_Input* effective_date;
	Fl_Multiline_Input* employee_id;

};

