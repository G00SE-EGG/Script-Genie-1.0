#pragma once
#include "ScriptWindow.h"
#include <FL/Fl_Text_Editor.H>
#include <vector>
#include <iostream>


class DelEmailsScript : public ScriptWindow
{
public:
	DelEmailsScript(int x, int y, int width, int height, char* title);
	~DelEmailsScript();

private:
	inline void cb_generate();

	//create input boxes
	Fl_Multiline_Input* psq_number;
	Fl_Multiline_Input* user_name;//add to window
	Fl_Multiline_Input* date;

	//create a field to input text
	Fl_Text_Buffer* buff;
	Fl_Text_Editor* msg_que_log_id;

	//create vector to hold inputs
	std::vector<std::string> msg_log_ids;

	//create output stream for msg log ids
	std::ifstream msg_input_stream;
	std::ofstream msg_output_stream;
};

