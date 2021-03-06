/* file: initializer_types.h */
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
//  Implementation of neural_networks Network layer.
//--
*/

#ifndef __INITIALIZERS__TYPES__H__
#define __INITIALIZERS__TYPES__H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "services/daal_defines.h"
#include "services/collection.h"
#include "data_management/data/data_collection.h"
#include "algorithms/neural_networks/initializers/initializer_types_defs.h"
#include "algorithms/engines/engine.h"
#include "algorithms/engines/mt19937/mt19937.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
/**
 * @defgroup initializers Initializers
 * \copydoc daal::algorithms::neural_networks::initializers
 * @ingroup neural_networks
 * @{
 */
/**
 * \brief Contains classes for neural network weights and biases initializers
 */
namespace initializers
{
/**
 * <a name="DAAL-ENUM-ALGORITHMS__NEURAL_NETWORKS__INITIALIZERS__INPUTID"></a>
 * Available identifiers of input objects for neural network weights and biases initializer
 */
enum InputId
{
    data,      /*!< Input data */
    lastInputId = data
};

/**
 * <a name="DAAL-ENUM-ALGORITHMS__NEURAL_NETWORKS__INITIALIZERS__RESULTID"></a>
 * Available identifiers of results for the neural network weights and biases initializer
 */
enum ResultId
{
    value,      /*!< Tensor to store the result */
    lastResultId = value
};

/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__INITIALIZERS__PARAMETER"></a>
 * Parameters of the neural network weights and biases initializer
 */
class Parameter: public daal::algorithms::Parameter
{
public:
    Parameter(layers::forward::LayerIfacePtr layerForParameter = layers::forward::LayerIfacePtr()): layer(layerForParameter) {}
    virtual ~Parameter() {}

    layers::forward::LayerIfacePtr layer; /*!< Pointer to the layer whose weights and biases are initialized by the initializer */
    engines::EnginePtr engine;            /*!< Pointer to the engine for generating random numbers */
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__INITIALIZERS__INPUT"></a>
 * \brief %Input objects for initializer algorithm
 */
class DAAL_EXPORT Input : public daal::algorithms::Input
{
public:
    /**
     * Default constructor
     */
    Input() : daal::algorithms::Input(1) {}
    /** Copy constructor */
    Input(const Input& other) : daal::algorithms::Input(other){}

    virtual ~Input() {}

    /**
     * Returns input tensor of the initializer
     * \param[in] id    Identifier of the input tensor
     * \return          %Input tensor that corresponds to the given identifier
     */
    data_management::TensorPtr get(InputId id) const
    {
        return data_management::Tensor::cast(Argument::get(id));
    }

    /**
     * Sets input for the initializer
     * \param[in] id    Identifier of the input object
     * \param[in] ptr   Pointer to the object
     */
    void set(InputId id, const data_management::TensorPtr &ptr)
    {
        Argument::set(id, ptr);
    }

    /**
     * Checks an input object for the initializer
     * \param[in] par     %Parameter of algorithm
     * \param[in] method  Computation method of the algorithm
     *
     * \return Status of computations
     */
    services::Status check(const daal::algorithms::Parameter *par, int method) const DAAL_C11_OVERRIDE;
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__INITIALIZERS__RESULT"></a>
 * \brief Provides methods to access the result obtained with the compute() method of the neural network weights and biases initializer
 */
class DAAL_EXPORT Result : public daal::algorithms::Result
{
public:
    /** \brief Constructor */
    Result() : daal::algorithms::Result(1) {}

    virtual ~Result() {}

    /**
     * Allocates memory to store the results of initializer
     * \param[in] input  Pointer to the input structure
     * \param[in] par    Pointer to the parameter structure
     * \param[in] method Computation method of the algorithm
     *
     * \return Status of computations
     */
    template <typename algorithmFPType>
    services::Status allocate(const daal::algorithms::Input *input, const daal::algorithms::Parameter *par, const int method)
    {
        const Input *algInput = static_cast<const Input *>(input);

        set(value, algInput->get(data));
        return services::Status();
    }

    /**
     * Returns result of the initializer
     * \param[in] id   Identifier of the result
     * \return         Result that corresponds to the given identifier
     */
    data_management::TensorPtr get(ResultId id) const
    {
        return data_management::Tensor::cast(Argument::get(id));
    }

    /**
     * Sets the result of the initializer
     * \param[in] id    Identifier of the result
     * \param[in] ptr   Pointer to the result
     */
    void set(ResultId id, const data_management::TensorPtr &ptr)
    {
        Argument::set(id, ptr);
    }

    /**
     * Checks the result object for the initializer
     * \param[in] input         %Input of the algorithm
     * \param[in] parameter     %Parameter of algorithm
     * \param[in] method        Computation method of the algorithm
     *
     * \return Status of computations
     */
    virtual services::Status check(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter,
        int method) const DAAL_C11_OVERRIDE;

protected:
    /** \private */
    template<typename Archive, bool onDeserialize>
    services::Status serialImpl(Archive *arch)
    {
        return daal::algorithms::Result::serialImpl<Archive, onDeserialize>(arch);
    }
};
typedef services::SharedPtr<Result> ResultPtr;
} // interface1
using interface1::Input;
using interface1::Result;
using interface1::ResultPtr;
using interface1::Parameter;
} // namespace initializers
/** @} */
} // namespace neural_networks
} // namespace algorithm
} // namespace daal
#endif
