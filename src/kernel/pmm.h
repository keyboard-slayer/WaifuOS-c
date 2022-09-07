#ifndef KERNEL_PMM_H
#define KERNEL_PMM_H

#include <stddef.h>
#include <stdint.h>

void pmm_free(uint64_t, uint64_t);
void pmm_init(void);
void *pmm_alloc(size_t);
void *pmm_alloc_page(size_t);
size_t pmm_available_pages(void);

#endif /* !KERNEL_PMM_H */
