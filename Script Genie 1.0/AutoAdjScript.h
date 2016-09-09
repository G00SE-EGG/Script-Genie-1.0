#pragma once
#include "ScriptWindow.h"
class AutoAdjScript : public ScriptWindow
{
public:
	AutoAdjScript(int x, int y, int width, int height, char* title);
	~AutoAdjScript();

private:
	inline void cb_generate();

	//create input boxes
	Fl_Multiline_Input* psq_number;
	Fl_Multiline_Input* user_name;//add to window
	Fl_Multiline_Input* date;
	Fl_Multiline_Input* employer_id;
	Fl_Multiline_Input* employee_id;
	Fl_Multiline_Input* card_transaction_id;//add to window
};

