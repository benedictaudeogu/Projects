
.data					# section declaration

        # Useful offset constants for accessing members of a 
        # struct mp1_blink_struct structure
        LOCATION   = 0    
        ON_CHAR    = 2
        OFF_CHAR   = 3 
        ON_LENGTH  = 4
        OFF_LENGTH = 6
        COUNTDOWN  = 8
        STATUS     = 10
        NEXT       = 12

        STRUCT_SIZE = 16

# Pointer to head of list (initialized to NULL)
mp1_list_head:
        .long   0

.text					# section declaration

jump_table:
        .long mp1_ioctl_add, mp1_ioctl_remove, mp1_ioctl_find, mp1_ioctl_sync

# Export the function symbol names

.global mp1_rtc_tasklet
.global mp1_ioctl

# void mp1_poke(void);
#
# Interface: Register-based arguments (not C-style)
#    Inputs: %cl  - The byte you wish to write
#            %eax - Offset from the start of video memory that you wish
#                   to write to
#   Outputs: Text-mode video screen is written to at location %eax with
#            the byte in %cl
# Registers: Clobbers EDX
mp1_poke:

	movl    vmem_base_addr(,1),%edx
	movb    %cl,(%edx,%eax,1)
	ret

# void mp1_rtc_tasklet(unsigned long);
#
# Interface: Register-based arguments (not C-style)
#    Inputs: %esi  - List head pointer
#            COUNTDOWN - Number of RTC interrupts left in period
#            STATUS - Status word (on=1/off=0)
#            ON_LENGTH - Length of on period
#            OFF_LENGTH - Length of off period
#            ON_CHAR - Char to put during "on" period
#            OFF_CHAR - Char to put during "off" period
#            LOCATION - Linear offset on text-mode buffer       
#            NEXT - pointer to next item in linked list      
#   Outputs: Updates linked list based on RTC interrupt
mp1_rtc_tasklet:
        pushl %ebp
        movl %esp, %ebp
        pushl %ebx                      # stranger doing callee saving
        pushl %edi
        pushl %esi

        movl mp1_list_head, %esi        # esi = head
        
start:
        cmpl $0, %esi                   # returns when it reaches the end of list: node->next = null
        je end_tasklet
        decw COUNTDOWN(%esi)
        cmpw $0, COUNTDOWN(%esi)
        jne update
        cmpw $1, STATUS(%esi)
        je on 
        cmpw $0, STATUS(%esi)
        je off 

update:
        movl NEXT(%esi), %esi           # move on to next list item
        jmp start
        
end_tasklet:
        popl %esi                       # stranger doing callee restore
        popl %edi
        popl %ebx
        leave
        ret
on:    
        movb OFF_CHAR(%esi), %cl
        xorl %eax, %eax
        movw LOCATION(%esi), %ax
        shll $1, %eax                   # eax = location*2 = offset
        call mp1_poke                   # cl=0, eax = offset
        movw $0, STATUS(%esi)
        movw OFF_LENGTH(%esi), %bx
        movw %bx, COUNTDOWN(%esi)
        jmp update                      # node success
        
off:    
        movb ON_CHAR(%esi), %cl
        xorl %eax, %eax
        movw LOCATION(%esi), %ax
        shll $1, %eax
        call mp1_poke                   # cl=1, eax = offset
        movw $1, STATUS(%esi)
        movw ON_LENGTH(%esi), %bx
        movw %bx, COUNTDOWN(%esi)
        jmp update                      # node success

# int mp1_ioctl(unsigned long arg, unsigned long cmd);
#
# Interface: Register-based arguments (not C-style)
#    Inputs: %eax - <command number> - implicates which core function to run
#            %edi - <arg> -> copy from struct pointer                      
#   Outputs: Uses jump table to exceute core functions
mp1_ioctl:                              # callee

        movl 8(%esp), %eax              # eax = <cmd>
        movl 4(%esp), %edi              # edi = <arg>
        cmpl $0, %eax
        jb return                       # < 0
        cmpl $3, %eax
        ja return                       # > 3
        jmp *jump_table(, %eax, 4)
        ret

