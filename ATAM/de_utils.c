#include <asm/desc.h>

void my_store_idt(struct desc_ptr *idtr) {
//# <STUDENT FILL>
	// TODO: if we omit inline assembly:  store_idt(&tmpidtr);
	asm volatile("SIDT %0;":"=m"(*idtr));
// </STUDENT FILL>
}

void my_load_idt(struct desc_ptr *idtr) {
// <STUDENT FILL>
	// if we omit inline assembly: load_idt(addr);
	asm volatile("LIDT %0;"::"m"(*idtr));
// <STUDENT FILL>
}

void my_set_gate_offset(gate_desc *gate, unsigned long addr) {
// <STUDENT FILL>
	// TODO: pack_gate(gate, GATE_INTERRUPT, addr, 0, 0, __KERNEL_CS);
	unsigned long temp = addr;
	unsigned short low = temp;
	unsigned short mid;
	unsigned int high;
	temp = temp>>16;
	mid = (unsigned short) temp;
	temp = temp>>16;
	high = (unsigned int) temp; 
	asm volatile("movw %%dx, %%ax;"
		     "movw %%si, %%bx;"
		     "movl %%edi, %%ecx;"
		     :"=a"(gate->offset_low), "=b"(gate->offset_middle), "=c"(gate->offset_high)
			: "d"(low), "S"(mid), "D"(high));  
	
// </STUDENT FILL>
}

unsigned long my_get_gate_offset(gate_desc *gate) {
// <STUDENT FILL>
	// TODO: return gate_offset(gate);
	unsigned long result;
	unsigned short low = gate->offset_low;
	unsigned short mid = gate->offset_middle;
	unsigned int high = gate->offset_high;
	asm volatile("xorq %%rdx,%%rdx;"
		     "movl %%ecx,%%edx;"
		     "shlq $16,%%rdx;"
		     "movw %%bx,%%dx;"
		     "shlq $16,%%rdx;"
		     "movw %%ax,%%dx;"	
 		     :"=d"(result)
		     :"a"(low),"b"(mid),"c"(high));
	return result;

// </STUDENT FILL>
}
