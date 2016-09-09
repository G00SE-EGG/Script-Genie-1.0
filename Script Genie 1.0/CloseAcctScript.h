#pragma once
#include "ScriptWindow.h"


class CloseAcctScript : public ScriptWindow
{
public:
	CloseAcctScript(int x, int y, int width, int height, char* title);
	~CloseAcctScript();

private:
	inline void cb_generate();

	//create input boxes
	Fl_Multiline_Input* psq_number;
	Fl_Multiline_Input* user_name;//add to window
	Fl_Multiline_Input* date;
	Fl_Multiline_Input* member_account_id;//add to window
};

