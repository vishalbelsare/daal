/* file: layer_forward_descriptor.h */
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
//  Implementation of neural network forward layer descriptor.
//--
*/

#ifndef __LAYER_FORWARD_DESCRIPTOR_H__
#define __LAYER_FORWARD_DESCRIPTOR_H__

#include "algorithms/neural_networks/layers/layer_forward.h"

namespace daal
{
namespace algorithms
{
/**
 * \brief Contains classes for training and prediction using neural network
 */
namespace neural_networks
{
/**
 * \brief Contains classes for neural network layers
 */
namespace layers
{
/**
 * \brief Contains classes for the forward stage of the neural network layer
 */
namespace forward
{
namespace interface1
{
/**
 * @ingroup layers_forward
 * @{
 */

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__FORWARD__LAYERDESCRIPTOR"></a>
 * \brief Class defining descriptor for layer on forward stage
 */
class LayerDescriptor
{
public:
    DAAL_NEW_DELETE();

    /** Constructs an empty layer descriptor with zero index */
    LayerDescriptor(): _index(0) {}

    /**
     * Constructs a layer descriptor from the provided layer object and an index to be assigned to this object,
     * and the collection of indices of the layers following the current layer in the network
     * \param[in] index_        Index of the neural network layer
     * \param[in] layer_        Neural network layer
     * \param[in] nextLayers_   Layers following the current layer in the network
     */
    LayerDescriptor(const size_t index_, const forward::LayerIfacePtr &layer_, const NextLayers &nextLayers_) :
        _index(index_), _layer(layer_), _nextLayers(nextLayers_) {}

    /**
     * Constructs a layer descriptor from the provided layer object and an index to be assigned to this object
     * \param[in] index_        Index of the neural network layer
     * \param[in] layer_        Neural network layer
     */
    LayerDescriptor(const size_t index_, const forward::LayerIfacePtr &layer_) : _index(index_), _layer(layer_) {}

    /** Constructor */
    LayerDescriptor(const LayerDescriptor& other): _index(other._index), _layer(other._layer), _nextLayers(other._nextLayers) {}

    /**
     * Access to the index of the layer in the network
     * \return Index of the layer in the network
     */
    size_t index() const { return _index; }

    /**
     * Adds index of a layer to the list of next layers
     * \param[in] index Index to add
     *
     * \return Status of computations
     */
    services::Status addNext(size_t index)
    {
        _nextLayers.add(index);
        return services::Status();
    }

    /**
     * Access to the layer in the network
     * \return The layer in the network
     */
    const forward::LayerIfacePtr & layer() const { return _layer; }

    /**
     * Access to the collection of indices of the layers following the current layer in the network
     * \return The collection of indices of the layers following the current layer in the network
     */
    const NextLayers & nextLayers() const { return _nextLayers; }

private:
    forward::LayerIfacePtr _layer; /*!< Layer algorithm */
    NextLayers _nextLayers;        /*!< Layers following the current layer in the network */
    size_t _index;                 /*!< Index of the layer in the network */
};
/** }@ */
} // namespace interface1
using interface1::LayerDescriptor;
} // namespace forward
} // namespace layers
} // namespace neural_networks
} // namespace algorithms
} // namespace daal
#endif
