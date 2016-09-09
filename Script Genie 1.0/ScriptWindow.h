#pragma once

#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Multiline_Input.H>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>


class ScriptWindow : public Fl_Window
{
public:
	ScriptWindow(int x, int y, int width, int height, char* title);
	~ScriptWindow();

protected:
	//create string for script name
	std::string filename;
	/*create file streams for reading template
	and writing new script based on template
	*/
	std::ifstream input_stream;
	std::ofstream output_stream;

	//get script name
	std::string script_name;
	std::string username;
	//check to see if all parameters are filled in
	bool parameter_check;
	//make buttons protected
	Fl_Button* btn_generate;

	//make callbacks virtual functions
	static void cb_generate_i(Fl_Widget* w, void* v);
	//each derived class will have to handle its
	//generate separate
	virtual inline void cb_generate() = 0;

	//close window
	static void cb_close_i(Fl_Widget* w, void* v);
	inline void cb_close();
};

