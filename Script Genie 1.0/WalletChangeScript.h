#pragma once
#include "ScriptWindow.h"

class WalletChangeScript : public ScriptWindow
{
public:
	WalletChangeScript(int x, int y, int width, int height, char* title);
	~WalletChangeScript();

private:
	inline void cb_generate();

	//create input boxes
	Fl_Multiline_Input* psq_number;
	Fl_Multiline_Input* user_name;//add to window
	Fl_Multiline_Input* date;
	Fl_Multiline_Input* settlement_id;
	Fl_Multiline_Input* member_account_from;
	Fl_Multiline_Input* member_account_to;

};
