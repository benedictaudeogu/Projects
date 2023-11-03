#define ASM 1

.text
.globl loadPageDirectory, enablePaging, flushTLB
            
# Loading the page directory into the cr3 register.
loadPageDirectory:             
    pushl %ebp                      
    movl %esp, %ebp                 
    movl 8(%esp), %eax              
    movl %eax, %cr3                
    movl %ebp, %esp                 
    popl %ebp                       
    ret     

# setting bits that allow for page dir and page tables to be used.
enablePaging:                  
    pushl %ebp        
    movl %esp, %ebp
    movl %cr4, %eax
    orl $0x00000090, %eax
    movl %eax, %cr4                 
    movl %cr0, %eax                 
    orl $0x80000001, %eax           
    movl %eax, %cr0                 
    movl %ebp, %esp      
    popl %ebp                       
    ret

# resetting value in cr3 register
flushTLB:
    movl %cr3, %eax
    movl %eax, %cr3
    ret
