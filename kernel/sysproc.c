#include "types.h"
#include "riscv.h"
#include "param.h"
#include "defs.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64 sys_exit(void)
{
    int n;
    argint(0, &n);
    exit(n);
    return 0;// not reached
}

uint64 sys_getpid(void) { return myproc()->pid; }

uint64 sys_fork(void) { return fork(); }

uint64 sys_wait(void)
{
    uint64 p;
    argaddr(0, &p);
    return wait(p);
}

uint64 sys_sbrk(void)
{
    uint64 addr;
    int n;

    argint(0, &n);
    addr = myproc()->sz;
    if (growproc(n) < 0) return -1;
    return addr;
}

uint64 sys_sleep(void)
{
    int n;
    uint ticks0;

    argint(0, &n);
    acquire(&tickslock);
    ticks0 = ticks;
    while (ticks - ticks0 < n) {
        if (killed(myproc())) {
            release(&tickslock);
            return -1;
        }
        sleep(&ticks, &tickslock);
    }
    release(&tickslock);
    return 0;
}

#ifdef LAB_PGTBL
int sys_pgaccess(void)
{
    // lab pgtbl: your code here.
    int nums;
    uint64 va_head, user_bit_mask_addr;
    //    用户页面的起始va地址
    argaddr(0, &va_head);
    //    页数
    argint(1, &nums);
    if (nums > 32) {
        printf("page nums is too many!\n");
        return -1;
    }
    //    用户态存掩码的变量地址
    argaddr(2, &user_bit_mask_addr);
    //    当前页掩码
    int kernel_res_mask = 0;

    //    遍历va
    for (int i = 0; i < nums; i++) {
        uint64 va = va_head + i * PGSIZE;
        int this_page_mask = 0;
        if (va >= MAXVA) return 0;
        //        根据va和初始页表地址查找pte
        pte_t *pte = walk(myproc()->pagetable, va, 0);
        if (pte == 0) return 0;
        //        命中
        if ((*pte & PTE_A) != 0) {
            this_page_mask = 1;
            *pte = *pte & (~PTE_A);
        }
        kernel_res_mask = kernel_res_mask | this_page_mask << i;
    }
    if (copyout(myproc()->pagetable, user_bit_mask_addr, (char *)&kernel_res_mask,
                sizeof(kernel_res_mask)) < 0) {
        return -1;
    }
    return 0;
}
#endif

uint64 sys_kill(void)
{
    int pid;

    argint(0, &pid);
    return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64 sys_uptime(void)
{
    uint xticks;

    acquire(&tickslock);
    xticks = ticks;
    release(&tickslock);
    return xticks;
}
