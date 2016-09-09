#include "ScriptWindow.h"


ScriptWindow::ScriptWindow(int x, int y, int width, int height, char* title)
	:Fl_Window(x, y, width, height, title),
	parameter_check(false)
{
	begin();
	//btn_generate = new Fl_Button(100,400, 70, 40, "Generate");
	end();
	show();
}


ScriptWindow::~ScriptWindow()
{
}

void ScriptWindow::cb_generate_i(Fl_Widget* w, void* v)
{
	((ScriptWindow*)v)->cb_generate();
}

void ScriptWindow::cb_generate()
{

}

void ScriptWindow::cb_close_i(Fl_Widget* w, void* v)
{
	((ScriptWindow*)v)->cb_close();
}
void ScriptWindow::cb_close()
{
	hide();
}
