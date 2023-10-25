/*
	hfd
*/

#pragma once

#include <libpond/pond.h>
#include <libpond/Event.h>
#include <libgraphics/Font.h>
#include "libui/widget/Widget.h"
#include "Window.h"
#include "Poll.h"
#include "Timer.h"
#include "Theme.h"
#include "DrawContext.h"
#include <libapp/App.h>

namespace UI {
	extern Pond::Context* pond_context;

	void init(char** argv, char** envp);
	void run();
	void run_while(std::function<bool()> predicate);
	void update(int timeout);
	bool ready_to_exit();

	void set_timeout(std::function<void()> func, int interval);
	Duck::Ptr<Timer> set_interval(std::function<void()> func, int interval);
	void remove_timer(int id);

	bool set_app_name(const std::string& app_name);
	App::Info& app_info();

	void add_poll(const Poll& poll);

	Duck::Ptr<const Gfx::Image> icon(Duck::Path path);

	void __register_window(const std::shared_ptr<Window>& window, int id);
	void __deregister_window(int id);
}

