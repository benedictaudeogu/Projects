#ifndef _LOAD_PAGIN_H
#define _LOAD_PAGING_H

extern void loadPageDirectory(page_dir_t*);
extern void enablePaging();
extern void flushTLB();

#endif
