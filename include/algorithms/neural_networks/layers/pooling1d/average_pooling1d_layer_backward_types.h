/* file: average_pooling1d_layer_backward_types.h */
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
//  Implementation of backward average 1D pooling layer.
//--
*/

#ifndef __AVERAGE_POOLING1D_LAYER_BACKWARD_TYPES_H__
#define __AVERAGE_POOLING1D_LAYER_BACKWARD_TYPES_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "data_management/data/homogen_tensor.h"
#include "data_management/data/homogen_numeric_table.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/pooling1d/pooling1d_layer_backward_types.h"
#include "algorithms/neural_networks/layers/pooling1d/average_pooling1d_layer_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace average_pooling1d
{
/**
 * @defgroup average_pooling1d_backward Backward One-dimensional Average Pooling Layer
 * \copydoc daal::algorithms::neural_networks::layers::average_pooling1d::backward
 * @ingroup average_pooling1d
 * @{
 */
/**
 * \brief Contains classes for backward average 1D pooling layer
 */
namespace backward
{

/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__AVERAGE_POOLING1D__BACKWARD__INPUT"></a>
 * \brief %Input objects for the backward average 1D pooling layer
 */
class DAAL_EXPORT Input : public pooling1d::backward::Input
{
public:
    typedef pooling1d::backward::Input super;
    /**
     * Default constructor
     */
    Input();

    /** Copy constructor */
    Input(const Input& other);

    virtual ~Input() {}

    using layers::backward::Input::get;
    using layers::backward::Input::set;

    /**
     * Returns an input object for backward average 1D pooling layer
     * \param[in] id    Identifier of the input object
     * \return          %Input object that corresponds to the given identifier
     */
    data_management::NumericTablePtr get(LayerDataId id) const;

    /**
     * Sets an input object for the backward average 1D pooling layer
     * \param[in] id  Identifier of the input object
     * \param[in] ptr Pointer to the object
     */
    void set(LayerDataId id, const data_management::NumericTablePtr &ptr);

    /**
     * Checks an input object for the backward average 1D pooling layer
     * \param[in] parameter Algorithm parameter
     * \param[in] method    Computation method
     *
     * \return Status of computations
     */
    services::Status check(const daal::algorithms::Parameter *parameter, int method) const DAAL_C11_OVERRIDE;

protected:
    virtual data_management::NumericTablePtr getAuxInputDimensions() const DAAL_C11_OVERRIDE;
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__AVERAGE_POOLING1D__BACKWARD__RESULT"></a>
 * \brief Provides methods to access the result obtained with the compute() method
 *        of the backward average 1D pooling layer
 */
class DAAL_EXPORT Result : public pooling1d::backward::Result
{
public:
    DECLARE_SERIALIZABLE_CAST(Result);
    /** Default constructor */
    Result();
    virtual ~Result() {}

    /**
     * Returns an result object for the backward average 1D pooling layer
     */
    using layers::backward::Result::get;

    /**
     * Sets an result object for the backward average 1D pooling layer
     */
    using layers::backward::Result::set;

    /**
     * Allocates memory to store the result of the backward average 1D pooling layer
     * \param[in] input Pointer to an object containing the input data
     * \param[in] parameter %Parameter of the backward average 1D pooling layer
     * \param[in] method Computation method for the layer
     *
     * \return Status of computations
     */
    template <typename algorithmFPType>
    DAAL_EXPORT services::Status allocate(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, const int method);

    /**
     * Checks the result of the backward average 1D pooling layer
     * \param[in] input     %Input object for the layer
     * \param[in] parameter %Parameter of the layer
     * \param[in] method    Computation method
     *
     * \return Status of computations
     */
    services::Status check(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, int method) const DAAL_C11_OVERRIDE;

protected:
    /** \private */
    template<typename Archive, bool onDeserialize>
    services::Status serialImpl(Archive *arch)
    {
        return daal::algorithms::Result::serialImpl<Archive, onDeserialize>(arch);
    }
};
typedef services::SharedPtr<Result> ResultPtr;

} // namespace interface1
using interface1::Input;
using interface1::Result;
using interface1::ResultPtr;
} // namespace backward
/** @} */

} // namespace average_pooling1d
} // namespace layers
} // namespace neural_networks
} // namespace algorithm
} // namespace daal

#endif
