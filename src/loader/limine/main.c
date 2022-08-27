#include "limine.h"

extern void bootstrap(void);

volatile struct limine_entry_point_request entry_point = {
	LIMINE_ENTRY_POINT_REQUEST, 0, 0, bootstrap
};
