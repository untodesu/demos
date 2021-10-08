#ifndef ARCH_PAGING_H
#define ARCH_PAGING_H 1

#define PG_SHIFT            (12)
#define PG_ALIGN            (4096)
#define PG_COUNT            (1024)

#define PGDIR_INDEX_MASK    (0x3FF)
#define PGDIR_INDEX_SHIFT   (22)
#define PGDIR_INDEX(addr)   (((addr) >> PGDIR_INDEX_SHIFT) & PGDIR_INDEX_MASK)

#define PGTAB_INDEX_MASK    (0x3FF)
#define PGTAB_INDEX_SHIFT   (12)
#define PGTAB_INDEX(addr)   (((addr) >> PGTAB_INDEX_SHIFT) & PGTAB_INDEX_MASK)

#define PDE_PRESENT         (1 << 0)
#define PDE_READ_WRITE      (1 << 1)
#define PDE_USER            (1 << 3)
#define PDE_WRITE_THROUGH   (1 << 4)
#define PDE_CACHE_DISABLED  (1 << 5)
#define PDE_ACCESSED        (1 << 6)
#define PDE_PAGE_SIZE       (1 << 7)
#define PDE_IGNORED         (1 << 8)

#define PTE_PRESENT         (1 << 0)
#define PTE_READ_WRITE      (1 << 1)
#define PTE_USER            (1 << 2)
#define PTE_WRITE_THROUGH   (1 << 3)
#define PTE_CACHE_DISABLED  (1 << 4)
#define PTE_ACCESSED        (1 << 5)
#define PTE_DIRTY           (1 << 6)
#define PTE_GLOBAL          (1 << 8)

#endif
