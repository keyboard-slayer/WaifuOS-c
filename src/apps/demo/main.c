/**
 * Copyright (C) 2022 Keyboard Slayer
 *
 * This file is part of waifuOS.
 *
 * waifuOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * waifuOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with waifuOS.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stddef.h>
#include <ui/app.h>

static size_t btn_click_count = 0;

void
btn_click_func(ui_win_t *win)
{
	btn_click_count++;
	win->refresh();
}

void
win_main(ui_win_t *win)
{
	/* clang-format off */
    win->push(
        ui_text("You have clicked the button %d", btn_click_count)
    );

    win->push(
        ui_btn(btn_click_func, "Click on me")
    );
	/* clang-format on */
}

int
main(void)
{
	/* clang-format off */
	ui_apprun(
        win_main,
        "Button clicker"
    );

	/* clang-format on */
	return 0;
}
