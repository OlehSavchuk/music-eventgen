// Copyright 2018 @ Chun Shen

#ifndef SRC_EOS_BEST_H_
#define SRC_EOS_BEST_H_

#include "eos_base.h"

class EOS_BEST : public EOS_base {
 private:
   
 public:
    EOS_BEST();
    ~EOS_BEST();
    
    void initialize_eos();
    double p_rho_func     (double e, double rhob, double proper_tau) const;
    double p_e_func       (double e, double rhob, double proper_tau) const;
    double get_temperature(double e, double rhob, double proper_tau) const;
    double get_mu         (double e, double rhob, double proper_tau) const;
    double get_pressure   (double e, double rhob, double proper_tau) const;
    double get_s2e        (double s, double rhob, double proper_tau) const;

    void check_eos() const {check_eos_with_finite_muB();}
};

#endif  // SRC_EOS_BEST_H_