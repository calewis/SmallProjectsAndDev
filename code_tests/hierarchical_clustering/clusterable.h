#pragma once

#include <array>
#include <memory>
#include <typeinfo>
#include <iostream>

class ClusterableConcept {
   public:
    using position_t = std::array<double, 3>;

    virtual ~ClusterableConcept() = default;

    virtual ClusterableConcept *clone_() const = 0;
    virtual unsigned long charge_() const = 0;
};

template <typename T>
class ClusterableModel : public ClusterableConcept {
   public:
    using position_t = ClusterableConcept::position_t;

    ClusterableModel(T t) : element_(std::move(t)) {}
    ClusterableModel(const ClusterableModel &c) = default;
    ClusterableModel(ClusterableModel &&c) = default;
    ClusterableModel &operator=(ClusterableModel c) {
        element_ = std::move(c.element_);
        return *this;
    }
    ClusterableModel &operator=(ClusterableModel &&c) = default;

    ClusterableConcept *clone_() const override final {
        return new ClusterableModel(*this);
    }

    unsigned long charge_() const override final {
        return charge(element_);
    }

   private:
    T element_;
};

class Clusterable {
   public:
    using position_t = ClusterableConcept::position_t;

    Clusterable() = delete;

    template <typename T>
    Clusterable(T t)
        : element_impl_(std::make_shared<ClusterableModel<T>>(std::move(t))) {
    }

    Clusterable(Clusterable const &c) = default;
    Clusterable &operator=(Clusterable const &c) = default;
    Clusterable(Clusterable &&c) = default;
    Clusterable &operator=(Clusterable &&c) = default;

    friend unsigned long charge(Clusterable const &c){
        return c.element_impl_->charge_();
    }

   private:
    std::shared_ptr<ClusterableConcept> element_impl_;
};


