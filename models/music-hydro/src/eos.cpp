// Copyright 2018 @ Chun Shen

#include "eos.h"
#include "eos_idealgas.h"
#include "eos_EOSQ.h"
#include "eos_s95p.h"
#include "eos_WB.h"
#include "eos_hotQCD.h"
#include "eos_best.h"
#include "eos_neos.h"
#include "eos_PCE.h"
#include <iostream>
#include <memory>

EOS::EOS(const InitData &DATA_in) : eos_id(DATA_in.whichEOS), DATA(DATA_in) {
    if (eos_id == 0) {
        eos_ptr = std::unique_ptr<EOS_idealgas> (new EOS_idealgas ());
    } else if (eos_id == 1) {
        eos_ptr = std::unique_ptr<EOS_eosQ> (new EOS_eosQ ());
    } else if (eos_id >= 2 && eos_id <= 7) {
        eos_ptr = std::unique_ptr<EOS_s95p> (new EOS_s95p (eos_id));
    } else if (eos_id == 8) {
        eos_ptr = std::unique_ptr<EOS_WB> (new EOS_WB ());
    } else if (eos_id == 9) {
        eos_ptr = std::unique_ptr<EOS_hotQCD> (new EOS_hotQCD ());
    } else if (eos_id >= 10 && eos_id <= 14) {
        eos_ptr = std::unique_ptr<EOS_neos> (new EOS_neos (eos_id));
    } else if (eos_id == 17) {
        eos_ptr = std::unique_ptr<EOS_BEST> (new EOS_BEST ());
    } else if (eos_id == 18) {
        eos_ptr = std::unique_ptr<EOS_PCE> (new EOS_PCE (DATA));
    } else {
        std::cout << "No EOS for eos_id = " << std::endl;
        exit(1);
    }
    eos_ptr->initialize_eos();
}

