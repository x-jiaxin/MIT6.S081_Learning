#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
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

uint64 sys_getpid(void)
{
    return myproc()->pid;
}

uint64 sys_fork(void)
{
    return fork();
}

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
    //    myproc()->sz = myproc()->sz + n;
    if (growproc(n) < 0)
        return -1;
    return addr;
}

uint64 sys_sleep(void)
{
    int n;
    uint ticks0;

    argint(0, &n);
    if (n < 0)
        n = 0;
    acquire(&tickslock);
    ticks0 = ticks;
    while (ticks - ticks0 < n)
    {
        if (killed(myproc()))
        {
            release(&tickslock);
            return -1;
        }
        sleep(&ticks, &tickslock);
    }
    backtrace();
    release(&tickslock);
    return 0;
}

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

void sys_myt()
{
    struct proc *p = myproc();
    printf("kernel_trap:%p\n", (void *)p->trapframe->kernel_trap);
}

uint64 sys_sigalarm(void)
{
    printf("sys_sigalarm\n");
    int tick;
    uint64 funcaddr;
    argint(0, &tick);
    argaddr(1, &funcaddr);
    //    printf("tick: %d\n", tick);
    //    printf("funcaddr: %p\n", funcaddr);
    struct proc *p = myproc();
    p->alarm_interval = tick;
    p->alarm_ticks = tick;
    p->alarm_handler = funcaddr;
    return 0;
}
uint64 sys_sigreturn(void)
{
    printf("sys_return\n");
    struct proc *p = myproc();
    *p->trapframe = *p->alarm_trapframe;
    p->alarm_running = 0;
    //    test3
    return p->trapframe->a0;
}