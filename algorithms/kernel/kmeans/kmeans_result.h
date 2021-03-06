/* file: kmeans_result.h */
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
//  Implementation of kmeans classes.
//--
*/

#ifndef __KMEANS_RESULT_
#define __KMEANS_RESULT_

#include "algorithms/kmeans/kmeans_types.h"

using namespace daal::data_management;

namespace daal
{
namespace algorithms
{
namespace kmeans
{

/**
 * Allocates memory to store the results of the K-Means algorithm
 * \param[in] input     Pointer to the structure of the input objects
 * \param[in] parameter Pointer to the structure of the algorithm parameters
 * \param[in] method    Computation method
 */
template <typename algorithmFPType>
DAAL_EXPORT services::Status Result::allocate(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, const int method)
{
    const Parameter *kmPar = static_cast<const Parameter *>(parameter);

    Input *algInput  = static_cast<Input *>(const_cast<daal::algorithms::Input *>(input));
    size_t nFeatures = algInput->getNumberOfFeatures();
    size_t nClusters = kmPar->nClusters;

    services::Status status;
    set(centroids, HomogenNumericTable<algorithmFPType>::create(nFeatures, nClusters, NumericTable::doAllocate, &status));
    set(objectiveFunction, HomogenNumericTable<algorithmFPType>::create(1, 1, NumericTable::doAllocate, &status));
    set(nIterations, HomogenNumericTable<int>::create(1, 1, NumericTable::doAllocate, &status));

    if(kmPar->assignFlag)
    {
        size_t nRows = algInput->get(data)->getNumberOfRows();
        set(assignments, HomogenNumericTable<int>::create(1, nRows, NumericTable::doAllocate, &status));
    }

    return status;
}
/**
 * Allocates memory to store the results of the K-Means algorithm
 * \param[in] partialResult Pointer to the partial result structure
 * \param[in] parameter     Pointer to the structure of the algorithm parameters
 * \param[in] method        Computation method
 */
template <typename algorithmFPType>
DAAL_EXPORT services::Status Result::allocate(const daal::algorithms::PartialResult *partialResult, const daal::algorithms::Parameter *parameter, const int method)
{
    size_t nClusters = (static_cast<const Parameter *>(parameter))->nClusters;
    size_t nFeatures = (static_cast<const PartialResult *>(partialResult))->getNumberOfFeatures();

    services::Status status;
    set(centroids, HomogenNumericTable<algorithmFPType>::create(nFeatures, nClusters, NumericTable::doAllocate, &status));
    set(objectiveFunction, HomogenNumericTable<algorithmFPType>::create(1, 1, NumericTable::doAllocate, &status));
    set(nIterations, HomogenNumericTable<int>::create(1, 1, NumericTable::doAllocate, &status));
    return status;
}

} // namespace kmeans
} // namespace algorithms
} // namespace daal

#endif
