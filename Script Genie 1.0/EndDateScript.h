#pragma once
#include "ScriptWindow.h"

class EndDateScript : public ScriptWindow
{
public:
	EndDateScript(int x, int y, int width, int height, char* title);
	~EndDateScript();

private:
	//create generate callback
	inline void cb_generate();

	//create input boxes
	Fl_Multiline_Input* psq_number;
	Fl_Multiline_Input* user_name;
	Fl_Multiline_Input* date;
	Fl_Multiline_Input* end_date;
	Fl_Multiline_Input* member_enrollment_id;
	Fl_Multiline_Input* member_account_id;

};

