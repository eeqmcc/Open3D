// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#pragma once

#include "open3d/core/Tensor.h"

namespace open3d {
namespace t {
namespace pipelines {
namespace kernel {

/// \brief Convert rotation and translation to the transformation matrix.
///
/// \param R Rotation, a tensor of shape {3, 3} and dtype Float32.
/// \param t Translation, a tensor of shape {3, 3} and dtype Float32.
/// \return Transformation, a tensor of shape {4, 4}, dtype Float32.
core::Tensor RtToTransformation(const core::Tensor &R, const core::Tensor &t);

/// \brief Convert pose to the transformation matrix.
///
/// \param pose Pose [alpha, beta, gamma, tx, ty, tz], a tensor of
/// shape {6} and dtype Float32.
/// \return Transformation, a tensor of shape {4, 4}, dtype Float32.
core::Tensor PoseToTransformation(const core::Tensor &pose);

/// \brief Decodes a 6x6 linear system from a compressed 1x27 or 1x29 tensor.
/// If the compressed tensor is 1x29, then it is assumed that residual and
/// inlier count are present, if it is 1x27, they are assumed to be absent.
/// \param A_reduction {1x27} tensor storing a linear system
/// (21 for JtJ matrix, 6 for Jtr).
/// \param delta [output] 6d tensor for a se3 tangent vector.
void DecodeAndSolve6x6(const core::Tensor &A_reduction, core::Tensor &delta);

/// \brief Decodes a 6x6 linear system from a compressed 1x29 tensor.
/// \param A_reduction {1x29} tensor storing a linear system
/// (21 for JtJ matrix, 6 for Jtr, 1 for residual, 1 for inlier count).
/// \param delta [output] 6d tensor for a se3 tangent vector.
/// \param residual [output] 1d tensor for residual.
void DecodeAndSolve6x6(const core::Tensor &A_reduction,
                       core::Tensor &delta,
                       core::Tensor &residual);

/// \brief Decodes a 6x6 linear system from a compressed 1x29 tensor.
/// \param A_reduction {1x29} tensor storing a linear system
/// (21 for JtJ matrix, 6 for Jtr, 1 for residual, 1 for inlier count).
/// \param delta [output] 6d tensor for a se3 tangent vector.
/// \param residual [output] double.
void DecodeAndSolve6x6(const core::Tensor &A_reduction,
                       core::Tensor &delta,
                       double &residual,
                       int64_t &count);

}  // namespace kernel
}  // namespace pipelines
}  // namespace t
}  // namespace open3d
