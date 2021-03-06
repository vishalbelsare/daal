/* file: service_heap.h */
/*******************************************************************************
* Copyright 2014-2017 Intel Corporation
* All Rights Reserved.
*
* If this  software was obtained  under the  Intel Simplified  Software License,
* the following terms apply:
*
* The source code,  information  and material  ("Material") contained  herein is
* owned by Intel Corporation or its  suppliers or licensors,  and  title to such
* Material remains with Intel  Corporation or its  suppliers or  licensors.  The
* Material  contains  proprietary  information  of  Intel or  its suppliers  and
* licensors.  The Material is protected by  worldwide copyright  laws and treaty
* provisions.  No part  of  the  Material   may  be  used,  copied,  reproduced,
* modified, published,  uploaded, posted, transmitted,  distributed or disclosed
* in any way without Intel's prior express written permission.  No license under
* any patent,  copyright or other  intellectual property rights  in the Material
* is granted to  or  conferred  upon  you,  either   expressly,  by implication,
* inducement,  estoppel  or  otherwise.  Any  license   under such  intellectual
* property rights must be express and approved by Intel in writing.
*
* Unless otherwise agreed by Intel in writing,  you may not remove or alter this
* notice or  any  other  notice   embedded  in  Materials  by  Intel  or Intel's
* suppliers or licensors in any way.
*
*
* If this  software  was obtained  under the  Apache License,  Version  2.0 (the
* "License"), the following terms apply:
*
* You may  not use this  file except  in compliance  with  the License.  You may
* obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*
* Unless  required  by   applicable  law  or  agreed  to  in  writing,  software
* distributed under the License  is distributed  on an  "AS IS"  BASIS,  WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
* See the   License  for the   specific  language   governing   permissions  and
* limitations under the License.
*******************************************************************************/

/*
//++
//  Implementation of heap algorithms.
//--
*/

#ifndef __SERVICE_HEAP_H__
#define __SERVICE_HEAP_H__

#include "daal_defines.h"
#include "service_utils.h"

namespace daal
{
namespace algorithms
{
namespace internal
{

using namespace services::internal;

template <CpuType cpu, typename T> DAAL_FORCEINLINE T heapLeftChildIndex(T index) { return 2 * index + 1; }
template <CpuType cpu, typename T> DAAL_FORCEINLINE T heapRightChildIndex(T index) { return 2 * index + 2; }
template <CpuType cpu, typename T> DAAL_FORCEINLINE T heapParentIndex(T index) { return (index - 1) / 2; }

template <CpuType cpu, typename RandomAccessIterator, typename Compare>
void pushMaxHeap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    if (first != last)
    {
        --last;
        auto i = last - first;
        if (i > 0)
        {
            const auto newItem = *last; // It can be moved instead.
            auto prev = i;
            for (i = heapParentIndex<cpu>(i); i && compare(*(first + i), newItem); i = heapParentIndex<cpu>(i))
            {
                *(first + prev) = *(first + i); // It can be moved instead.
                prev = i;
            }
            *(first + i) = newItem; // It can be moved instead.
        }
    }
}

template <CpuType cpu, typename RandomAccessIterator>
void pushMaxHeap(RandomAccessIterator first, RandomAccessIterator last)
{
    if (first != last)
    {
        --last;
        auto i = last - first;
        if (i > 0)
        {
            const auto newItem = *last; // It can be moved instead.
            auto prev = i;
            for (i = heapParentIndex<cpu>(i); i && (*(first + i) < newItem); i = heapParentIndex<cpu>(i))
            {
                *(first + prev) = *(first + i); // It can be moved instead.
                prev = i;
            }
            *(first + i) = newItem; // It can be moved instead.
        }
    }
}

template <CpuType cpu, typename RandomAccessIterator, typename Diff, typename Compare>
DAAL_FORCEINLINE void internalAdjustMaxHeap(RandomAccessIterator first, RandomAccessIterator /*last*/, Diff count, Diff i, Compare compare)
{
    for (auto largest = i;; i = largest)
    {
        const auto l = heapLeftChildIndex<cpu>(i);
        if ((l < count) && compare(*(first + largest), *(first + l)))
        {
            largest = l;
        }
        const auto r = heapRightChildIndex<cpu>(i);
        if ((r < count) && compare(*(first + largest), *(first + r)))
        {
            largest = r;
        }

        if (largest == i) { break; }
        iterSwap<cpu>(first + i, first + largest);
    }
}

template <CpuType cpu, typename RandomAccessIterator, typename Diff>
DAAL_FORCEINLINE void internalAdjustMaxHeap(RandomAccessIterator first, RandomAccessIterator /*last*/, Diff count, Diff i)
{
    for (auto largest = i;; i = largest)
    {
        const auto l = heapLeftChildIndex<cpu>(i);
        if ((l < count) && (*(first + largest) < *(first + l)))
        {
            largest = l;
        }
        const auto r = heapRightChildIndex<cpu>(i);
        if ((r < count) && (*(first + largest) < *(first + r)))
        {
            largest = r;
        }

        if (largest == i) { break; }
        iterSwap<cpu>(first + i, first + largest);
    }
}

template <CpuType cpu, typename RandomAccessIterator, typename Compare>
void popMaxHeap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    if (1 < last - first)
    {
        --last;
        iterSwap<cpu>(first, last);
        internalAdjustMaxHeap<cpu>(first, last, last - first, first - first, compare);
    }
}

template <CpuType cpu, typename RandomAccessIterator>
void popMaxHeap(RandomAccessIterator first, RandomAccessIterator last)
{
    if (1 < last - first)
    {
        --last;
        iterSwap<cpu>(first, last);
        internalAdjustMaxHeap<cpu>(first, last, last - first, first - first);
    }
}

template <CpuType cpu, typename RandomAccessIterator, typename Compare>
void makeMaxHeap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    const auto count = last - first;
    auto i = count / 2;
    while (0 < i) { internalAdjustMaxHeap<cpu>(first, last, count, --i, compare); }
}

