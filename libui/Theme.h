/*
	This file is part of duckOS.

	duckOS is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	duckOS is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with duckOS.  If not, see <https://www.gnu.org/licenses/>.

	Copyright (c) Byteduck 2016-2021. All rights reserved.
*/

#pragma once

#include <map>
#include <string>
#include <libgraphics/Graphics.h>
#include <libgraphics/Image.h>

#define LIBUI_THEME_DEFAULT "default"
#define LIBUI_THEME_LOCATION "/usr/share/themes/"

namespace UI {
	class Theme {
	public:
		Duck::Ptr<Gfx::Image> get_image(const std::string& key);
		int get_value(const std::string& key);
		Gfx::Color get_color(const std::string& key);
		std::string get_string(const std::string& key);
		Gfx::Font* get_font();
		Gfx::Font* get_font_mono();

		///STATIC
		static Theme* get_theme(const std::string& name);
		static Theme* current();
		static void load_config(std::map<std::string, std::string>& config);

		static Duck::Ptr<Gfx::Image> image(const std::string& key);
		static int value(const std::string& key);
		static Gfx::Color color(const std::string& key);
		static std::string string(const std::string& key);

		//Standard fonts
		static Gfx::Font* font();
		static Gfx::Font* font_mono();

		//Standard colors
		static Gfx::Color bg();
		static Gfx::Color fg();
		static Gfx::Color accent();
		static Gfx::Color window();
		static Gfx::Color window_title();
		static Gfx::Color window_title_unfocused();
		static Gfx::Color window_titlebar_a();
		static Gfx::Color window_titlebar_b();
		static Gfx::Color shadow_1();
		static Gfx::Color shadow_2();
		static Gfx::Color highlight();
		static Gfx::Color button();
		static Gfx::Color button_text();

		//Standard values
		static int button_padding();
		static int progress_bar_height();

	private:
		//STATIC
		static std::map<std::string, Theme*> themes;
		static Theme* _current;
		static std::string _current_theme_name;

		//NON-STATIC
		explicit Theme(std::string name);
		bool load();

		std::string name;
		std::map<std::string, Duck::Ptr<Gfx::Image>> images;
		std::map<std::string, Gfx::Color> colors;
		std::map<std::string, int> values;
		std::map<std::string, std::string> strings;

		std::string _font = "gohu-11";
		std::string _font_mono = "gohu-11";
		Duck::Ptr<Gfx::Image> blank_image = Gfx::Image::empty();
	};
}


