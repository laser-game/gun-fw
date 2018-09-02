/* ----------------------------------------------------------------------
 * Copyright (C) 2010-2014 ARM Limited. All rights reserved.
 *
 * $Date:        19. March 2015
 * $Revision:   V.1.4.5
 *
 * Project:         CMSIS DSP Library
 * Title:		arm_power_f32.c
 *
 * Description:	Sum of the squares of the elements of a floating-point vector.
 *
 * Target Processor: Cortex-M4/Cortex-M3/Cortex-M0
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *   - Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   - Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   - Neither the name of ARM LIMITED nor the names of its contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * ---------------------------------------------------------------------------- */

#include "arm_math.h"

/**
 * @ingroup groupStats
 */

/**
 * @defgroup power Power
 *
 * Calculates the sum of the squares of the elements in the input vector.
 * The underlying algorithm is used:
 *
 * <pre>
 *  Result = pSrc[0] * pSrc[0] + pSrc[1] * pSrc[1] + pSrc[2] * pSrc[2] + ... + pSrc[blockSize-1] * pSrc[blockSize-1];
 * </pre>
 *
 * There are separate functions for floating point, Q31, Q15, and Q7 data types.
 */

/**
 * @addtogroup power
 * @{
 */


/**
 * @brief Sum of the squares of the elements of a floating-point vector.
 * @param[in]       *pSrc points to the input vector
 * @param[in]       blockSize length of the input vector
 * @param[out]      *pResult sum of the squares value returned here
 * @return none.
 *
 */


void arm_power_f32(
    float32_t *pSrc,
    uint32_t   blockSize,
    float32_t *pResult)
{
    float32_t sum = 0.0f; /* accumulator */
    float32_t in;         /* Temporary variable to store input value */
    uint32_t blkCnt;      /* loop counter */

    #ifndef ARM_MATH_CM0_FAMILY

    /* Run the below code for Cortex-M4 and Cortex-M3 */

    /*loop Unrolling */
    blkCnt = blockSize >> 2u;

    /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.
    ** a second loop below computes the remaining 1 to 3 samples. */
    while (blkCnt > 0u)
    {
        /* C = A[0] * A[0] + A[1] * A[1] + A[2] * A[2] + ... + A[blockSize-1] * A[blockSize-1] */
        /* Compute Power and then store the result in a temporary variable, sum. */
        in   = *pSrc++;
        sum += in * in;
        in   = *pSrc++;
        sum += in * in;
        in   = *pSrc++;
        sum += in * in;
        in   = *pSrc++;
        sum += in * in;

        /* Decrement the loop counter */
        blkCnt--;
    }

    /* If the blockSize is not a multiple of 4, compute any remaining output samples here.
    ** No loop unrolling is used. */
    blkCnt = blockSize % 0x4u;


    #else  /* ifndef ARM_MATH_CM0_FAMILY */

    /* Run the below code for Cortex-M0 */

    /* Loop over blockSize number of values */
    blkCnt = blockSize;

    #endif /* #ifndef ARM_MATH_CM0_FAMILY */


    while (blkCnt > 0u)
    {
        /* C = A[0] * A[0] + A[1] * A[1] + A[2] * A[2] + ... + A[blockSize-1] * A[blockSize-1] */
        /* compute power and then store the result in a temporary variable, sum. */
        in   = *pSrc++;
        sum += in * in;

        /* Decrement the loop counter */
        blkCnt--;
    }

    /* Store the result to the destination */
    *pResult = sum;
} /* arm_power_f32 */

/**
 * @} end of power group
 */