template <CpuType cpu, typename RandomAccessIterator>
void makeMaxHeap(RandomAccessIterator first, RandomAccessIterator last)
{
    const auto count = last - first;
    auto i = count / 2;
    while (0 < i) { internalAdjustMaxHeap<cpu>(first, last, count, --i); }
}

template <CpuType cpu, typename RandomAccessIterator, typename Compare>
RandomAccessIterator isMaxHeapUntil(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    if (first != last)
    {
        auto i = first;
        while (++i != last)
        {
            if (compare(*(first + heapParentIndex<cpu>(i)), *i)) { return i; }
        }
    }
    return last;
}

template <CpuType cpu, typename RandomAccessIterator>
RandomAccessIterator isMaxHeapUntil(RandomAccessIterator first, RandomAccessIterator last)
{
    if (first != last)
    {
        auto i = first;
        while (++i != last)
        {
            if (*(first + heapParentIndex<cpu>(i)) < *i) { return i; }
        }
    }
    return last;
}

template <CpuType cpu, typename RandomAccessIterator, typename Compare>
DAAL_FORCEINLINE bool isMaxHeap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    return (isMaxHeapUntil<cpu>(first, last, compare) == last);
}

template <CpuType cpu, typename RandomAccessIterator>
DAAL_FORCEINLINE bool isMaxHeap(RandomAccessIterator first, RandomAccessIterator last)
{
    return (isMaxHeapUntil<cpu>(first, last) == last);
}

template <CpuType cpu, typename RandomAccessIterator, typename Compare>
DAAL_FORCEINLINE void sortMaxHeap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    while (1 < last - first)
    {
        popMaxHeap<cpu>(first, --last, compare);
    }
}

template <CpuType cpu, typename RandomAccessIterator>
DAAL_FORCEINLINE void sortMaxHeap(RandomAccessIterator first, RandomAccessIterator last)
{
    while (1 < last - first)
    {
        popMaxHeap<cpu>(first, --last);
    }
}

} // namespace internal
} // namespace algorithms
} // namespace daal

#endif
