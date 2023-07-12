#include "floatx.h"
#include "bitFields.h"
#include <assert.h>
#include <limits.h> // for CHAR_BIT - number of bits per byte
#include <math.h> // for isinf and isnan

union hexDouble {
  double dbl;
  unsigned long lng;
};

floatx doubleToFloatx(double val,int totBits,int expBits) {

/*-----------------------------------------------------------------------------------------------
	From the README: 	At a high level, doing the conversion requires several manipulations:
	1. Extracting the sign bit from the double value, and inserting it into the floatx value at
		the correct position.
	2. Handle special cases, such as 0.0, infinity, or not-a-number.
	3. Extract the biased exponent from the double value.
			Check to see if the double value is sub-normal. If so, handle it.
			Check to make sure the floatx exponent won't overflow or underflow).
					If so, handle as a special case.
			If not, rebias the exponent using the floatx bias (which depends on the number of exponent bits)
			and write the result to the correct location in the floatx result.
	4. Extract the fraction bits from the double value.
			Determine how many bits are available for the fraction in the floatx value,
			and truncate or extend the original value,
			and write the resulting bits to the floatx result.
	6. Return the floatx result.
----------------------------------------------------------------------------------------------------*/

	// First, make some assertions to ensure the totBits and expBits parameters are OK
	// Then, implement the algorithm

	assert(totBits <= 64 && totBits > 0);
	assert(totBits - expBits > 1 && expBits > 0);
	
	union hexDouble temp;	
	union hexDouble answer;	
	
	temp.dbl = val;

	//unsigned long valL = unionVal.lng;	
	//unionVal.lng = 0;
	
	answer.lng = 0;
	
	//formatting floatx
	int fracBits = totBits - expBits - 1;
	
	if(getBit(63, temp.lng)){
		setBit(totBits-1, 1, &(answer.lng));
	} else {
		setBit(totBits-1, 0, &(answer.lng));
	}
	
	unsigned long bias = (1L << (expBits-1)) - 1;
	unsigned long valExp = getBitFldU(62, 11, temp.lng);
	valExp = getBitFldU(10, 11, valExp);
	valExp = valExp - 1023;
	valExp = valExp + bias;
	
	unsigned long valFrac = getBitFld(51, 52, temp.lng);
	
	if(valExp > (bias*2)){
		unsigned long uno = (1L << (63-1)) - 1;
		unsigned long none = 0;	
		if(isnan(val)){
			setBitFld(expBits-1, expBits, uno, &valExp);
			setBit(0, 1, &valFrac);
			setBitFld(totBits-2, expBits, valExp, &(answer.lng));
			setBitFld(fracBits-1, fracBits, valFrac, &(answer.lng));
			return answer.lng;
		} else {
			setBitFld(expBits-1, expBits, uno, &valExp);
			setBitFld(fracBits-1, fracBits, none, &valFrac);
			setBitFld(totBits-2, expBits, valExp, &(answer.lng));
			setBitFld(fracBits-1, fracBits, valFrac, &(answer.lng));
			return answer.lng;
		}
	}
	
	valFrac = getBitFld(51, fracBits, valFrac);
	
	
	if(valExp == 0){
		if(valFrac == 0)	{
			//special case 0
			return 0;
		} else {
			//special case subnormal
			return 0;	
		}
	}
	
	setBitFld(totBits-2, expBits, valExp, &(answer.lng));
	setBitFld(fracBits-1, fracBits, valFrac, &(answer.lng));
	
	return answer.lng;
}