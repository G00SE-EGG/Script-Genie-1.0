#pragma once

#include "ScriptWindow.h"
#include <iostream>

class EffetDateScript : public ScriptWindow
{
public:
	EffetDateScript(int x, int y, int width, int height, char* title);
	~EffetDateScript();

private:
	inline void cb_generate();

	//create input boxes
	Fl_Multiline_Input* psq_number;
	Fl_Multiline_Input* user_name;//add to window
	Fl_Multiline_Input* date;
	Fl_Multiline_Input* effective_date;
	Fl_Multiline_Input* member_enrollment_id;
	Fl_Multiline_Input* member_account_id;//add to window
};

