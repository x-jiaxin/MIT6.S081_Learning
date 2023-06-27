#include <iostream>
#define PTE_V (1L << 0)// valid
#define PTE_R (1L << 1)
#define PTE_W (1L << 2)
#define PTE_X (1L << 3)
#define PTE_U (1L << 4)// user can access
#define MAXVA (1L << (9 + 9 + 9 + 12 - 1))
#define PGSIZE 4096// bytes per page
#define TRAMPOLINE (MAXVA - PGSIZE)
#define TRAPFRAME (TRAMPOLINE - PGSIZE)
#define USYSCALL (TRAPFRAME - PGSIZE)
//#define ADD (1L << 2)
int main()
{
    //    std::cout << PTE_V << std::endl;
    //    std::cout << PTE_R << std::endl;
    //    std::cout << PTE_W << std::endl;
    //    std::cout << PTE_X << std::endl;
    //    std::cout << PTE_U << std::endl;
    //    std::cout << MAXVA << std::endl;
    //    std::cout << TRAMPOLINE << std::endl;
    //    std::cout << TRAPFRAME << std::endl;
    //    std::cout << USYSCALL << std::endl;
    //    std::cout << ADD << std::endl;
    //    ((1 << 1) | (1 << 2) | (1 << 30))
    std::cout << (1 << 1) << std::endl;
    std::cout << (1 << 2) << std::endl;
    std::cout << (1 << 30) << std::endl;
    return 0;
}