# int mp1_ioctl_add(unsigned long arg);
#
# Interface: Register-based arguments and C-style
#    Inputs: %edi - <arg> -> copy from address struct pointer 
#            %eax - copy to address struct pointer
#            STATUS - Status word (on=1/off=0)
#            ON_LENGTH - Length of on period
#            ON_CHAR - Char to put during "on" period
#            NEXT - pointer to next item in linked list   
#            LOCATION - Linear offset on text-mode buffer            
#   Outputs: Blinking location added
mp1_ioctl_add:
        pushl %ebp
        movl %esp, %ebp
        pushl %ebx                      # stranger doing callee saving
        pushl %edi
        pushl %esi

        # call mp1_malloc
        cmpl $0, %edi                   # valid <arg>
        je return_malloc_failed
        push $STRUCT_SIZE               # argument for mp_malloc
        call mp1_malloc                 # returns pointer where to place struct
        addl $4, %esp                                                   
        cmpl $0, %eax                   # null check
        je return_malloc_failed
        movl %eax, %ebx                 # store pointer EBX = malloc pointer
        
        # copy struct
        push $STRUCT_SIZE               # n parameter
        pushl %edi                      # *from parameter
        pushl %eax                      # *to parameter
        call mp1_copy_from_user
        addl $12,%esp 
        cmpl $0, %eax
        jne return                      # meaning copy failed
        
        # copy success, check bounds
        movl %ebx, %eax                 # restore pointer
        movw LOCATION(%eax), %bx        
        cmpw $1999, %bx
        ja return                       # out of bounds
        cmpw $0, %bx
        jb return                       # out of bounds

        # we are within bounds
        movw ON_LENGTH(%eax), %bx                               
        movw %bx, COUNTDOWN(%eax)       # set countdown to on_length
        movw $1, STATUS(%eax)           # set status field to 1
                
        # Linked List                   # edi = next node->next
        movl mp1_list_head, %esi        # esi = head
        movl %esi, NEXT(%eax)           # new node->next = head
        movl %eax, mp1_list_head        # insert structure at head of linked list(esi = eax)   (eax = struct)
        movl %eax, %ebx                 # copy pointer
        
        # call mp1_poke
        movb ON_CHAR(%eax), %cl         # cl = byte                          
        xorl %edi, %edi
        movw LOCATION(%eax), %di        # alternative: movzwl LOCATION(%eax), %edi -> edi = offset, zwl ---> zero, word-to-long
        shll $1, %edi                                           
        movl %edi, %eax                 # eax = offset
        pushl %edx
        call mp1_poke                   
        popl %edx
        andl $0, %eax                   # all success                                                                
        jmp done_add

return_malloc_failed:
        movl $-1, %eax
        jmp done_add

# malloc success, but copy failed, so we free
return:                                 
        pushl %eax
        call mp1_free
        addl $4, %esp 
        movl $-1, %eax                  

done_add:
        popl %esi                       # stranger doing callee restore
        popl %edi
        popl %ebx
        leave
        ret

# int mp1_ioctl_remove(unsigned long arg); 
#
# Interface: Register-based arguments and C-style
#    Inputs: %edi - <arg> -> Location to be removed(Not pointer)
#            %esi - List head pointer
#            NEXT - Pointer to next item in linked list  
#            LOCATION - Linear offset on text-mode buffer   
#   Outputs: Remove a blinking location   
mp1_ioctl_remove:
        pushl %ebp
        movl %esp, %ebp
        pushl %ebx                      # stranger doing callee saving
        pushl %edi
        pushl %esi

# search list for element with same address as location
        movl mp1_list_head, %esi
        movl mp1_list_head, %eax
        
search_head:       
        cmpl $0, %esi
        je return_malloc_failed
        movw LOCATION(%esi), %dx        # list location
        cmpw %dx, %di                   # di = short of arg provided 
        je remove_head
        movl NEXT(%esi), %esi 

