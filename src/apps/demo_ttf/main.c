/**
 * Copyright (C) 2022 Keyboard Slayer & contributor
 *
 * This file is part of WaifuOS.
 *
 * WaifuOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WaifuOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WaifuOS.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <ui/app.h>

/* void
appmain(ui_win_t *win)
{
	win->push(
		win,
		ui_text("Hello, World !"));
}
 */
int
main(void)
{
	ui_load_font("media/fonts/roboto/Roboto-Regular.ttf");
	/* 	ui_app_run(appmain, "DemoTTF"); */
	return 0;
}
