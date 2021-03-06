/* file: BaseParameter.java */
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

/**
 * @defgroup pca Principal Component Analysis
 * @brief Contains classes for computing the results of the principal component analysis (PCA) algorithm
 * @ingroup analysis
 * @{
 */
package com.intel.daal.algorithms.pca;

import com.intel.daal.algorithms.Precision;
import com.intel.daal.algorithms.ComputeMode;
import com.intel.daal.algorithms.ComputeStep;
import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__PCA__BASEPARAMETER"></a>
 * @brief Common parameters of the PCA algorithm
 */
public class BaseParameter extends com.intel.daal.algorithms.Parameter {
    public long _algAddr;
    public Method _method;
    public ComputeMode _cmode;
    public ComputeStep _step;
    public Precision _prec;

    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    public BaseParameter(DaalContext context, long cObject, long algAddr, Precision prec, Method method, ComputeMode cmode, ComputeStep step) {
        super(context);
        _algAddr = algAddr;
        _method = method;
        _cmode = cmode;
        _step = step;
        _prec = prec;
        this.cObject = cObject;
    }

    public BaseParameter(DaalContext context, long cObject, long algAddr, Precision prec, Method method, ComputeMode cmode) {
        super(context);
        _algAddr = algAddr;
        _method = method;
        _cmode = cmode;
        _step = ComputeStep.step1Local;
        _prec = prec;
        this.cObject = cObject;
    }

    protected native void cSetCovariance(long cObject, long cCovariance, int method, int cmode, int step, int prec);
}
/** @} */
