#include <stddef.h>

#include "limine.h"

extern void bootstrap(void);

/* clang-format off */
volatile struct limine_entry_point_request entry_point = {
	.id = LIMINE_ENTRY_POINT_REQUEST,
	.entry = bootstrap
};

volatile struct limine_kernel_file_request kfile_req = {
	.id = LIMINE_KERNEL_FILE_REQUEST
};

uintptr_t 
loader_get_kfile(void)
{
	if (kfile_req.response == NULL)
	{
		return 0;
	}

	return (uintptr_t) kfile_req.response->kernel_file->address;
}
