#ifndef DALI_EXTEND_LANDMARKS_H_
#define DALI_EXTEND_LANDMARKS_H_

#include "dali/core/geom/vec.h"
// #include "dali/core/geom/box.h"

namespace dali {

template<int ndims, typename CoordinateType>
struct Landmarks_5 {
    static constexpr int ndim = ndims;
    static constexpr int npnt = 5;
    static constexpr int size = ndim * npnt;

    using corner_t = vec<ndims, CoordinateType>;
    static_assert(std::is_pod<corner_t>::value, "Corner has to be POD");

    // left eye, right eye, mouth left corner, nose, mouth right corner
    corner_t le, re, ml, nose, mr;

    constexpr Landmarks_5() = default;

    constexpr DALI_HOST_DEV Landmarks_5(const corner_t &le, const corner_t &re,
                                        const corner_t &ml, const corner_t &nose, const corner_t &mr) :
            le(le), re(re), ml(ml), nose(nose), mr(mr) {}

    // constexpr DALI_HOST_DEV bool isContainedByBox(const Box &other) const {
    //     for (int i = 0; i < ndims; i++) {
    //         if (!((other.lo[i] >= le[i] && other.hi[i] <= le[i]) &&
    //               (other.lo[i] >= re[i] && other.hi[i] <= re[i]) &&
    //               (other.lo[i] >= ml[i] && other.hi[i] <= ml[i]) &&
    //               (other.lo[i] >= nose[i] && other.hi[i] <= nose[i]) &&
    //               (other.lo[i] >= mr[i] && other.hi[i] <= mr[i]))
    //            )
    //             return false;
    //     }
    //     return true;
    // }
};

template <int ndims, typename CoordinateType>
std::ostream &operator<<(std::ostream &os, const Landmarks_5<ndims, CoordinateType> &lm) {
    auto print_corner = [&os](const typename Landmarks_5<ndims, CoordinateType>::corner_t &c) {
        for (size_t i = 0; i < ndims; i++) {
            os << (i ? ", " : "(") << c[i];
        }
        os << ")";
    };
    os << "{";
    print_corner(lm.le);
    os << ",";
    print_corner(lm.re);
    os << ",";
    print_corner(lm.ml);
    os << ",";
    print_corner(lm.nose);
    os << ",";
    print_corner(lm.mr);
    os << "}";
    return os;
}

} // namespace dali

#endif  // DALI_EXTEND_LANDMARKS_H_