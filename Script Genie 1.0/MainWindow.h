#pragma once

#include <FL\Fl.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Text_Display.H>
#include <iostream>
#include "EffetDateScript.h"
#include "EndDateScript.h"
#include "DelEmailsScript.h"
#include "CloseAcctScript.h"
#include "UpdPmtStatScript.h"
#include "WalletChangeScript.h"
#include "UnverifyTxnScript.h"
#include "RmvTermSepScript.h"
#include "ReactHSAScript.h"
#include "AutoAdjScript.h"
#include "BalanceAdjScript.h"

class MainWindow : public Fl_Window
{
public:
	MainWindow();
	~MainWindow();

private:
	int _screen_width;
	int _screen_height;

	/* read in description of a script based on selected script
	*/
	std::ifstream script_desc_stream;

	int script_type = 0;

	//this function returs script descriptions
	std::string getDesc(int);

	//create choices dropdown
	Fl_Choice* script_choices;
	static void cb_choices_i(Fl_Widget* w, void* v);
	inline void cb_choices();
	/*
	Create function that converts enum to script template
	name, then use that to dynamically add names to list
	for(int i =0; i < choices.size(); i++)
	choices->add(convertChoice(c[i]);?
	*/

	//Add box to window that display what script does
	Fl_Text_Display* description;
	Fl_Text_Buffer* buff;

	/*Create buttons for selecting script and
	add new script
	also add callbacks
	*/
	Fl_Button* btn_use_script;
	static void cb_select_i(Fl_Widget* w, void* v);
	inline void cb_select();

	Fl_Button* btn_add_new_script;
	//static void cb_add_i(Fl_Widget* w, void* v);
	//inline void cb_add();

	/*Creates script windows
	using pointer i will be able to use one base
	to serve for all script types
	ParameterWindow* win;

	switch()
	case 1:
	win = new CoverageEffectiveWindow();
	*/
	//Coverage effective date
	ScriptWindow* script_window;

};

