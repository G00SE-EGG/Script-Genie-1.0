#pragma once
#include "ScriptWindow.h"

class UpdPmtStatScript : public ScriptWindow
{
public:
	UpdPmtStatScript(int x, int y, int width, int height, char* title);
	~UpdPmtStatScript();


private:
	inline void cb_generate();

	//create input boxes
	Fl_Multiline_Input* psq_number;
	Fl_Multiline_Input* user_name;//add to window
	Fl_Multiline_Input* date;
	Fl_Multiline_Input* payment_status;
	Fl_Multiline_Input* settlement_id;
};

