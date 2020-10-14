#ifndef DALI_EXNTEND_LANDMARKS_UTILS_H_
#define DALI_EXNTEND_LANDMARKS_UTILS_H_

#include <limits>
#include "landmarks.h"
#include "dali/core/geom/box.h"
#include "dali/core/tensor_layout.h"
#include "dali/core/math_util.h"

namespace dali {

template <int ndim>
void ReadLandmarks(span<Landmarks_5<ndim, float>> lms, span<const float> coords) {
    static constexpr int lm_size = ndim * 5;
    assert(coords.size() % lm_size == 0);
    assert(coords.size() / lm_size == lms.size());
    int nlms = lms.size();

    std::array<float, lm_size> tmp;
    for (int i = 0; i < nlms; i++) {
        auto &lm = lms[i];
        const float* in = coords.data() + i * lm_size;
        for (int d = 0; d < lm_size; d++) {
            tmp[d] = in[d];
        }

        for (int d = 0; d < ndim; d++) {
            lm.le[d]   = tmp[         d];
            lm.re[d]   = tmp[  ndim + d];
            lm.ml[d]   = tmp[2*ndim + d];
            lm.nose[d] = tmp[3*ndim + d];
            lm.mr[d]   = tmp[4*ndim + d];
        }
    }
}

template <int ndim>
void WriteLandmarks(span<float> coords, span<const Landmarks_5<ndim, float>> lms) {
    static constexpr int lm_size = ndim * 5;
    assert(coords.size() % lm_size == 0);
    assert(coords.size() / lm_size == lms.size());
    int nlms = lms.size();

    for (int i = 0; i < nlms; i++) {
        const auto &lm = lms[i];
        std::array<float, lm_size> tmp;
        for (int d = 0; d < ndim; d++) {
            tmp[         d] = lm.le[d];
            tmp[  ndim + d] = lm.re[d];
            tmp[2*ndim + d] = lm.ml[d];
            tmp[3*ndim + d] = lm.nose[d];
            tmp[4*ndim + d] = lm.mr[d];
        }

        float *out = coords.data() + i * lm_size;
        for (int d = 0; d < lm_size; d++) {
            out[d] = tmp[d];
        }
    }
}

template <int ndim>
Landmarks_5<ndim, float> RemapLandmark(const Landmarks_5<ndim, float> &lm, const Box<ndim, float> &crop) {
    Landmarks_5<ndim, float> mapped_lm = lm;
    auto rel_extent = crop.extent();
    auto le = (lm.le - crop.lo) / rel_extent;
    auto re = (lm.re - crop.lo) / rel_extent;
    auto ml = (lm.ml - crop.lo) / rel_extent;
    auto nose = (lm.nose - crop.lo) / rel_extent;
    auto mr = (lm.mr - crop.lo) / rel_extent;

    mapped_lm.le = clamp(le, vec<ndim, float>{0.0f}, vec<ndim, float>{1.0f});
    mapped_lm.re = clamp(re, vec<ndim, float>{0.0f}, vec<ndim, float>{1.0f});
    mapped_lm.ml = clamp(ml, vec<ndim, float>{0.0f}, vec<ndim, float>{1.0f});
    mapped_lm.nose = clamp(nose, vec<ndim, float>{0.0f}, vec<ndim, float>{1.0f});
    mapped_lm.mr = clamp(mr, vec<ndim, float>{0.0f}, vec<ndim, float>{1.0f});
    return mapped_lm;
}

} // namespace dali

#endif  // DALI_EXNTEND_LANDMARKS_UTILS_H_