search_else:       
        cmpl $0, %esi
        je return_malloc_failed
        movw LOCATION(%esi), %dx
        cmpw %dx, %di
        je remove_else
        movl %esi, %eax                 # store previous node
        movl NEXT(%esi), %esi
        jmp search_else

remove_head:
        movl %esi, %eax                 # head to delete
        movl NEXT(%esi), %esi
        movl %esi, mp1_list_head
        pushl %eax
        call mp1_free
        addl $4, %esp
        andl $0, %eax                   # all success                                                                
        jmp done_add

remove_else:
        movl %esi, %ecx                 # not head to delete
        movl NEXT(%esi), %ebx           # new next
        movl %ebx, NEXT(%eax)
        pushl %ecx
        call mp1_free
        addl $4, %esp
        andl $0, %eax                   # all success                                                                
        jmp done_add    

# int mp1_ioctl_find(unsigned long arg); 
#    Inputs: %edi - <arg> -> struct pointer
#            %esi - List head pointer
#            LOCATION - Linear offset on text-mode buffer
#            NEXT - Pointer to next item in linked list     
#   Outputs: Get information about a location  
mp1_ioctl_find:
        pushl %ebp
        movl %esp, %ebp
        pushl %ebx                      # stranger doing callee saving
        pushl %edi
        pushl %esi

        cmpl $0, %edi
        je return_malloc_failed         # null check

# search list for element with same address as location
        movl mp1_list_head, %esi        #
search_find:       
        cmpl $0, %esi
        je return_malloc_failed
        movw LOCATION(%esi), %ax
        shll $1, %eax
        movw LOCATION(%edi), %bx  
        cmpw %ax, %bx
        je found_location
        movl NEXT(%esi), %esi           #
        jmp search_find 

found_location:
        push $STRUCT_SIZE               # n parameter
        pushl %esi                      # *from parameter
        pushl %edi                      # *to parameter
        call mp1_copy_to_user
        addl $12, %esp
        andl $0, %eax                   # all success                                                                
        jmp done_add    

# int mp1_ioctl_sync(unsigned long arg);
#    Inputs: %edi - <arg> -> Location to be removed(Not pointer)
#                 - 2 16 bit location in edi
#            %esi - List head pointer
#            LOCATION - Linear offset on text-mode buffer
#            NEXT - Pointer to next item in linked list     
#   Outputs: Synchronize a new blink location with an existing one  
mp1_ioctl_sync:
        pushl %ebp
        movl %esp, %ebp
        pushl %ebx                      # stranger doing callee saving
        pushl %edi
        pushl %esi

        movl mp1_list_head, %esi        # head

        # get locations
        xorw %cx, %cx
        movl %edi, %ecx                 # second integer - location first blinking char
        shrl $16, %edi    
        xorw %bx, %bx
        movl %edi, %ebx                 # first integer - location second blinking char

search_sync:
        cmpl $0, %esi
        je return_malloc_failed
        movw LOCATION(%esi), %ax        # list location
        cmpw %ax, %bx
        je save
        movl NEXT(%esi), %esi
        jmp search_sync
save:
        movl %esi, %edi                 # save first pointer
        movl mp1_list_head, %esi        # head

found_first:
        cmpl $0, %esi
        je return_malloc_failed
        movw LOCATION(%esi), %ax        # list location
        cmpw %ax, %cx
        je found_second
        movl NEXT(%esi), %esi
        jmp found_first

found_second:
        movl %esi, %edx                 # save second pointer
        movw ON_LENGTH(%edi), %ax
        movw %ax, ON_LENGTH(%edx)

        movw OFF_LENGTH(%edi), %ax
        movw %ax, OFF_LENGTH(%edx)

        movw COUNTDOWN(%edi), %ax
        movw %ax, COUNTDOWN(%edx)

        movw STATUS(%edi), %ax
        movw %ax, STATUS(%edx)

        andl $0, %eax                    # all success
        jmp done_add                   

.end
