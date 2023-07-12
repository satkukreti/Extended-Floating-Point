#include "bitFields.h"
#include <assert.h>

int getBit(int bn,unsigned long val) {
	// TODO:
	//		check to make sure bn is a valid bit position in long 
	//		(you may assert this is true)
	//		If the bit in val at position bn is 1, return 1
	//		otherwise return 0.
	assert(bn < 64 && bn >=0);
	
	unsigned long temp = 1UL << bn;
	unsigned long determine = val ^ 	temp;
		
	if(determine > val){
		return 0;			
	} else {
		return 1;			
	}

}

void setBit(int bn,int new,unsigned long *val) {
	// TODO:
	//		check to make sure bn is a valid bit position in long (you may assert 
	//		this is true)
	//		if new is true, set the bit in val at bn to 1
	//     otherwise, set the bit in val at bn to 0
	
	assert(bn < 64 && bn >=0);
		
	if(new){
		*val |= (1UL << bn);
	} else {
		*val &= (~(1UL << bn));
	}

}

long getBitFld(int bs,int len,unsigned long val) {
	// TODO:
	//		check to make sure bs is a valid bit position in long (you may assert this is 
	//		true)
	//		check to make sure len is a valid length for a subfield that starts at bs 
	//		(you may assert this is true)
	// 		perform an unsigned getBitFldU to extract the unsigned version of the field
	//		get the high order bit of the result... that's the "sign" bit
	//		if the sign bit not zero, replace the 0 padding with 1 padding
	assert(bs < 64 && bs >=0);
	assert((bs-len+1) >= 0);	
	
	unsigned long toReturn = getBitFldU(bs, len, val);
			
	if(getBit(len-1, val)){	
		unsigned long mask = ~((1UL << len) - 1);		
		toReturn |= mask;
	}
	return toReturn;

	
}

unsigned long getBitFldU(int bs,int len,unsigned long val) {
	// TODO:
	//		check to make sure bs is a valid bit position in long 
	//		(you may assert this is true)
	//		check to make sure len is a valid length for a subfield that starts at bs 
	//		(you may assert this is true)
	// 		make a mask that has len 1's
	// 		Shift that mask left so it's leftmost 1 starts at bs
	//      bitwise and the mask and val to isolate the bit field bits
	//		Shift the result to the right so that the rightmost bit of the bit field is 
	//		bit 0
	//			Note that shift right pads to the left with the sign bit if the field is 
	//		signed, but
	//			for unsigned, it will pad to the left with 0

	assert(bs < 64 && bs >=0);
	assert((bs-len+1) >= 0);
			
	unsigned long mask = (1UL << len) - 1;

	mask = mask << (bs-len+1);
	val &= mask;
			
	val = val >> (bs-len+1);			
	return val;
}

void setBitFld(int bs,int len,unsigned long new,unsigned long *val) {
	// TODO:
	//		check to make sure bs is a valid bit position in long 
	//			(you may assert this is true)
	//		check to make sure len is a valid length for a subfield that starts at bs 
	//			(you may assert this is true)
	//      Make a mask that has len bits, right justified
	//		Use mask to turn off any bits to the left of the bitField values in new
	// 		Shift both the new value and the mask to the correct bit position
	//		Turn off all bits in *val under the mask by bitwise anding with ~mask
	//		Or *val with new.  (new has zeros for all non bit field positions, 
	//			so won't affect val)
	
	assert(bs < 64 && bs >=0);
	assert((bs-len+1) >= 0);
	
	
	unsigned long mask = (1UL << len) - 1;
	
	new &= mask;
	new = new << (bs-len+1);
	mask = mask << (bs-len+1);
	
	*val &= ~mask;
	*val |= new;
}
