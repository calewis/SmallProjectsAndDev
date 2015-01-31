#include "clusterable.h"

#include <vector>
#include <array>

class Cluster {
   public:
    using position_t = std::array<double, 3>;

    explicit Cluster(std::vector<Clusterable> cs)
        : clusterables_(std::move(cs)) {}

    std::vector<Clusterable> const &elements() const { return clusterables_; }

   private:
    std::vector<Clusterable> clusterables_;
};


unsigned long charge(Cluster const &c) {
    unsigned long cluster_charge = 0;

    for (auto const &elem : c.elements()) {
        cluster_charge += charge(elem);
    }

    return cluster_charge;
}
